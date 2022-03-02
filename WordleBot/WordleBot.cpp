#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <mutex>

#include "FormList.h"
#include "InfoCase.h"
#include "WordInfo.h"
#include "WordList.h"
#include "CaseList.h"

const int THREAD_COUNT = 1;

std::thread workers[THREAD_COUNT];
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
        if (wordCalcIndex >= WordList::length) {
            wordsMux.unlock();
            break;
        }
        wordsMux.unlock();

        wordIdxMux.lock();
        std::string word = WordList::wordList[wordCalcIndex];

        wordCalcIndex++;
        wordIdxMux.unlock();

        auto start = std::chrono::high_resolution_clock::now();

        WordInfo* newWord = new WordInfo(word);

        auto end = std::chrono::high_resolution_clock::now();
        double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << time << "\n";

        wordsMux.lock();
        words.push_back(newWord);
        wordsMux.unlock();
    }
    coutMux.lock();
    std::cout << "Thread ended - " << id << "\n";
    coutMux.unlock();
}

int main() {

    WordList::load("WordList.txt", 10);
    FormList::load("FormList.txt");
    CaseList::load("CaseList.txt");

    std::cout << "Computing word information...\n";

    for (int i = 0; i < THREAD_COUNT; i++) {
        workers[i] = std::thread(threadRunner, i);
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