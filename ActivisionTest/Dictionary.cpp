#include "Dictionary.h"

Dictionary::Dictionary(string file) {
	ifstream infile(file);
	if (!infile) {
		cout << "unable to open file";
		return;
	}
	string line;
	int i = 0;
	while (getline(infile, line)) {
		if (i == 0) {
			numWords = std::stoi(line);
			validWords = new string[numWords];
		}
		else 
			validWords[i - 1] = line;
		++i;
	}
}
