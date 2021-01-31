#include <iostream>
#include <algorithm>
#include <set>
#include <fstream>
#include "Dictionary.h"
#include "Lock.h"
using namespace std;
set<string> foundWords;
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

bool WordInDictionary(string word, Dictionary d) {
    if (BinarySearch(d.GetValidWords(), word, d.GetNumWords()))
        return true;
    return false;
}

vector<vector<int>> GenerateCombinations(Lock l) {
    vector<int> v(l.GetNumWheels());
    vector<vector<int>> combination;
    while (v.at(0) < l.GetNumChars()) {
        v.at(1) = 0;
        while (v.at(1) < l.GetNumChars()) {
            v.at(2) = 0;
            while (v.at(2) < l.GetNumChars()) {
                v.at(3) = 0;
                while (v.at(3) < l.GetNumChars()) {
                    v.at(4) = 0;
                    while (v.at(4) < l.GetNumChars()) {
                        combination.push_back(v);
                        v.at(4)++;
                    }
                    v.at(3)++;
                }
                v.at(2)++;
            }
            v.at(1)++;
        }
        v.at(0)++;
    }
    return combination;
}

void OutputWords(Dictionary d, Lock l) {
    ofstream outFile;
    outFile.open("output.txt");
    if (!outFile) {
        cout << "unable to open file";
        return;
    }

    /* Get each case */
    vector<vector<int>> combinations = GenerateCombinations(l);
    std::cout << combinations.size();

	/* Test each case */
    string test;
    for (auto& instance : combinations) {
        for (int i = 0; i < l.GetNumWheels() - 1; ++i) {
            test.clear();
            test += (l.GetWheels().at(i).second.at(instance.at(i)));
            test += (l.GetWheels().at(i + 1).second.at(instance.at(i + 1)));
            int inc = 2;
            while (WordInDictionary(test, d)) {     // Keep going along the current combination to see if we can extend the word
                foundWords.insert(test);
                if (i + inc < l.GetNumWheels()) {
                    test += (l.GetWheels().at(i + inc).second.at(instance.at(i + inc)));
                    ++inc;
                }
                else
                    break;      // We have tested the last wheel
            }
        }
    }

    for(auto& w : foundWords)
        outFile << w << "\n";
    outFile << "Words Found:" << foundWords.size() << "\n";
    outFile.close();
}

int main() {
    Dictionary dictionary("dictionary.txt");
    Lock lock("wheels.txt");
    OutputWords(dictionary, lock);
    return 0;
}