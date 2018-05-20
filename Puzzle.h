#pragma once
#include "string"
#include "fstream"
#include "vector"
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
	Puzzle(unsigned int size_x, unsigned int size_y, string name, Dictionary* dictionary_object);
	Puzzle(unsigned int size_x, unsigned int size_y, string name, vector<puzzle_word> load_vector, Dictionary* dictionary_object);
	bool insert(puzzle_word word);
	bool insert_string(string puzzle_word_pos, string puzzle_word_string);
	bool remove(puzzle_word word);
	bool remove_string(string puzzle_word_pos, string puzzle_word_string);
	bool recreate_verify_2d_vector();
	bool check_word(puzzle_word word);
	vector<string> possible_words(string puzzle_word_pos);
	void fill();
	bool save(ofstream* output_file, Board* board);
	static std::pair<Board*, Puzzle*> load(ifstream* inputput_file, Dictionary* dictionary_object);

	static void trow_error(string error);
	static void trow_error(int error);

	vector<vector<char>> two_d_puzzle_vector;

	ifstream file;

private:
	unsigned int size_x;
	unsigned int size_y;
	string name;
	vector<puzzle_word> puzzle_word_vector;
	Dictionary* dictionary;
};

