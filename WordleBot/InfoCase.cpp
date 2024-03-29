#include <algorithm>

#include "InfoCase.h"
#include "CaseList.h"

InfoCase::InfoCase() : _formCount(0), _forms{0} {}

void InfoCase::addWord(std::string word, State data[]) {
	for (unsigned int i = 0; i < word.length(); i++) {
		_forms[_formCount] = (word[i] - 'a') * 15 + i * 3 + (int) data[i];
		_formCount++;
	}
	std::sort(_forms, _forms + _formCount);
}

void InfoCase::clear() {
	_formCount = 0;
}

bool InfoCase::checkWord(int testIdx) {

	static Case* testCase;
	testCase = &CaseList::caseList[testIdx];
	int formIdx = 0;

	for (int i = 0; i < testCase->validFormCount; i++) {

		if (_forms[formIdx] == testCase->validForms[i]) {
			formIdx++;
		}

		if (formIdx == _formCount) {
			return true;
		}
	}

	return false;
}