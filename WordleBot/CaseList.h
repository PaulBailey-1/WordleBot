#pragma once
#include<string>
#include<iostream>
#include<fstream>

#include "WordList.h"

struct Case {
	std::string word;
	int validForms[FORM_COUNT];
};

class CaseList
{
public:

	static void load(std::string fileName);

	static Case caseList[WORD_COUNT];

};



