#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <mutex>

#include "InfoCase.h"
#include "WordInfo.h"

#define THREAD_COUNT 1

std::vector<std::thread> workers;
std::vector<std::string>* wordList;
std::vector<WordInfo*> words;
int wordCalcIndex = 0;
std::mutex wordIdxMux;
std::mutex wordsMux;
std::mutex coutMux;

void threadRunner(int workerInx) {
    std::thread::id id = workers[workerInx].get_id();
    coutMux.lock();
    std::cout << "Thread started - " << id << "\n";
    coutMux.unlock();
    while (true) {

        wordsMux.lock();
        if (wordCalcIndex >= wordList->size()) {
            wordsMux.unlock();
            break;
        }
        wordsMux.unlock();

        wordIdxMux.lock();
        std::string word = wordList->at(wordCalcIndex);

        wordCalcIndex++;
        wordIdxMux.unlock();

        WordInfo* newWord = new WordInfo(word);

        wordsMux.lock();
        words.push_back(newWord);
        wordsMux.unlock();
    }
    coutMux.lock();
    std::cout << "Thread ended - " << id << "\n";
    coutMux.unlock();
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

    std::cout << "Computing word information...\n";

    for (int i = 0; i < THREAD_COUNT; i++) {
        workers.push_back(std::thread(threadRunner, i));
    }
    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }

    std::cout << "Done\n";

    std::cout << "Sorting words...\n";
    std::sort(words.begin(), words.end(), WordInfo::compareWordInfos);
    std::cout << "Done\n";

    for (int i = 0; i < (words.size() < 10 ? words.size() : 10); i++) {
        std::cout << words[i]->getWord() << " - " << words[i]->getScore() << "\n";
    }

    return 0;
}