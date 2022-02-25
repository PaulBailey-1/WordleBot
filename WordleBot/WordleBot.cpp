#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <mutex>

#include "InfoCase.h"
#include "WordInfo.h"

#define THREAD_COUNT 2

std::vector<std::string>* wordList;
std::vector<WordInfo*> words;
int wordCalcIndex = 0;
std::mutex indexMux;
std::mutex wordsMux;

void threadRunner() {
    while (words.size() < wordList->size()) {

        indexMux.lock();
        int index = wordCalcIndex;
        wordCalcIndex++;
        indexMux.unlock();

        WordInfo* newWord = new WordInfo(wordList->at(index));

        wordsMux.lock();
        words.push_back(newWord);
        wordsMux.unlock();
    }
}

int main() {

    std::ifstream wordListFile("WordList.txt");
    wordList = new std::vector<std::string>();
    WordInfo::wordList = wordList;
    std::string word;

    std::cout << "Loading words...\n";
    int lim = 0;
    while (std::getline(wordListFile, word) && lim < 10) {
        wordList->push_back(word);
        lim++;
    }
    std::cout << "Done\n";

    std::vector<std::thread> workers;

    std::cout << "Computing word information...\n";
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < THREAD_COUNT; i++) {
        workers.push_back(std::thread(threadRunner));
    }
    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
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