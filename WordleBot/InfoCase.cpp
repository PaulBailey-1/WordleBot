#include "InfoCase.h"

InfoCase::InfoCase() {
	_dataCount = 0;
}

InfoCase::~InfoCase() {
	for (int i = 0; i < _dataCount; i++) {
		free(_data[i]);
	}
}

void InfoCase::addWord(std::string word, Case data[]) {
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < word.length(); i++) {
		_data[_dataCount] = new Form(word[i], i, data[i]);
		_dataCount++;
	}
	auto end = std::chrono::high_resolution_clock::now();
	double time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << time << "\n";
}

bool InfoCase::checkWord(std::string test) {

	for (int i = 0; i < _dataCount; i++) {
		Form* form = _data[i];
		switch (form->data) {
			case PRESENT:
				if (test[form->place] != form->letter) {
					return false;
				}
				break;
			case NOT_PRESENT:
				for (int i = 0; i < test.length(); i++) {
					if (test[i] == form->letter) {
						return false;
					}
				}
				break;
			case NEAR:
				if (test[form->place] == form->letter) {
					return false;
				}
				bool present = false;
				for (int i = 0; i < test.length(); i++) {
					if (test[i] == form->letter) {
						present = true;
					}
				}
				if (!present) {
					return false;
				}
				break;
		}
	}
	return true;
}