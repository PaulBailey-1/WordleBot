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

	double getScore() { return _score; }

	std::string getWord() { return _word; }

	static bool compareWordInfos(WordInfo* w1, WordInfo* w2);

private:

	std::string _word;
	double _score;

};

