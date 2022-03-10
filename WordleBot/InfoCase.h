#pragma once
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <iostream>

#include "FormList.h"

const int MAX_FORMS = 10;

class InfoCase {

public:

	InfoCase();
	
	void addWord(std::string word, State data[]);
	void clear();

	bool checkWord(int testIdx);

private:

	int _forms[MAX_FORMS];
	int _formCount;

};