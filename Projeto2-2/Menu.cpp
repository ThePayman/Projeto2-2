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
	//TODO:
	//criar um vetor de usernames com o numero de puzzles já completos (pode ficar isto o nosso score)
	/*if (username not in usernames){
		usernames.push_back(username)
	}*/
	return true;
}

void Menu::welcome_username() {
	//se o username já existir mostrar o score dele, se não existir mostrar 0
	//cout << endl;
	//cout << "Welcome, " << username << endl;
	//cout << Your score is: " << usernames[x_coorespondente_username][1];
	//cout << endl;
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
