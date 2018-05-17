#include "string"
#include "iostream"
#include "vector"
#include "map"

using namespace std;


struct puzzle_word {
	char positionX;
	char positionY;
	char direction;
	string word_string;
};

class Puzzle {
public:
	Puzzle(int size_x, int size_y, string name, vector<puzzle_word> load_vector, vector<string> solved_puzzle_corresponding_word_vector);
	bool insert(puzzle_word word);
	bool recreate_verify_2d_vector();
	static Puzzle load(istream inputput_file, string dictionary_file_name, multimap<string, string> dictionary_mmap);
private:
	int size_x;
	int size_y;
	string name;
	vector<vector<char>> two_d_puzzle_vector;
	vector<puzzle_word> solved_puzzle_word_vector;
	vector<string> solved_puzzle_corresponding_word_vector;
	vector<puzzle_word> puzzle_word_vector;
};