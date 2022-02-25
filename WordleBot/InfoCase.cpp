#include "InfoCase.h"

InfoCase::~InfoCase() {
	for (Form* form : _data) {
		free(form);
	}
}

void InfoCase::addWord(std::string word, Case data[]) {
	for (int i = 0; i < word.length(); i++) {
		_data.push_back(new Form(word[i], i, data[i]));
	}
}

bool InfoCase::checkWord(std::string test) {

	for (int i = 0; i < _data.size(); i++) {
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