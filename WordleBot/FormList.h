#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

const int FORM_COUNT = 390;

enum class State {
	PRESENT,
	NOT_PRESENT,
	NEAR
};

struct Form {

	Form(char letter_, int place_, State state_) :
		letter(letter_), place(place_), state(state_) {}

	Form() : letter('a'), place(0), state(State::PRESENT) {}

	char letter;
	int place;
	State state;

};

class FormList
{
public:

	static void load(std::string fileName);

	static Form formList[FORM_COUNT];

};



