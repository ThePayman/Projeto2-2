#include "stdafx.h"
#include "Puzzle.h"

Puzzle::Puzzle(int set_size_x, int set_size_y, string set_name, vector<puzzle_word> load_vector, vector<string> puzzle_corresponding_word_vector) {
	size_x = set_size_x;
	size_y = set_size_y;
	name = set_name;
	for (int x = 0; x < set_size_x; x++) {
		vector<char> y_vector;
		for (int y = 0; y < set_size_y; y++) {
			y_vector.push_back(' ');
		}
		two_d_puzzle_vector.push_back(y_vector);
	}
	solved_puzzle_word_vector = load_vector;
	solved_puzzle_corresponding_word_vector = puzzle_corresponding_word_vector;
}
bool Puzzle::insert(puzzle_word word) {
	for (const puzzle_word solved_puzzle_word : solved_puzzle_word_vector) {
		if (word.positionX == solved_puzzle_word.positionX && word.positionY == solved_puzzle_word.positionY && word.direction == solved_puzzle_word.direction && word.word_string == solved_puzzle_word.word_string) {
			puzzle_word_vector.push_back(word);
			this->recreate_verify_2d_vector();
			return true;
		}
	}
	return false;	
}

bool Puzzle::recreate_verify_2d_vector() {
	two_d_puzzle_vector = {};
	for (const puzzle_word new_puzzle_word : puzzle_word_vector) {
		int x_index = new_puzzle_word.positionX - 'a';
		int y_index = new_puzzle_word.positionY - 'A';
		for (int i = 0; i < new_puzzle_word.word_string.size(); i++) {
			two_d_puzzle_vector[x_index][y_index] = new_puzzle_word.word_string[i];
			if (new_puzzle_word.direction == 'H') x_index++;
			else if (new_puzzle_word.direction == 'V') y_index++;
		}
	}
	return true;
}

Puzzle Puzzle::load(istream file, string dictionary_file_name, multimap<string, string> dictionary_mmap) {
	string word;
	int i = 0;
	int size_x = 0;
	int size_y = 0;
	bool getting_2d_puzzle = false;
	bool getting_puzzle_words = false;
	vector<puzzle_word> loaded_puzzle_words;
	vector<string> solved_puzzle_corresponding_word_vector;
	string dictionary_file;
	for (string line; getline(file, line); )
	{
		if (i == 0) {
			dictionary_file = line;
			if (dictionary_file != dictionary_file_name) {
				cout << "Loaded Dictionary File might be different from the one used to generate this puzzle. This can result in unexpected problems." << endl;
			}
		}
		else {
			if (!line.empty()) {
				if (getting_2d_puzzle) {
					if (size_x == 0) {
						for (const char string_char : line) {
							if (string_char != ' ') size_x++;
						}
					}
					size_y++;
				}
				if (getting_puzzle_words) {
					puzzle_word new_puzzle_word;
					vector<string> synonym;
					new_puzzle_word.positionY = line[0];
					new_puzzle_word.positionX = line[1];
					new_puzzle_word.direction = line[2];
					new_puzzle_word.word_string = line.substr(4, line.size() - 4);
					for (auto itr = dictionary_mmap.begin(); itr != dictionary_mmap.end(); itr++) {
						if (itr->first == new_puzzle_word.word_string) {
							synonym.push_back(itr->second);
						}
					}
					int random_index = rand() % synonym.size();

					solved_puzzle_corresponding_word_vector.push_back(synonym[random_index]);
					loaded_puzzle_words.push_back(new_puzzle_word);
				}
			}
			else {
				if (!getting_2d_puzzle && !getting_puzzle_words) getting_2d_puzzle = true;
				else if (getting_2d_puzzle && !getting_puzzle_words) {
					getting_2d_puzzle = false;
					getting_puzzle_words = true;
				}
				else if (!getting_2d_puzzle && getting_puzzle_words) {
					getting_puzzle_words = false;
				}
			}
		}
		i++;
	}
	Puzzle new_puzzle = Puzzle(size_x, size_x, "Puzzle", loaded_puzzle_words, solved_puzzle_corresponding_word_vector);
	return (new_puzzle);
}
