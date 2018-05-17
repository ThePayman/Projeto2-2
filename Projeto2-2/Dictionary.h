#pragma once
#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "map"

using namespace std;



class Dictionary {

public:
	ifstream dictionary_file;
	Dictionary();

	bool read_dictionary();

private:
	string dictionary_file_name;
	vector<string> usable_words;
	ofstream word_file;
	multimap<string, string> dictionary_mmap = {};
	//ifstream dictionary_file;

};
