#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>

#include "InfoCase.h"
#include "WordInfo.h"

std::vector<WordInfo*> words;

void createWord(std::string word) {
    words.push_back(new WordInfo(word));
    //std::cout << "Created " << word << "\n";
}

int main() {

    std::ifstream wordListFile("WordList.txt");
    std::vector<std::string>* wordList = new std::vector<std::string>();
    WordInfo::wordList = wordList;
    std::string word;

    std::cout << "Loading words...\n";
    int lim = 0;
    while (std::getline(wordListFile, word) && lim < 100) {
        wordList->push_back(word);
        lim++;
    }
    std::cout << "Done\n";

    std::vector<std::thread> workers;

    std::cout << "Computing word information...\n";
    auto start = std::chrono::high_resolution_clock::now();

    int index = 0;
    while (words.size() < wordList->size()) {
        while (workers.size() < 16 && index < wordList->size()) {
            workers.push_back(std::thread(createWord, wordList->at(index)));
            index++;
        }
        for (std::thread& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
        workers.clear();
    }
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    std::cout << time << "\n";


    std::cout << "Done\n";

    std::cout << "Sorting words...\n";
    std::sort(words.begin(), words.end(), WordInfo::compareWordInfos);
    std::cout << "Done\n";

    for (int i = 0; i < (words.size() < 10 ? words.size() : 10); i++) {
        std::cout << words[i]->getWord() << " - " << words[i]->getScore() << "\n";
    }

    return 0;
}