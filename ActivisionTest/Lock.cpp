#include "Lock.h"
#include <algorithm>
Lock::Lock(string file, Dictionary d) {
	numWheels = 0;
	numChars = 0;
	ifstream infile(file);
	if (!infile) {
		cout << "unable to open file";
		return;
	}
	string line;
	int i = 0;
	while (getline(infile, line)) {
		if (i == 0)
			numWheels = std::stoi(line);
		else if (i == 1)
			numChars = std::stoi(line);
		else {
			std::vector<char> charVec;
			int x = 0;
			while (line[x]) {
				charVec.push_back(line[x]);
				x++;
			}
			wheels.push_back(make_pair(i - 2, charVec));
		}
		++i;
	}
	dictionary = d;
}

void Lock::GenerateCombinations() {
	vector<int> current;
	int pos = 0;
	current.resize(numWheels);
	while (!(pos == 0 && current.at(pos) == numChars)) {
		while (current.at(pos) < numChars) {
			if (pos != numWheels - 1) {
				current.at(pos + 1) = 0;
				++pos;
			}
			else {
				TestCombination(current);
				current.at(pos)++;
			}
		}
		if (pos > 0) {
			--pos;
			current.at(pos)++;
		}
	}
}

int Lock::BinarySearch(string arr[], string x, int n) {
	int l = bestLeft;		 
	int r = n - 1;
	while (l <= r) {
		int m = l + (r - l) / 2;
		if (x == (arr[m])) {
			bestLeft = m;		// If we find a match, the next possible string MUST be to the right of it
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

void Lock::TestCombination(vector<int> current) {
	string substr;
	for (int i = 0; i < numWheels - 1; ++i) {
		substr.clear();
		substr += (wheels.at(i).second.at(current.at(i)));
		substr += (wheels.at(i + 1).second.at(current.at(i + 1)));
		transform(substr.begin(), substr.end(), substr.begin(), [](unsigned char c) { return tolower(c); });

		/* Keep going along the current combination to see if we can extend the word */
		while (BinarySearch(dictionary.GetValidWords(), substr, dictionary.GetNumWords())) {    
			transform(substr.begin(), substr.end(), substr.begin(), [](unsigned char c) { return toupper(c); });
			foundWords.insert(substr);
			if (i + substr.size() < numWheels) {
				substr += (wheels.at(i + substr.size()).second.at(current.at(i + substr.size())));
				transform(substr.begin(), substr.end(), substr.begin(), [](unsigned char c) { return tolower(c); });
			}
			else {
				break;      // We have tested the last wheel
			}
		}
	}
}