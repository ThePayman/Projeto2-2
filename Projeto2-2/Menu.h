#pragma once
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "Dictionary.h"
#include "Puzzle.h"
#include "Board.h"

using namespace std;


class Menu {
public:
	Menu();

	void Selection();
	
	void ask_position_and_word();
	bool ask_puzzle_options();
	ifstream* get_input_file();
	ofstream* get_output_file();
	ofstream* get_next_output_puzzle();
	bool get_dictionary();
	bool get_board_file();
	std::pair<int,int> get_board_size();


	Puzzle* puzzle;
	Board* board;
	Dictionary* dictionary;

	~Menu();

	static void trow_error(string error);
	static void trow_error(int error);

	ifstream* board_file;

private:
	string option;
	string position;
	string word;
	string dictionary_file_name;
	ifstream* dictionary_file;
	string board_file_name;
	puzzle_word puzzle_word;
};

