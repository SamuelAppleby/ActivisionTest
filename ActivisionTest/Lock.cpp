/*		 Created By Samuel Buzz Appleby
 *               03/02/2021
 *			  Lock Implementation			 */
#include "Lock.h"
#include <thread>
Lock::Lock(ifstream& file, Dictionary& d) {
	numWheels = 0;
	numChars = 0;
	bestLeft = 0;
	dictionary = &d;

	string line;
	int pos = 0;
	while (getline(file, line)) {
		switch (pos) {
		case 0:
			numWheels = stoi(line);
			break;
		case 1:
			numChars = stoi(line);
			break;
		default:
			wheels.push_back(make_pair(pos - 2, line));
			break;
		}
		++pos;
	}
}

void foo(int Z)
{
	for (int i = 0; i < Z; i++) {
		cout << "Thread using function"
			" pointer as callable\n";
	}
}

/* Given our number of wheels(N) and characters per wheel (M), we test every possible combination, M ^ N */
set<string> Lock::GenerateAndTestCombinations() {
	int total = pow(numChars, numWheels);

	int* current = new int[numWheels] {0};
	int** combinations = new int* [total];
	for (int i = 0; i < total; ++i)
		combinations[i] = new int[numWheels] {0};

	int pos = 0, count = 0;
	while ((pos != 0 || current[pos] != numChars)) {
		while (current[pos] < numChars) {
			if (pos != numWheels - 1) {
				current[pos + 1] = 0;
				++pos;
			}
			else {
				for (int i = 0; i < numWheels; ++i) {
					combinations[count][i] = current[i];
				}
				++count;
				current[pos]++;
			}
		}
		if (pos > 0) {
			--pos;
			current[pos]++;
		}
	}

	//TestCombination(combinations, total);		// Non multi threading
	int numThread = 2;
	float rem = total % numThread;
	int size = total / numThread;
	vector<int**> subCombs;
	vector<thread> threads;
	subCombs.resize(numThread);
	for (int i = 0; i < numThread; ++i) {
		int** comb;
		
		if (rem != 0 && i == numThread - 1) {
			comb = new int* [size + rem];
			for (int j = 0; j < size + rem; ++j) {
				comb[j] = new int[numWheels] {0};
				comb[j] = combinations[j + (i * size)];
			}
			subCombs[i] = comb;
			threads.push_back(thread(&Lock::TestCombinations, this, subCombs[i], size + rem));
		}
		else {
			comb = new int* [size];
			for (int j = 0; j < size; ++j) {
				comb[j] = new int[numWheels] {0};
				comb[j] = combinations[j + (i * size)];
			}
			subCombs[i] = comb;
			threads.push_back(thread(&Lock::TestCombinations, this, subCombs[i], size));
		}
	}
	for (auto& t : threads)
		t.join();
	return foundWords;
}

/* We can perform a binary search on our ordered containers */
int Lock::BinarySearch(string arr[], string x, int n) {
	int l = bestLeft;
	int r = n - 1;
	while (l <= r) {
		int m = l + (r - l) / 2;
		if (x == (arr[m])) {
			bestLeft = m;		// If we find a match, the next possible string MUST be to the right
			return m;
		}
		else if (x > (arr[m]))
			l = m + 1;
		else
			r = m - 1;
	}
	bestLeft = 0;
	return 0;
}

/* Given our lock configuration, we see what words can be made */
void Lock::TestCombinations(int** combs, int size) {
	for (int i = 0; i < size; ++i) {
		int* current = combs[i];
		string substr;
		for (int i = 0; i < numWheels - 1; ++i) {
			substr.clear();
			/* Keep going along the current combination to see if we can extend the word */
			while (i + substr.size() < numWheels) {
				if (substr.size() == 0)		// First round
					substr += (wheels.at(i).second[current[i]]);
				substr += (wheels.at(i + substr.size()).second[current[i + substr.size()]]);
				if (BinarySearch(dictionary->GetValidWords(), substr, dictionary->GetNumWords())) {
					foundWords.insert(substr);
				}
			}
		}
	}
}