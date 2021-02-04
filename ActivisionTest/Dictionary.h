/*		 Created By Samuel Buzz Appleby
 *               03/02/2021
 *			 Dictionary Definition			 */
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  
#include <iostream>  
#include <algorithm>
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

