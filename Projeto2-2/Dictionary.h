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
	ifstream* dictionary_file;

	Dictionary(ifstream* dictionary_file, string dictionary_file_name);

	bool read_dictionary();

	string dictionary_file_name;
	multimap<string, string> dictionary_mmap = {};

	vector<string> usable_words;
	ofstream word_file;


};
