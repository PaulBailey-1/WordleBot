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
	~InfoCase();
	
	void addWord(std::string word, State data[]);
	bool checkWord(std::string test);

private:

	Form* _data[MAX_FORMS];
	int _dataCount;
};