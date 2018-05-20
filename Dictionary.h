#pragma once
#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"

using namespace std;



class Dictionary{

public:
	ifstream* dictionary_file;

	//Default constructor
	Dictionary(ifstream* dictionary_file, string dictionary_file_name);

	//Destructor
	~Dictionary();

	//Acessor functions
	vector<string> read_dictionary();
	vector<string> usable_words_sort();

	vector<string> usable_words;
	string dictionary_file_name;

};

