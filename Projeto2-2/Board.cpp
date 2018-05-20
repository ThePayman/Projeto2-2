#include "stdafx.h"
#include "Board.h"
#include "Menu.h"


// PROG - MIEIC // JAS // Example of a program that prints colored characters on the console (in text mode)
//========================================================================================== //COLOR CODES: (alternative: use symbolic const’s) 
#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15
//==========================================================================================
void clrscr(void) {
	COORD coordScreen = { 0, 0 }; // upper left corner 
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;


	// fill with spaces 
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner 
	SetConsoleCursorPosition(hCon, coordScreen);
}
//==========================================================================================
// Position the cursor at column 'x', line 'y' 
// The coodinates of upper left corner of the screen are (x,y)=(0,0)
void gotoxy(int x, int y) { COORD coord; coord.X = x; coord.Y = y; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); }
//==========================================================================================
// Set text color
void setcolor(unsigned int color) { HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hcon, color); }
//==========================================================================================
// Set text color & background
void setcolor(unsigned int color, unsigned int background_color) { HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); if (background_color == BLACK) SetConsoleTextAttribute(hCon, color); else SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); }


Board::Board(int x_size, int y_size){
	column_size = x_size;
	line_size = y_size;
	for (int x = 0; x < column_size + 1; x++) {
		vector<char> y_vector;
		for (int y = 0; y < line_size + 1; y++) {
			y_vector.push_back('.');
		}
		board.push_back(y_vector);
	}

	for (unsigned int i = 1; i < line_size + 1; i++) {
		board[0][i] = char(96 + i);
	}
	for (unsigned int i = 1; i < column_size + 1; i++) {
		board[i][0] = char(64 + i);
	}

	board[0][0] = ' ';
}

void Board::create_board() {
	Menu::trow_error("Deprecated. This function should not be called");
}

void Board::show_board() {

	for (unsigned int x = 0; x < board.size(); x++){
		for (unsigned int y = 0; y < board[0].size(); y++){
			if (x == 0) { setcolor(4); }
			if (y == 0) { setcolor(4); }
			if (x != 0 && y != 0) { setcolor(0,7); }
			if (y == (board[0].size() - 1)) { cout << " " << board[x][y] << " "; }
			else { cout << " " << board[x][y]; }
		}
		cout << endl;
		setcolor(7);
	}
}

void Board::write_to_file(ofstream* output_file) {
	ofstream& file = *output_file;
	for (unsigned int x = 0; x < board.size(); x++) {
		for (unsigned int y = 0; y < board[0].size(); y++) {
			if (x != 0 && y != 0) { setcolor(0, 7); }
			if (y == (board[0].size() - 1)) { file << " " << board[x][y] << " "; }
			else { file << " " << board[x][y]; }
		}
		file << endl;
	}
}

bool Board::update_board(vector<vector<char>> two_d_vector){
	for (unsigned int x = 0; x < two_d_vector.size(); x++){
		for (unsigned int y = 0; y < two_d_vector[0].size(); y++) {
			board[1 + y][1 + x] = two_d_vector[x][y];
			}
	}
	return true;
}

Board::~Board(){
	//save the board and exit
}




