#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  
#include <iostream>  
using namespace std;
class Dictionary {
public:
	Dictionary(string file);
	Dictionary() = default;
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

