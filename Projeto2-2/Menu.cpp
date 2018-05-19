#include "stdafx.h"
#include "Menu.h"


Menu::Menu(){
	cout << "================================" << endl;
	cout << endl;
	cout << "      CROSSWORD PUZZLE" << endl;
	cout << endl;
	cout << "================================" << endl;
	cout << endl;
	cout << endl;
	this->ask_dictionary();
	this->ask_board_file_name();
	this->ask_username();
}

bool Menu::ask_dictionary() {
	cout << "What is the dictionary file?" << endl;
	cin >> dicitionary_name;
	return true;
}

bool Menu::ask_board_file_name() {
	cout << "What is the board file?" << endl;
	cin >> board_file_name;
	return true;
}

bool Menu::ask_username() {
	cout << "What is your username?" << endl;
	cin >> username;
	//criar um vetor de usernames com o numero de puzzles já completos (pode ficar isto o nosso score)
	/*if (username not in usernames){
		usernames.push_back(username)
	}*/
	return true;
}

void Menu::menu_rules() {
	cout << endl
	<< "================================" << endl
	<< endl
	<< "RULES:"
	<<"1 - " <<endl
	<< "" <<endl
	<< "" <<endl
	<< endl
	<< "================================" << endl;
}

Menu::~Menu()
{
}
