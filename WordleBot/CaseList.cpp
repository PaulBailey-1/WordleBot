#include "CaseList.h"

#include "WordList.h"

Case CaseList::caseList[WORD_COUNT];

void CaseList::load(std::string fileName, bool reload) {

    std::ifstream caseListFileIn(fileName);

    if(!caseListFileIn.good() || reload) {

        std::cout << "Creating Cases...\n";

		caseListFileIn.close();
        std::ofstream caseListFileOut(fileName);

		for (int i = 0; i < WordList::length; i++) {

			std::string word = WordList::wordList[i];
            caseListFileOut << "-\n" << word << "\n";

			for (int formIdx = 0; formIdx < FORM_COUNT; formIdx++) {

				Form form = FormList::formList[formIdx];
				bool valid = true;

				switch (form.state) {
					case State::PRESENT:
						if (word[form.place] != form.letter) {
							valid = false;
						}
						break;
					case State::NOT_PRESENT:
						for (unsigned int i = 0; i < word.length(); i++) {
							if (word[i] == form.letter) {
								valid = false;
							}
						}
						break;
					case State::NEAR:
						if (word[form.place] == form.letter) {
							valid = false;
						}
						bool present = false;
						for (unsigned int i = 0; i < word.length(); i++) {
							if (word[i] == form.letter) {
								present = true;
							}
						}
						if (!present) {
							valid = false;
						}
						break;
				}
				if (valid) {
					caseListFileOut << formIdx << "\n";
				}
			}
        }
        caseListFileOut.close();
		caseListFileIn.open(fileName);
    }

	std::cout << "Loading Cases...\n";

	std::string line;
	int caseIdx = 0;

	std::getline(caseListFileIn, line);

	while (std::getline(caseListFileIn, line)) {

		Case aCase;
		aCase.word = line;
		int formIdx = 0;

		while (std::getline(caseListFileIn, line) && line != "-") {
			aCase.validForms[formIdx] = stoi(line);
			formIdx++;
		}

		aCase.validFormCount = formIdx;
		caseList[caseIdx] = aCase;
		caseIdx++;
	}

	caseIdx < WordList::length ? throw std::runtime_error("Case data invalid") : NULL;

    caseListFileIn.close();
    std::cout << "Done\n";
}