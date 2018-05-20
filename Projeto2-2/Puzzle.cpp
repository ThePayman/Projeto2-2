#include "stdafx.h"
#include "Puzzle.h"

Puzzle::Puzzle(int set_size_x, int set_size_y, string set_name, vector<puzzle_word> load_vector, vector<string> puzzle_corresponding_word_vector, Dictionary* dictionary_object) {
	size_x = set_size_x;
	size_y = set_size_y;
	name = set_name;
	dictionary = dictionary_object;
	for (int x = 0; x < set_size_x; x++) {
		vector<char> y_vector;
		for (int y = 0; y < set_size_y; y++) {
			y_vector.push_back('.');
		}
		two_d_puzzle_vector.push_back(y_vector);
	}
	for (int i = 0; i < load_vector.size(); i++) {
		puzzle_word word = load_vector[i];
		this->insert(word,true);
	}
	two_d_puzzle_vector_blacks = two_d_puzzle_vector;
	for (int x = 0; x < size_x; x++) {
		for (int y = 0; y < size_y; y++) {
			if (two_d_puzzle_vector_blacks[x][y] != '.' && two_d_puzzle_vector_blacks[x][y] != '#') {
				two_d_puzzle_vector_blacks[x][y] = '.';
			}
		}
	}
	two_d_puzzle_vector = two_d_puzzle_vector_blacks;
	solved_puzzle_word_vector.clear();
	for (int i = 0; i < load_vector.size(); i++) {
		puzzle_word word = load_vector[i];
		if (word.word_string != "#") {
			solved_puzzle_word_vector.push_back(load_vector[i]);
		}
	}
	solved_puzzle_corresponding_word_vector = puzzle_corresponding_word_vector;

	for (int i = 0; i < solved_puzzle_word_vector.size(); i++) {
		pair<puzzle_word, string> clue_pair(solved_puzzle_word_vector[i], solved_puzzle_corresponding_word_vector[i]); //erro
		if (solved_puzzle_word_vector[i].direction == 'H') horizontal_clues.push_back(clue_pair);
		else vertical_clues.push_back(clue_pair);
	}
}

/*
Inserts a new word 
*/
bool Puzzle::insert(puzzle_word word, bool put_blacks) {
	int x_index = word.positionX - 'a';
	int y_index = word.positionY - 'A';
	if (!fits_solved(word) && !put_blacks) {
		return false;
	}
	if (!check_word(word)) {
		return false;
	}
	vector<vector<char>> new_two_d_puzzle_vector = two_d_puzzle_vector;
	if (put_blacks) {
		if (word.direction == 'H') {
			if (x_index - 1 >= 0) if (new_two_d_puzzle_vector[x_index - 1][y_index] == '.') new_two_d_puzzle_vector[x_index - 1][y_index] = '#';
			if (x_index + word.word_string.size() < size_x) if (new_two_d_puzzle_vector[x_index + word.word_string.size()][y_index]) new_two_d_puzzle_vector[x_index + word.word_string.size()][y_index] = '#';
		}
		if (word.direction == 'V') {
			if (y_index - 1 >= 0) if (new_two_d_puzzle_vector[x_index][y_index - 1] == '.') new_two_d_puzzle_vector[x_index][y_index - 1] = '#';
			if (y_index + word.word_string.size() < size_y) if (new_two_d_puzzle_vector[x_index][y_index + word.word_string.size()]) new_two_d_puzzle_vector[x_index][y_index + word.word_string.size()] = '#';
		}
	}
	for (int i = 0; i < word.word_string.size(); i++) {
		char selected_vector_position = new_two_d_puzzle_vector[x_index][y_index];

		if (selected_vector_position != word.word_string[i] && selected_vector_position != '.') {
			return false;
		}
		else {
			new_two_d_puzzle_vector[x_index][y_index] = word.word_string[i];
		}
		if (word.direction == 'V') y_index++;
		else if (word.direction == 'H') x_index++;
	}

	two_d_puzzle_vector = new_two_d_puzzle_vector;
	puzzle_word_vector.push_back(word);
	return true;
}

bool Puzzle::insert_string(string puzzle_word_pos, string puzzle_word_string) {
	puzzle_word new_puzzle_word;
	new_puzzle_word.positionX = puzzle_word_pos[0];
	new_puzzle_word.positionY = puzzle_word_pos[1];
	new_puzzle_word.direction = puzzle_word_pos[2];
	new_puzzle_word.word_string = puzzle_word_string;
	this->insert(new_puzzle_word, false);
	return true;
}

bool Puzzle::remove(puzzle_word word) {
	for (int i = 0; i < puzzle_word_vector.size(); i++) {
		if (word.direction == puzzle_word_vector[i].direction && word.positionX == puzzle_word_vector[i].positionX && word.positionY == puzzle_word_vector[i].positionY && word.word_string == puzzle_word_vector[i].word_string) {
			puzzle_word_vector.erase(puzzle_word_vector.begin() + i);
		}
	}
	this->recreate_verify_2d_vector();
	return true;
}

bool Puzzle::remove_string(string puzzle_word_pos, string puzzle_word_string) {
	puzzle_word new_puzzle_word;
	new_puzzle_word.positionX = puzzle_word_pos[0];
	new_puzzle_word.positionY = puzzle_word_pos[1];
	new_puzzle_word.direction = puzzle_word_pos[2];
	new_puzzle_word.word_string = puzzle_word_string;
	this->remove(new_puzzle_word);
	return true;
}

