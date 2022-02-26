#include "WordInfo.h"

std::vector<std::string>*  WordInfo::wordList = nullptr;

WordInfo::WordInfo(std::string word) : _word(word), _score(0.0) {

	if (wordList == nullptr) {
		throw std::runtime_error("Error: No word list found\n");
	}

	int cases[5] = { 0, 0, 0, 0, 0 };
	while (true) {

		InfoCase info;
		info.addWord(_word, (InfoCase::Case*) cases);
		double prob = 0.0;
		for (int i = 0; i < wordList->size(); i++) {
			info.checkWord(wordList->at(i)) ? prob++ : NULL;
		}

		if (prob != 0.0) {
			prob /= wordList->size();
			prob *= -log2l(prob);
			_score += prob;
		}
		
		cases[0]++;
		for (int i = 0; i < 4; i++) {
			if (cases[i] > 2) {
				cases[i] = 0;
				cases[i+1]++;
			}
		}

		if (cases[4] == 3) {
			break;
		}
	}
}

bool WordInfo::compareWordInfos(WordInfo* w1, WordInfo* w2) {
	return w1->getScore() > w2->getScore();
}