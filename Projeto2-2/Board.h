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
	Board();

	void create_board();

	void show_board();

	bool update_board(vector<vector<char>>);

	~Board();

	unsigned int line_size, column_size;

private:

	vector<vector<char>> board;
};

