#pragma once
#include<string>
#include<iostream>
#include<fstream>

#include "WordList.h"

struct Case {
	Case() : validForms{0} {}
	std::string word;
	int validForms[FORM_COUNT];
	int validFormCount;
};

class CaseList
{
public:

	static void load(std::string fileName);

	static Case caseList[WORD_COUNT];

};