bool Puzzle::recreate_verify_2d_vector() {
	two_d_puzzle_vector = two_d_puzzle_vector_blacks;
	for (int x = 0; x < size_x; x++) {
		vector<char> y_vector;
		for (int y = 0; y < size_y; y++) {
			y_vector.push_back('.');
		}
		two_d_puzzle_vector.push_back(y_vector);
	}
	vector<puzzle_word> existing_puzzle_words = puzzle_word_vector;
	puzzle_word_vector.clear();
	for (const puzzle_word new_puzzle_word : existing_puzzle_words) {
		this->insert(new_puzzle_word, false);
	}
	return true;
}

bool Puzzle::check_word(puzzle_word word) {
	unsigned int x_index = word.positionX - 'a';
	unsigned int y_index = word.positionY - 'A';
	if (word.direction == 'H') {
		if (x_index + word.word_string.size() > size_x) {
			return false;
		}
	}
	if (word.direction == 'V') {
		if (y_index + word.word_string.size() > size_y) {
			return false;
		}
	}
	for (int i = 0; i < word.word_string.size(); i++) {
		char selected_vector_position = two_d_puzzle_vector[x_index][y_index];
		if (selected_vector_position != word.word_string[i] && selected_vector_position != '.') {
			return false;
		}
		if (word.direction == 'H') x_index++;
		else if (word.direction == 'V') y_index++;
	}
	if (word.word_string == "#") return true;
	for (const string dictionary_word : dictionary->usable_words) {
		if (dictionary_word == word.word_string) return true;
	}
	return false;
}

bool Puzzle::fits_solved(puzzle_word word) {
	for (const puzzle_word solved_word : solved_puzzle_word_vector) {
		if (word.positionX == solved_word.positionX && word.positionY == solved_word.positionY && word.direction == solved_word.direction) {
			if (solved_word.word_string.size() == word.word_string.size()) return true;
		}
		if (word.word_string == solved_word.word_string) return false;
	}
	return false;
}

void Puzzle::show_clues() {
	cout << "Horizontal Words: " << endl;
	for (const pair<puzzle_word,string> clue : horizontal_clues) {
		cout << clue.first.positionX << clue.first.positionY << clue.first.direction << " - " << clue.second << endl;
	}
	cout << endl << endl;
	cout << "Vertical Words: " << endl;
	for (const pair<puzzle_word, string> clue : vertical_clues) {
		cout << clue.first.positionX << clue.first.positionY << clue.first.direction << " - " << clue.second << endl;
	}
}

bool Puzzle::check_if_complete() {
	if (puzzle_word_vector.size() == solved_puzzle_word_vector.size()) return true;
}

int Puzzle::puzzle_correctly_filled() {
	int amount_correct = 0;
	bool all_correct = true;
	for (const puzzle_word solved_puzzle_word : solved_puzzle_word_vector) {
		bool found_in_solved = false;
		for (const puzzle_word try_puzzle_word : puzzle_word_vector) {
			if (try_puzzle_word.positionX == solved_puzzle_word.positionX && try_puzzle_word.positionY == solved_puzzle_word.positionY && try_puzzle_word.direction == solved_puzzle_word.direction && try_puzzle_word.word_string == solved_puzzle_word.word_string) {
				found_in_solved = true;
			}
		}
		if (found_in_solved) {
			amount_correct++;
		}
		else {
			all_correct = false;
		}
	}
	return amount_correct;
}

pair<Board*, Puzzle*> Puzzle::load(ifstream* file, Dictionary* dictionary_object) {
	string word;
	int i = 0;
	int size_x = 0;
	int size_y = 0;
	bool getting_2d_puzzle = false;
	bool getting_puzzle_words = false;
	vector<puzzle_word> loaded_puzzle_words; //Placed in the correct places
	vector<string> solved_puzzle_corresponding_word_vector;
	string dictionary_file;
	for (string line; getline(*file, line); )
	{
		if (i == 0) {
			dictionary_file = line;
			if (dictionary_file != dictionary_object->dictionary_file_name) {
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
					//Creates a vector with the synonyms of a word
					puzzle_word new_puzzle_word;
					vector<string> synonym;
					new_puzzle_word.positionX = line[0];
					new_puzzle_word.positionY = line[1];
					new_puzzle_word.direction = line[2];
					new_puzzle_word.word_string = line.substr(4, line.size() - 4);
					for (auto itr = dictionary_object->dictionary_mmap.begin(); itr != dictionary_object->dictionary_mmap.end(); itr++) {
						if (itr->first == new_puzzle_word.word_string) {
							synonym.push_back(itr->second);
						}
					}
					if (synonym.size() > 0) {
						int random_index = rand() % synonym.size();

						solved_puzzle_corresponding_word_vector.push_back(synonym[random_index]);
						loaded_puzzle_words.push_back(new_puzzle_word);
					}
					if (new_puzzle_word.word_string == "#") {
						loaded_puzzle_words.push_back(new_puzzle_word);
					}
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
	size_y--;
	Board* board = new Board(size_y, size_x);
	Puzzle* new_puzzle = new Puzzle(size_x, size_y, "Puzzle", loaded_puzzle_words, solved_puzzle_corresponding_word_vector, dictionary_object);
	pair<Board*, Puzzle*> board_puzzle_pair(board, new_puzzle);
	return board_puzzle_pair;
}
