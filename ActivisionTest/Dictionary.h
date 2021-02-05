/*		 Created By Samuel Buzz Appleby
 *               05/02/2021
 *			 Dictionary Definition			 */
#pragma once
#include <string>
#include <fstream>
#include <iostream>  
#include <algorithm>
#include <set>
#include <regex>

using namespace std;
class Dictionary {
public:
	Dictionary(ifstream& file);
	Dictionary() = default;
	~Dictionary();

	string* GetValidWords() const {
		return validWords;
	}
	int GetNumWords() const {
		return numWords;
	}
private:
	int numWords;
	string* validWords;
};

