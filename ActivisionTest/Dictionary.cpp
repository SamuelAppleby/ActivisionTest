/*		 Created By Samuel Buzz Appleby
 *               03/02/2021
 *			Dictionary Implementation			 */
#include "Dictionary.h"
#include <set>
Dictionary::Dictionary(ifstream& file) {
	numWords = 0;
	
	string line;
	int pos = 0;
	set<string> orderedWords;		// We want our dictionary ordered
	while (getline(file, line)) {
		transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return toupper(c); });
		orderedWords.insert(line);
		++pos;
	}
	numWords = orderedWords.size();
	validWords = new string[numWords];
	pos = 0;
	for (auto& w : orderedWords) {
		validWords[pos] = w;
		pos++;
	}
}

Dictionary::~Dictionary() {
	
}

