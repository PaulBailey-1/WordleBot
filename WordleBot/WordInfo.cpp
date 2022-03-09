#include "WordInfo.h"

int WordInfo::cases[243][5];

WordInfo::WordInfo(std::string word) : _word(word), _score(0.0) {

	double prob = 0.0;

	InfoCase info;

	double time1 = 0.0;

	for (int i = 0; i < 243; i++) {

		info.clear();
		prob = 0.0;
		info.addWord(_word, (State*) cases[i]);

		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < WordList::length; i++) {
			info.checkWord(i) ? prob++ : NULL;
		}

		auto end = std::chrono::high_resolution_clock::now();
		time1 += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		if (prob != 0.0) {
			prob /= WordList::length;
			prob *= -log2l(prob);
			_score += prob;
		}

	}

	time1 /= 243;

	std::cout << time1 << "\n";
}

void WordInfo::generateCases() {

	for (int i = 0; i < 5; i++) {
		cases[0][i] = 0;
	}

	for (int i = 1; i < 243; i++) {

		for (int j = 0; j < 5; j++) {
			cases[i][j] = cases[i-1][j];
		}

		cases[i][0]++;
		for (int j = 0; j < 4; j++) {
			if (cases[i][j] > 2) {
				cases[i][j] = 0;
				cases[i][j + 1]++;
			}
		}
	}
}

bool WordInfo::compareWordInfos(WordInfo* w1, WordInfo* w2) {
	return w1->getScore() > w2->getScore();
}