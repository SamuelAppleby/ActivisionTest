/*		 Created By Samuel Buzz Appleby
 *               05/02/2021
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
        exit(EXIT_FAILURE);
    }
    return infile;
}

int main() {
    /* File loading */
    cout << "Loading Files..." << endl;
    ifstream dictionaryStream = LoadFile("dictionary.txt");
    ifstream wheelStream = LoadFile("wheels.txt");

    /* Create our objects */
    cout << "Loading Dictionary..." << endl;
    Dictionary dictionary(dictionaryStream);

    cout << "Loading Lock..." << endl;
    Lock lock(wheelStream, dictionary);

    /* Output */

    /* Set up multi-threading */
    cout << "Finding Words..." << endl;
    set<string> foundWords = lock.GenerateAndTestCombinations();
    OutputWords(foundWords);
    return 0;
}