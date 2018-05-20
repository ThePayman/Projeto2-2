#pragma once
#include "string"

using namespace std;

class Player
{
public:
	Player(string name);
	~Player();

	string name;
	int start_time;
	int end_time;
	int points;

	int clues_given;

	int seconds_taken();
	void set_score();
};

