/*		 Created By Samuel Buzz Appleby
 *               03/02/2021
 *			  Lock Implementation			 */
#include "Lock.h"
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

/* Given our number of wheels(N) and characters per wheel (M), we test every possible combination, M ^ N */
set<string> Lock::GenerateAndTestCombinations() {
	vector<int> current;
	current.resize(numWheels);
	int pos = 0;
	int combinations = 0;
	while (!(pos == 0 && current.at(pos) == numChars)) {
		while (current.at(pos) < numChars) {
			if (pos != numWheels - 1) {
				current.at(pos + 1) = 0;
				++pos;
			}
			else {
				combinations++;
				TestCombination(current);
				current.at(pos)++;
			}
		}
		if (pos > 0) {
			--pos;
			current.at(pos)++;
		}
	}
	std::cout << "combs " << combinations << std::endl;
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
void Lock::TestCombination(vector<int> current) {
	string substr;
	for (int i = 0; i < numWheels - 1; ++i) {
		substr.clear();
		/* Keep going along the current combination to see if we can extend the word */
		while (i + substr.size() < numWheels) {
			if(substr.size() == 0)		// First round
				substr += (wheels.at(i).second[current.at(i)]);
			substr += (wheels.at(i + substr.size()).second[current.at(i + substr.size())]);
			if (BinarySearch(dictionary->GetValidWords(), substr, dictionary->GetNumWords()))
				foundWords.insert(substr);
		}
	}
}