#pragma once
#include "Dictionary.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  
#include <iostream>  
#include <set>
using namespace std;
class Lock {
public:
	Lock(string file, Dictionary d);
	void GenerateCombinations();
	void TestCombination(vector<int> comb);
	int BinarySearch(string arr[], string x, int n);
	int GetNumWheels() const {
		return numWheels;
	}
	int GetNumChars() const {
		return numChars;
	}
	vector<pair<int, vector<char>>> GetWheels() const {
		return wheels;
	}
	set<string> GetFoundWords() const {
		return foundWords;
	}
private:
	int numWheels;
	int numChars;
	vector<pair<int, vector<char>>> wheels;
	int pos;
	set<string> foundWords;
	Dictionary dictionary;
};

