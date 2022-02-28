#pragma once
#include<string>
#include<iostream>
#include<fstream>

#include "InfoCase.h"

const int WORD_COUNT = 12971;

class WordList
{
public:
	static void load(std::string fileName, int num = INT_MAX);

	static std::string wordList[WORD_COUNT];
	static int length;
};

