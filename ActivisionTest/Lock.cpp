#include "Lock.h"
Lock::Lock(string file) {
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
	current.resize(numWheels);
}

void Lock::GenerateCombinations() {
	while (!(pos == 0 && current.at(pos) == numChars)) {
		while (current.at(pos) < numChars) {
			if (pos != numWheels - 1) {
				current.at(pos + 1) = 0;
				++pos;
			}
			else {
				combinations.push_back(current);
				current.at(pos)++;
			}
		}
		if (pos > 0) {
			--pos;
			current.at(pos)++;
		}
	}
}
