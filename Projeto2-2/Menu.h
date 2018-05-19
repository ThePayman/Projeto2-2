#pragma once
#include "stdafx.h"
#include "iostream"
#include "string"
#include "vector"

using namespace std;

class Menu
{
public:
	
	Menu();

	bool ask_dictionary();
	bool ask_board_file_name();
	bool ask_username();
	void menu_rules();

	~Menu();

private:
	string dicitionary_name;
	string board_file_name;
	string username;
	vector<string> usernames;
};

