#include "stdafx.h"
#include "Puzzle.h"
#include "Dictionary.h"

Puzzle::Puzzle(unsigned int set_size_x, unsigned int set_size_y, string set_name, Dictionary* dictionary_object) {
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
}
Puzzle::Puzzle(unsigned int set_size_x, unsigned int set_size_y, string set_name, vector<puzzle_word> load_vector, Dictionary* dictionary_object) {
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
		this->insert(word);
	}
}
/*
Inserts an word into the puzzle's puzzle_word vector and two dimentional vector.
Param: puzzle_word word - The instance of puzzle_word struct to be added to the puzzle. 
*/
bool Puzzle::insert(puzzle_word word) {
	int x_index = word.positionX - 'a';
	int y_index = word.positionY - 'A';
	if (!check_word(word)) {
		Puzzle::trow_error("Word doesnt fit into the given position");
		return false;
	}
	vector<vector<char>> new_two_d_puzzle_vector = two_d_puzzle_vector;
	if (word.direction == 'H') {
		if (x_index - 1 >= 0) if (new_two_d_puzzle_vector[x_index - 1][y_index] == '.') new_two_d_puzzle_vector[x_index - 1][y_index] = '#';
		if (x_index + word.word_string.size() < size_x) if (new_two_d_puzzle_vector[x_index + word.word_string.size()][y_index]) new_two_d_puzzle_vector[x_index + word.word_string.size()][y_index] = '#';
	}
	if (word.direction == 'V') {
		if (y_index - 1 >= 0) if (new_two_d_puzzle_vector[x_index][y_index - 1] == '.') new_two_d_puzzle_vector[x_index][y_index - 1] = '#';
		if (y_index + word.word_string.size() < size_y) if (new_two_d_puzzle_vector[x_index][y_index + word.word_string.size()]) new_two_d_puzzle_vector[x_index][y_index + word.word_string.size()] = '#';
	}
	for (int i = 0; i < word.word_string.size(); i++) {
		char selected_vector_position = new_two_d_puzzle_vector[x_index][y_index];

		if (selected_vector_position != word.word_string[i] && selected_vector_position != '.') { 
			Puzzle::trow_error(1);
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

/*
Inserts a word into the puzzle's puzzle_word vector and two dimentional vector.

Param: string puzzle_word_pos - A string of lenght 3 containing the X, Y and Direction of the word to insert.
	   string puzzle_word_pos - The string to insert.
*/
bool Puzzle::insert_string(string puzzle_word_pos, string puzzle_word_string) {
	puzzle_word new_puzzle_word;
	new_puzzle_word.positionX = puzzle_word_pos[0];
	new_puzzle_word.positionY = puzzle_word_pos[1];
	new_puzzle_word.direction = puzzle_word_pos[2];
	new_puzzle_word.word_string = puzzle_word_string;
	this->insert(new_puzzle_word);
	return true;
}


/*
Removes a puzzle_word from the puzzle's puzzle_word vector and the two dimentional vector.
Param: puzzle_word word - The puzzle_word struct to be removed to the puzzle. 
*/
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

/*
Recreates the two dimentional vector using the puzzle_word vector.
*/
bool Puzzle::recreate_verify_2d_vector() {
	two_d_puzzle_vector.clear();
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
		this->insert(new_puzzle_word);
	}
	return true;
}

/*
Verifies if a puzzle_word can be added to the puzzle.
Param: puzzle_word word - The instance of puzzle_word struct to test.
*/
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
	Puzzle::trow_error("Word doesnt exist on the Dictionary.");
	return false;
}

/*
Creates a list of ten possible puzzle_words that fit the current puzzle.
Return: vector<puzzle_word> - List of words found to insert into the puzzle.
*/
vector<string> Puzzle::possible_words(string puzzle_word_pos) {
	vector<string> possible_words_vector;
	vector<string> selected_possible_words_vector;
	puzzle_word possible_puzzle_word;
	possible_puzzle_word.positionX = puzzle_word_pos[0];
	possible_puzzle_word.positionY = puzzle_word_pos[1];
	possible_puzzle_word.direction = puzzle_word_pos[2];
	for (const string word : dictionary->usable_words) {
		possible_puzzle_word.word_string = word;
		if (this->check_word(possible_puzzle_word)) {
			possible_words_vector.push_back(possible_puzzle_word.word_string);
		}
	}
	if (possible_words_vector.size() > 10) {
		for (int i = 0; i < 10; i++) {
			int index = rand() % possible_words_vector.size();
			selected_possible_words_vector.push_back(possible_words_vector[index]);
			possible_words_vector.erase(possible_words_vector.begin() + i);
		} 
	}
	else {
		selected_possible_words_vector = possible_words_vector;
	}
	return selected_possible_words_vector;
}

/*
Fills all non used space of the puzzle with #.
*/
void Puzzle::fill() {
	for (int x = 0; x < size_x; x++) {
		for (int y = 0; y < size_y; y++) {
			if (two_d_puzzle_vector[x][y] == '.') {
				two_d_puzzle_vector[x][y] = '#';
				puzzle_word new_puzzle_word;
				new_puzzle_word.positionX = x + 'a';
				new_puzzle_word.positionY = y + 'A';
				new_puzzle_word.direction = 'H';
				new_puzzle_word.word_string = "#";
				puzzle_word_vector.push_back(new_puzzle_word);
			}
		}
	}
}

/*
Saves the puzzle into a given file.
Param: ostream output_file - The file to output to. 
*/
bool Puzzle::save(ofstream* output_file, Board* board) {
	ofstream& file = *output_file;
	file << dictionary->dictionary_file_name << endl << endl;
	board->write_to_file(output_file);
	file << endl;
	for (const puzzle_word puzzle_word : puzzle_word_vector) {
		file << puzzle_word.positionX << puzzle_word.positionY << puzzle_word.direction << " " << puzzle_word.word_string << endl;
	}
	return true;
}


pair<Board*,Puzzle*> Puzzle::load(ifstream* file, Dictionary* dictionary_object) {
	string word;
	int i = 0;
	int size_x = 0;
	int size_y = 0;
	bool getting_2d_puzzle = false;
	bool getting_puzzle_words = false;
	vector<puzzle_word> loaded_puzzle_words;
	string dictionary_file;
	for (string line; getline(*file, line); )
	{
		if (i == 0) dictionary_file = line;
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
					new_puzzle_word.positionX = line[0];
					new_puzzle_word.positionY = line[1];
					new_puzzle_word.direction = line[2];
					new_puzzle_word.word_string = line.substr(4, line.size() - 4);
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
	size_y--;
	Board* board = new Board(size_y,size_x);
	Puzzle* new_puzzle = new Puzzle(size_x, size_y, "Puzzle", loaded_puzzle_words, dictionary_object);
	pair<Board*, Puzzle*> board_puzzle_pair (board, new_puzzle);
	return board_puzzle_pair;
}

void Puzzle::trow_error(string error) {
	cout << error << endl;
}
void Puzzle::trow_error(int error = 0) {
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