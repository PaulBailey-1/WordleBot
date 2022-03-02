#include "WordInfo.h"

WordInfo::WordInfo(std::string word) : _word(word), _score(0.0) {
	if (WordList::wordList == nullptr) {
		throw std::runtime_error("Error: No word list found\n");
	}

	int cases[5] = { 0, 0, 0, 0, 0 };
	double count = 0;
	while (true) {

		InfoCase info;
		info.addWord(_word, (State*) cases);
		double prob = 0.0;
		for (int i = 0; i < WordList::length; i++) {
			info.checkWord(i) ? prob++ : NULL;
		}
		count += prob;

		if (prob != 0.0) {
			prob /= WordList::length;
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