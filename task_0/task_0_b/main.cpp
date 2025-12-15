#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


// g++ -o wordcount main.cpp
// ./wordcount input.txt output.csv
int main(int argc, char *argv[]) {
    map<string, int> wordCount;
    list<string> words;
    string line, word;

    fstream file;
    file.open(argv[1]);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << argv[1] << endl;
        return 1;
    }

    while (getline(file, line)) {
        for (int i = 0; i < line.length(); i++) {
            if (isalnum(static_cast<unsigned char>(line[i])))
                word += tolower(static_cast<unsigned char>(line[i]));
            else if (!word.empty()) {
                wordCount[word]++;
                words.push_back(word);
                word.clear();
            }
        }
        if (!word.empty()) {
            wordCount[word]++;
            words.push_back(word);
            word.clear();
        }
    }

    ofstream outfile(argv[2]);
    vector<pair<string, int>> vecWordCount(wordCount.begin(), wordCount.end());

    sort(vecWordCount.begin(), vecWordCount.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    outfile << "Слово, частота, частота(в %)" << endl;
    for (auto& [pair1, pair2] : vecWordCount) {
        double average = static_cast<double>(pair2) / static_cast<double>(words.size());
        outfile << pair1 << "," << pair2 << "," << average << endl;
    }

    file.close();
    return 0;
}