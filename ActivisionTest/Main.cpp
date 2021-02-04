/*		 Created By Samuel Buzz Appleby
 *               03/02/2021
 *			        Main			    */
#include <iostream>
#include <fstream>
#include "Dictionary.h"
#include "Lock.h"
using namespace std;

/* Outputs all found words to console and output.txt */
void OutputWords(set<string> foundWords) {
    ofstream outFile;
    outFile.open("output.txt");
    if (!outFile) {
        cout << "Cannot Create File";
        return;
    }
    for (auto& w : foundWords) {
        cout << w << endl;
        outFile << w << "\n";
    }
    cout << "Words Found:" << foundWords.size() << endl;
    outFile << "Words Found:" << foundWords.size() << "\n";
    outFile.close();
}

/* Takes in a file name and will return a file stream */
ifstream LoadFile(string fileName) {
    ifstream infile(fileName);
    if (!infile) {
        cout << fileName << " Does Not Exist";
    }
    return infile;
}

int main() {
    /* File loading */
    cout << "Loading Files..." << endl;
    ifstream dictionaryStream = LoadFile("dictionary.txt");
    ifstream wheelStream = LoadFile("wheels.txt");
    if (!dictionaryStream || !wheelStream)
        return -1;

    /* Create our objects */
    cout << "Creating Dictionary..." << endl;
    Dictionary dictionary(dictionaryStream);

    cout << "Creating Lock..." << endl;
    Lock lock(wheelStream, dictionary);

    /* Output */
    cout << "Finding Words..." << endl;
    set<string> foundWords = lock.GenerateAndTestCombinations();
    OutputWords(foundWords);
    return 0;
}