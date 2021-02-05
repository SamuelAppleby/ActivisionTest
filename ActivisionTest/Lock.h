/*		 Created By Samuel Buzz Appleby
 *               05/02/2021
 *			   Lock Definition			 */
#pragma once
#include "Dictionary.h" 
#include <vector>
#include <thread>

using namespace std;
class Lock {
public:
	Lock(ifstream& file, Dictionary& d);
	set<string> GenerateAndTestCombinations();
	void FindWords(int** combs, int size);
	int BinarySearch(string arr[], string x, int n);
	void TestCombinations(vector<vector <int>>  current, int size, int pos);

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
	Dictionary* dictionary;
	vector<pair<int, string>> wheels;
	int numWheels;
	int numChars;
	int chunkSize;
	int numThreads;
	vector<set<string>> threadWords;
	set<string> foundWords;
};


