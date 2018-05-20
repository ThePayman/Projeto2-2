#pragma once
#include "string"
#include "iostream"
#include "vector"
#include "map"
#include "Dictionary.h"
#include "Board.h"

using namespace std;


struct puzzle_word {
	char positionX;
	char positionY;
	char direction;
	string word_string;
};

class Puzzle {
public:
	Puzzle(int size_x, int size_y, string name, vector<puzzle_word> load_vector, vector<string> solved_puzzle_corresponding_word_vector, Dictionary* dictionary_object);
	
	bool insert(puzzle_word word, bool put_blacks);
	bool insert_string(string puzzle_word_pos, string puzzle_word_string);
	bool remove(puzzle_word word);
	bool remove_string(string puzzle_word_pos, string puzzle_word_string);

	bool recreate_verify_2d_vector();

	bool check_word(puzzle_word word);

	void show_clues();

	static std::pair<Board*, Puzzle*> load(ifstream* file, Dictionary* dictionary_object);

	vector<vector<char>> two_d_puzzle_vector;
	vector<vector<char>> two_d_puzzle_vector_blacks;

	vector<pair<puzzle_word, string>> horizontal_clues;
	vector<pair<puzzle_word, string>> vertical_clues;

private:
	int size_x;
	int size_y;
	string name;
	
	vector<puzzle_word> solved_puzzle_word_vector;
	vector<string> solved_puzzle_corresponding_word_vector;
	vector<puzzle_word> puzzle_word_vector;

	Dictionary* dictionary;
};