/*		 Created By Samuel Buzz Appleby
 *               03/02/2021
 *			   Lock Definition			 */
#pragma once
#include "Dictionary.h" 
#include <vector>
using namespace std;
class Lock {
public:
	Lock(ifstream& file, Dictionary& d);

	set<string> GenerateAndTestCombinations();
	void TestCombinations(int** current, int size);
	int BinarySearch(string arr[], string x, int n);

	int GetNumWheels() const {
		return numWheels;
	}
	int GetNumChars() const {
		return numChars;
	}
	vector<pair<int, string>> GetWheels() const {
		return wheels;
	}
private:
	int numWheels;
	int numChars;
	vector<pair<int, string>> wheels;
	set<string> foundWords;
	Dictionary* dictionary;
	int bestLeft;
};

