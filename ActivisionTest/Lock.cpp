/*		 Created By Samuel Buzz Appleby
 *               05/02/2021
 *			  Lock Implementation			 */
#include "Lock.h"

Lock::Lock(ifstream& file, Dictionary& d) {
	numWheels = 0;
	numChars = 0;
	chunkSize = 10000;
	numThreads = 20;
	dictionary = &d;

	string line;
	int pos = 0;
	while (getline(file, line)) {
		switch (pos) {
		case 0:
			/* Number of wheels must be a number */
			if (!regex_match(line, std::regex("^[0-9]+$"))) {
				cout << "Number of wheels is not valid!";
				exit(EXIT_FAILURE);
			}
			numWheels = stoi(line);
			break;
		case 1:
			/* Number of characters per wheel must be a number */
			if (!regex_match(line, std::regex("^[0-9]+$"))) {
				cout << "Number of characters per wheel is not valid!";
				exit(EXIT_FAILURE);
			}
			numChars = stoi(line);
			break;
		default:
			/* Wheels must be of correct length and contain only characters */
			if (line.length() != numChars || !regex_match(line, std::regex("^[A-Za-z]+$"))) {
				cout << "A wheel is not valid!";
				exit(EXIT_FAILURE);
			}
			else if (wheels.size() == numWheels) {
				cout << "There are too many wheels!";
				exit(EXIT_FAILURE);
			}
			transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return toupper(c); });
			wheels.push_back(make_pair(pos - 2, line));
			break;
		}
		++pos;
	}
	if (wheels.size() < numWheels) {
		cout << "There are too few wheels!";
		exit(EXIT_FAILURE);
	}
}

/* Given our number of wheels(N) and characters per wheel (M), we generate and test every possible combination, M ^ N */
set<string> Lock::GenerateAndTestCombinations() {
	int* current = new int[numWheels] {0};
	int** combinations = new int*[chunkSize];		// Split the total combinations up into packet sizes
	for (int i = 0; i < chunkSize; ++i)
		combinations[i] = new int[numWheels];

	int pos = 0, count = 0;
	while ((pos != 0 || current[pos] != numChars)) {
		while (current[pos] < numChars) {
			if (pos != numWheels - 1) {
				current[pos + 1] = 0;
				++pos;
			}
			else {
				for (int i = 0; i < numWheels; ++i) {
					if(count < chunkSize)
						combinations[count][i] = current[i];
				}
				++count;
				if (count % chunkSize == 0) {
					/* We have our chunk of combinations, so send it for testing */
					FindWords(combinations, count);
					count = 0;
				}
				current[pos]++;
			}
		}
		if (pos > 0) {
			--pos;
			current[pos]++;
		}
	}
	if (count % chunkSize != 0)			// If there was a remainder chunk
		FindWords(combinations, count);

	delete[] current;
	for (int i = 0; i < chunkSize; ++i) {
		delete[] combinations[i];
	}
	delete[] combinations;
	return foundWords;
}

/* With our chunk of data and its size, we can multi-thread through the combinations */
void Lock::FindWords(int** combs, int newSize) {
	float rem = newSize % numThreads;
	int size = newSize / numThreads;
	int threadSize = size;
	vector<thread> threads(numThreads);
	threadWords.resize(numThreads);

	for (int i = 0; i < numThreads; ++i) {
		if (rem != 0 && i == numThreads - 1) 
			threadSize += rem;
		vector<vector <int>> comb(threadSize);
		for (int j = 0; j < threadSize; ++j) {
			comb.at(j).resize(numWheels);
			for(int k = 0; k < numWheels; ++k)
				comb.at(j).at(k) = combs[j + (i * size)][k];
		}
		threads.at(i) = thread(&Lock::TestCombinations, this, comb, threadSize, i);
	}

	for (auto& t : threads)		// Ensure all threads are done
		t.join();
	for (int i = 0; i < threadWords.size(); ++i) {
		for (auto& w : threadWords.at(i))
			foundWords.insert(w);		// Aggregate our found words lists
	}
}

/* We can perform a binary search on our ordered containers */
int Lock::BinarySearch(string arr[], string x, int n) {
	int l = 0;
	int r = n - 1;
	while (l <= r) {
		int m = l + (r - l) / 2;
		if (x == (arr[m])) 
			return m;
		else if (x > (arr[m]))
			l = m + 1;
		else
			r = m - 1;
	}
	return 0;
}

/* Given our sub set of combinations, we see what words can be made */
void Lock::TestCombinations(vector<vector<int>> combs, int size, int pos) {
	for (int i = 0; i < size; ++i) {
		vector<int> current = combs[i];
		string substr;
		for (int i = 0; i < numWheels - 1; ++i) {
			substr.clear();
			/* Keep going along the current combination to see if we can extend the word */
			while (i + substr.size() < numWheels) {
				if (substr.size() == 0)		// First round
					substr += (wheels.at(i).second[current.at(i)]);
				substr += (wheels.at(i + substr.size()).second[current.at(i + substr.size())]);
				if (BinarySearch(dictionary->GetValidWords(), substr, dictionary->GetNumWords())) 
					threadWords.at(pos).insert(substr);
			}
		}
	}
}