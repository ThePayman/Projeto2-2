#pragma once
#include "stdafx.h"
#include "iostream"
#include "string"
#include "vector"
#include "Board.h"

using namespace std;

class Menu
{
public:

	Menu();

	bool ask_dictionary();
	bool ask_board_file_name();
	bool ask_username();
	void menu_rules();
	bool check_username();
	void welcome_username();

	~Menu();

private:
	string dicitionary_name;
	string board_file_name;
	string username;
	vector<string> usernames = { "Afoxys","ThePayman" };
	vector<int> usernames_scores = { 15 , 20 };
	Board *board;
	int a = usernames.size();

};

