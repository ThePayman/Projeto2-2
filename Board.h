#pragma once
#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "ctime"
#include "cstdlib"
#include "windows.h"

using namespace std;

class Board
{
public:
	Board(int x_size, int y_size);

	void create_board();

	void show_board();
	void write_to_file(ofstream* output_file);

	bool update_board(vector<vector<char>>);

	~Board();

	unsigned int line_size, column_size;

private:
	
	vector<vector<char>> board;
};

