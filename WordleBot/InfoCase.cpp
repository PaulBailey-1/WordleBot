#include "InfoCase.h"

#include "CaseList.h"

InfoCase::InfoCase() : _formCount(0), _forms{0} {}

void InfoCase::addWord(std::string word, State data[]) {
	for (unsigned int i = 0; i < word.length(); i++) {
		_forms[_formCount] = (word[i] - 'a') * 15 + i * 3 + (int) data[i];
		_formCount++;
	}
}

bool InfoCase::checkWord(int testIdx) {

	Case testCase = CaseList::caseList[testIdx];
	int formIdx = 0;

	for (int i = 0; i < testCase.validFormCount; i++) {
		if (_forms[formIdx] == testCase.validForms[i]) {
			formIdx++;
		}
	}

	if (formIdx == _formCount) {
		return true;
	}

	return false;
}