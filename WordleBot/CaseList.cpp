#include "CaseList.h"

#include "WordList.h"

//Case CaseList::caseList[WORD_COUNT];

void CaseList::load(std::string fileName) {
    std::ifstream caseListFileIn(fileName);
    if (caseListFileIn.good()) {
        std::cout << "Loading Cases...\n";
        std::string line;
        int caseIdx = 0;
        std::getline(caseListFileIn, line);
        while (std::getline(caseListFileIn, line)) {
            Case aCase;
            aCase.word = line;
            int formIdx = 0;
            while (std::getline(caseListFileIn, line) && !line.compare("-")) {
                aCase.validForms[formIdx] = stoi(line);
                formIdx++;
            }
            caseList[caseIdx] = aCase;
            caseIdx++;
        }
        caseIdx < WORD_COUNT ? throw std::runtime_error("Case data invalid") : NULL;
    }
    else {
        std::cout << "Creating Cases...\n";
        std::ofstream caseListFile(fileName);
        for (std::string word : WordList::wordList) {
            caseListFile << "-\n" << word << "\n";
        }
        caseListFile.close();
    }

    caseListFileIn.close();
    std::cout << "Done\n";
}