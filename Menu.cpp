#include "stdafx.h"
#include "Menu.h"
#include "Board.h"
#include "Dictionary.h"
#include "Puzzle.h"



Menu::Menu(){
	cout << "CROSSWORDS PUZZLE CREATOR" << endl
		<< "=========================================" << endl
		<< endl
		<< "INSTRUCTIONS:" << endl
		<< endl
		<< "Position (LCD / CTRL - Z = Stop)" << endl
		<< "LCD stands for Line, Column and Direction" << endl
		<< endl
		<< "To define a line you must:" << endl
		<< "Input the letter that marks that line, that letter must be capitalized." << endl
		<< endl
		<< "To define a column you must:" << endl
		<< "Input the letter that marks that column, that letter must be lower case." << endl
		<< endl
		<< "To define the direction you must:" << endl
		<< "Input V (capitalized) if the direction you wish is vertical or H (capitalized) if it is horizontal." << endl
		<< endl
		<< "----------------------------------------"
		<< endl;
}
/*
	Main Menu function. Gives general options to the user.
*/
void Menu::Selection() {
	cout << "Choose from the following options:" << endl
		<< "1 - Create Puzzle" << endl
		<< "2 - Resume Puzzle" << endl
		<< "0 - Exit" << endl
		<< endl
		<< "What is your option?" << endl;
	cin >> option;
	
	if (option == "1") {
		cout << "----------------------------------------" << endl
			<< "CREATE BOARD" << endl
			<< "----------------------------------------" << endl;
		
		
		//dictionary->read_dictionary();
		if(!this->get_dictionary()) return;
		//dictionary->usable_words_sort();
		pair<int,int> x_y_size_pair = this->get_board_size();
		board = new Board(x_y_size_pair.first, x_y_size_pair.second);
		board->show_board();
		
		puzzle = new Puzzle(board->line_size, board->column_size, "", dictionary);

		this->ask_position_and_word();
		
		return;
		

	}
	else if(option == "2") {
		cout << "----------------------------------------" << endl
			<< "EDIT LOADED BOARD" << endl
			<< "----------------------------------------" << endl;

		if (!this->get_dictionary()) return;

		if (!this->get_board_file()) return;
		
		std::pair<Board*, Puzzle*> board_puzzle_loaded_pair = Puzzle::load(board_file , dictionary);
		board = board_puzzle_loaded_pair.first;
		puzzle = board_puzzle_loaded_pair.second;
		board->update_board(puzzle->two_d_puzzle_vector);
		board->show_board();

		this->ask_position_and_word();
		
		return;
	}
	else if(option == "0"){
		this->~Menu();
	}
	else {
		cout << endl;
		Menu::trow_error("Invalid input, please select a valid option. Not a possible option.");
		cout << endl;
		this->Selection();
	}

}
/*
	Asks a position and word to insert into a position on the puzzle. Loops until EOF of Cin.
*/
void Menu::ask_position_and_word(){
	string position = "";
	while (!cin.eof()) {
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
		if (word[0] == '-') puzzle->remove_string(position, word.substr(1,word.size() - 1));
		else if (word[0] == '?') { 
			vector<string> possible_words = puzzle->possible_words(position);
			cout << "Possible words for position " << position << ": " << endl;
			for (const string word : possible_words) {
				cout << word << endl;
			}
		}
		else puzzle->insert_string(position, word);
		board->update_board(puzzle->two_d_puzzle_vector);
		board->show_board();
	}
	cin.clear();
	this->ask_puzzle_options();
}

/*
	Puzzle Menu function. Gives options especific to a puzzle to the user.
*/
bool Menu::ask_puzzle_options() {
	cout << "Choose from the following options:" << endl
	<< "1 - Continue editing Puzzle" << endl
	<< "2 - Save Puzzle" << endl
	<< "3 - Finish and Save Puzzle" << endl
	<< "0 - Exit" << endl
	<< endl
	<< "What is your option?" << endl;
	cin >> option;
	if (option == "1") {
		this->ask_position_and_word();
	}
	if (option == "2") {
		ofstream* save_file = get_output_file();
		puzzle->save(save_file,board);
		cout << "The incomplete board has been saved." << endl;
	}
	if (option == "3") {
		ofstream* save_file = get_next_output_puzzle();
		puzzle->fill();
		puzzle->save(save_file, board);
		cout << "The complete board has been saved." << endl;
	}
	if (option == "0") {
		return false;
	}
	return true;
}
/*
	Loops until a valid input file is open.
*/
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

/*
	Loops until a valid output file is open.
*/
ofstream* Menu::get_output_file() {
	string file_name;
	cout << "What is the file name?" << endl;
	cin >> file_name;
	ofstream* file = new ofstream();
	file->open(file_name);
	if (!file->is_open()) {
		cout << "Invalid File" << endl;
		return this->get_output_file();
	}
	return file;
}

ofstream* Menu::get_next_output_puzzle() {
	string file_location;
	cout << "Where do you want to place the file?" << endl;
	cin >> file_location;
	if (file_location.back() != '/') file_location += '/';
	int puzzle_output_file_int = 0;
	string puzzle_output_file_name = "000";
	while (true) {
		puzzle_output_file_int++;
		if(puzzle_output_file_int < 10) puzzle_output_file_name = "00"+to_string(puzzle_output_file_int);
		else if(puzzle_output_file_int < 100) puzzle_output_file_name = "0"+to_string(puzzle_output_file_int);
		else puzzle_output_file_name = to_string(puzzle_output_file_int);
		ifstream f(file_location + puzzle_output_file_name + ".txt");
		if (!f.good()) break;
	}
	ofstream* file = new ofstream();
	file->open(file_location + puzzle_output_file_name + ".txt");
	return file;
}

/*
	Loops until a valid dictionary file is open and creates the dictionary object.
*/
bool Menu::get_dictionary() {
	cout << "What is the dictionary file name?" << endl;
	cin >> dictionary_file_name;
	dictionary_file = new ifstream();
	dictionary_file->open(dictionary_file_name);
	if (!dictionary_file->is_open()) {
		cout << "Invalid File" << endl;
		return this->get_dictionary();
	}
	dictionary = new Dictionary(dictionary_file, dictionary_file_name);
	return true;
}

bool Menu::get_board_file() {
	cout << "What is the board file name?" << endl;
	cin >> board_file_name;
	board_file = new ifstream();
	board_file->open(board_file_name);
	if (!board_file->is_open()) {
		cout << "Invalid File" << endl;
		return this->get_board_file();
	}
	return true;
}

pair<int, int> Menu::get_board_size() {
	int line_size;
	int column_size;

	cout <<
		"What is the board size (lines and columns separated by a space)?" << endl;
	cin >> line_size >> column_size;

	while (line_size <= 0 || column_size <= 0) {
		Menu::trow_error("Invalid board size, please input new values that are greater than 0.");
		cin.clear();
		cin >> line_size >> column_size;
	}
	pair<int, int> board_size (column_size, line_size);
	return board_size;
	
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
Menu::~Menu(){}

