#include "InfoCase.h"

InfoCase::InfoCase() {
	_dataCount = 0;
}

InfoCase::~InfoCase() {
	for (int i = 0; i < _dataCount; i++) {
		free(_data[i]);
	}
}

void InfoCase::addWord(std::string word, State data[]) {
	for (int i = 0; i < word.length(); i++) {
		_data[_dataCount] = new Form(word[i], i, data[i]);
		_dataCount++;
	}
}

bool InfoCase::checkWord(std::string test) {
	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < MAX_FORMS; i++) {
		Form* form = _data[i];
		switch (form->state) {
			case State::PRESENT:
				if (test[form->place] != form->letter) {
					return false;
				}
				break;
			case State::NOT_PRESENT:
				for (int i = 0; i < test.length(); i++) {
					if (test[i] == form->letter) {
						return false;
					}
				}
				break;
			case State::NEAR:
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
	auto end = std::chrono::high_resolution_clock::now();
	double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	std::cout << time << "\n";

	return true;
}