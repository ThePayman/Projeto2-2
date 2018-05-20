#include "stdafx.h"
#include "Menu.h"
#include "Board.h"
#include "Dictionary.h"
#include "Puzzle.h"


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
	this->ask_dictionary();
	this->ask_puzzle_file();
	pair<Board*, Puzzle*> board_puzzle_loaded_pair = Puzzle::load(puzzle_file, dictionary);
	board = board_puzzle_loaded_pair.first;
	puzzle = board_puzzle_loaded_pair.second;
	this->menu_rules();
	board->update_board(puzzle->two_d_puzzle_vector);
	board->show_board();
	this->ask_position_and_word();
}

bool Menu::ask_dictionary() {
	string dictionary_file_name;
	cout << "What is the dictionary file name?" << endl;
	cin >> dictionary_file_name;
	dictionary_file = new ifstream();
	dictionary_file->open(dictionary_file_name);
	if (!dictionary_file->is_open()) {
		cout << "Invalid File" << endl;
		return this->ask_dictionary();
	}
	dictionary = new Dictionary(dictionary_file, dictionary_file_name);
	return true;
}


bool Menu::ask_puzzle_file() {
	string file_name;
	cout << "What is the puzzle file?" << endl;
	cin >> file_name;
	ifstream* file = new ifstream();
	file->open(file_name);
	if (!file->is_open()) {
		cout << "Invalid File" << endl;
		return this->get_input_file();
	}
	puzzle_file = file;
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
		cout << "Welcome back, " << username << "!" << endl;
		cout << endl;
		for (unsigned int i = 0; i < usernames.size(); i++) {
			if (username == usernames[i]) {
				cout << "Your score is: " << usernames_scores[i] << "." << endl;
				cout << endl;
			}
		}
	}
	if (this->check_username()) {
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

void Menu::ask_position_and_word() {
	string position = "";
	string word;
	while (!cin.eof()) {
		puzzle->show_clues();
		cout << "Position (LCD / CTRL-Z = stop)   ?" << endl;
		cin >> position;
		if (position.size() != 3) {
			Menu::trow_error("Invalid input, please input a valid position. Incorrect length.");
			this->ask_position_and_word();
		}
		if (!(('a' <= position[0] && position[0] <= 'z') && ('A' <= position[1] && position[1] <= 'Z') && (position[2] == 'V' || position[2] == 'H'))) {
			Menu::trow_error("Invalid input, please input a valid position. Incorrect format.");
			this->ask_position_and_word();
		}
		cout << "Word ( - = remove / ? = help)   ?" << endl;
		cin >> word;
		if (cin.eof()) continue;
		for (int i = 0; i < word.size(); i++) {
			word[i] = toupper(word[i]);
		}
		if (word[0] == '-') puzzle->remove_string(position, word.substr(1, word.size() - 1));
		else if (word[0] == '?') {
			/*
			vector<string> possible_words = puzzle->possible_words(position);
			cout << "Possible words for position " << position << ": " << endl;
			for (const string word : possible_words) {
				cout << word << endl;
			}*/
		}
		else puzzle->insert_string(position, word);
		board->update_board(puzzle->two_d_puzzle_vector);
		board->show_board();
	}
	cin.clear();
	//this->ask_puzzle_options();
}

ifstream* Menu::get_input_file() {
	string file_name;
	cout << "What is the file name?" << endl;
	cin >> file_name;
	ifstream* file = new ifstream();
	file->open(file_name);
	if (!file->is_open()) {
		cout << "Invalid File" << endl;
		return this->get_input_file();
	}
	return file;
}


void Menu::trow_error(string error) {
	cout << error << endl;
}
void Menu::trow_error(int error = 0) {
	if (error == 0) {
		cout << "An undefined error has occurred." << endl;
	}
	switch (error)
	{
	case 1:
		cout << "Something went horribly wrong. This error should not happen." << endl;
		break;
	default:
		break;
	}
}

Menu::~Menu()
{
}
