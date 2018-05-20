#pragma once
#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "Dictionary.h"
#include "Puzzle.h"
#include "Board.h"
#include "Player.h"

using namespace std;

class Menu
{
public:
	
	Menu();

	bool ask_dictionary();
	bool ask_puzzle_file();
	bool ask_username();
	void menu_rules();
	
	void ask_position_and_word();

	bool give_score();

	ifstream* get_input_file();

	Puzzle* puzzle;
	Board* board;
	Dictionary* dictionary;
	Player* player;

	static void trow_error(string error);
	static void trow_error(int error);
	
	~Menu();

	ifstream* puzzle_file;

private:
	string dicitionary_file_name;
	ifstream* dictionary_file;
	string puzzle_file_name;
};

