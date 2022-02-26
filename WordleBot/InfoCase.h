#pragma once
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <iostream>

#define MAX_WORD_COUNT 13000

struct Form;

class InfoCase {

public:

	enum Case {
		PRESENT,
		NOT_PRESENT,
		NEAR
	};

	InfoCase();
	~InfoCase();
	
	void addWord(std::string word, Case data[]);
	bool checkWord(std::string test);

private:

	Form* _data[MAX_WORD_COUNT];
	int _dataCount;
};

struct Form {

	Form(char letter_, int place_, InfoCase::Case data_) :
		letter(letter_), place(place_), data(data_) {}

	char letter;
	int place;
	InfoCase::Case data;

};