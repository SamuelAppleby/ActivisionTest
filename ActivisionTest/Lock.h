#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  
#include <iostream>  
using namespace std;
class Lock {
public:
	Lock(string file);
	void GenerateCombinations();
	int GetNumWheels() const {
		return numWheels;
	}
	int GetNumChars() const {
		return numChars;
	}
	vector<pair<int, vector<char>>> GetWheels() const {
		return wheels;
	}
	vector<vector<int>> GetCombinations() const {
		return combinations;
	}
private:
	int numWheels;
	int numChars;
	vector<pair<int, vector<char>>> wheels;
	vector<vector<int>> combinations;
	int pos;
	vector<int> current;
};

