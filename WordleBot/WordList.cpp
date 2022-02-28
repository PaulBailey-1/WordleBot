#include "WordList.h"

std::string WordList::wordList[WORD_COUNT];
int WordList::length;

void WordList::load(std::string fileName, int num) {
    std::cout << "Loading words...\n";
    std::ifstream wordListFile(fileName);
    std::string word;
    int i = 0;
    while (std::getline(wordListFile, word) && i < num) {
        wordList[i] = word;
        i++;
    }
    length = i;
    wordListFile.close();
    std::cout << "Done\n";
}