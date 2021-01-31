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
	int GetNumWheels() const {
		return numWheels;
	}
	int GetNumChars() const {
		return numChars;
	}
	vector<pair<int, vector<char>>> GetWheels() const {
		return wheels;
	}
private:
	int numWheels;
	int numChars;
	vector<pair<int, vector<char>>> wheels;
};

