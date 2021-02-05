/*		 Created By Samuel Buzz Appleby
 *               05/02/2021
 *			Dictionary Implementation			 */
#include "Dictionary.h"

Dictionary::Dictionary(ifstream& file) {
	numWords = 0;
	string line;
	int pos = 0;
	set<string> orderedWords;
	while (getline(file, line)) {
		/* We fail if any word in the dictionary is not made of characters */
		if (!regex_match(line, std::regex("^[A-Za-z]+$"))) {
			cout << "A dictionary word is not valid!";
			exit(EXIT_FAILURE);
		}
		transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return toupper(c); });
		orderedWords.insert(line);
		++pos;
	}
	/* Convert to array, contiguous memory */
	numWords = orderedWords.size();
	validWords = new string[numWords];
	pos = 0;
	for (auto& w : orderedWords) {
		if(pos < numWords)
			validWords[pos] = w;
		pos++;
	}
}

Dictionary::~Dictionary() {
	delete[] validWords;
	validWords = nullptr;
}

