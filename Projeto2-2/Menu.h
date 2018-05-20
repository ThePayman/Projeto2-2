#pragma once
#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "Dictionary.h"
#include "Puzzle.h"
#include "Board.h"

using namespace std;

class Menu
{
public:
	
	Menu();

	bool ask_dictionary();
	bool ask_puzzle_file();
	bool ask_username();
	void menu_rules();
	bool check_username();
	void welcome_username();
	
	void ask_position_and_word();

	ifstream* get_input_file();

	Puzzle* puzzle;
	Board* board;
	Dictionary* dictionary;

	static void trow_error(string error);
	static void trow_error(int error);
	
	~Menu();

	ifstream* puzzle_file;

private:
	string dicitionary_file_name;
	ifstream* dictionary_file;
	string puzzle_file_name;
	string username;
	vector<string> usernames;
	vector<int> usernames_scores = { 15 , 20 };
	int a = usernames.size(); //devia ser local
};

