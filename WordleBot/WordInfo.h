#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "InfoCase.h"
#include "WordList.h"
#include "FormList.h"

class WordInfo {

public:

	WordInfo(std::string word);

	static void generateCases();

	double getScore() { return _score; }

	std::string getWord() { return _word; }

	static bool compareWordInfos(WordInfo* w1, WordInfo* w2);

private:

	static int cases[243][5];

	std::string _word;
	double _score;

};

