#include "Lock.h"
Lock::Lock(string file, Dictionary d) {
	numWheels = 0;
	numChars = 0;
	pos = 0;
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
				charVec.push_back(tolower(line[x]));
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
	int l = 0;
	int r = n - 1;
	while (l <= r) {
		int m = l + (r - l) / 2;
		if (x == (arr[m]))
			return m;
		if (x > (arr[m]))
			l = m + 1;
		else
			r = m - 1;
	}
	return 0;
}

void Lock::TestCombination(vector<int> current) {
	string test;
	for (int i = 0; i < numWheels - 1; ++i) {
		test.clear();
		test += (wheels.at(i).second.at(current.at(i)));
		test += (wheels.at(i + 1).second.at(current.at(i + 1)));
		int inc = 2;
		while (BinarySearch(dictionary.GetValidWords(), test, dictionary.GetNumWords())) {     // Keep going along the current combination to see if we can extend the word
			foundWords.insert(test);
			if (i + inc < numWheels) {
				test += (wheels.at(i + inc).second.at(current.at(i + inc)));
				++inc;
			}
			else
				break;      // We have tested the last wheel
		}
	}
}