#include <iostream>
#include <algorithm>
#include <set>
#include <fstream>
#include "Dictionary.h"
#include "Lock.h"
using namespace std;
int BinarySearch(string arr[], string x, int n) {
    int l = 0;
    int r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (x == (arr[m]))
            return m;
        if (x > (arr[m]))
            l = m + 1;
        else
            r = m - 1;
    }
    return 0;
}

set<string> GenerateAndFindWords(Dictionary d, Lock l) {
    /* Generate all combinations */
    std::cout << "Generating Combinations..." << std::endl;
    l.GenerateCombinations();
    return l.GetFoundWords();
}

void OutputWords(set<string> foundWords) {
    ofstream outFile;
    outFile.open("output.txt");
    if (!outFile) {
        cout << "unable to open file";
        return;
    }
    for (auto& w : foundWords) {
        std::cout << w << std::endl;
        outFile << w << "\n";
    }
    std::cout << "Words Found:" << foundWords.size() << std::endl;
    outFile << "Words Found:" << foundWords.size() << "\n";
    outFile.close();
}

int main() {
    std::cout << "Creating Dictionary..." << std::endl;
    Dictionary dictionary("dictionary.txt");
    std::cout << "Creating Lock..." << std::endl;
    Lock lock("wheels.txt", dictionary);
    set<string> words = GenerateAndFindWords(dictionary, lock);
    OutputWords(words);
    return 0;
}