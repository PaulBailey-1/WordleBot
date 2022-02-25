#pragma once
#include <string>
#include <map>
#include <vector>

struct Form;

class InfoCase {

public:

	enum Case {
		PRESENT,
		NOT_PRESENT,
		NEAR
	};

	~InfoCase();
	
	void addWord(std::string word, Case data[]);
	bool checkWord(std::string test);

private:

	std::vector<Form*> _data;

};

struct Form {

	Form(char letter_, int place_, InfoCase::Case data_) :
		letter(letter_), place(place_), data(data_) {}

	char letter;
	int place;
	InfoCase::Case data;

};