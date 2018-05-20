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
	this->ask_username();
	this->welcome_username();
	//this->ask_dictionary();
	this->ask_board_file_name();
	this->menu_rules();
	board->show_board();
	
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
	return true;
}

bool Menu::check_username() {
	for (unsigned int i = 0; i < usernames.size(); i++) {
		if (username != usernames[i]) {
			a--;
		}
	}
	if (a == 0) {
		usernames.push_back(username);
		usernames_scores.push_back(0);
		return false;
	}
	return true;
}

void Menu::welcome_username() {
	if (!this->check_username()) {
		cout << "Welcome back, " << username << "!" <<endl;
		cout << endl;
		for (unsigned int i = 0; i < usernames.size(); i++) {
			if (username == usernames[i]) {
				cout << "Your score is: " << usernames_scores[i] << "." << endl;
				cout << endl;
			}
		}
	}
	if (this->check_username()){
		cout << "Welcome, " << username << "!" << endl;
		cout << endl;
		cout << "Your score is: " << 0 << "." << endl;
		cout << endl;
	}
}

void Menu::menu_rules() {
	cout << endl
	<< "================================" << endl
	<< endl
	<< "RULES:" << endl
	<<endl
	<<"1 - To declare a position you must use the letters for the specifc line and column and the direction with a V for vertical and a H for horizontal." <<endl
	<<endl
	<< "2 - You must finish the puzzle in order to see if you have sucessfully guessed all the words" <<endl
	<< endl
	<< "================================" << endl;
}

Menu::~Menu()
{
}
