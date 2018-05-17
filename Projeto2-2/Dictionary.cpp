#include "stdafx.h"
#include "Dictionary.h"

Dictionary::Dictionary() {
	cout << "What is the dictionary file name?" << endl;
	cin >> dictionary_file_name;
	dictionary_file.open(dictionary_file_name);
	if (!dictionary_file.is_open()) {
		cout << "Invalid File" << endl;
	}

}



bool Dictionary::read_dictionary() {
	dictionary_mmap = {};
	for (string line; getline(dictionary_file, line); ) {
		string word_key = "";
		string temporary_word = "";
		for (const char line_char : line) {
			if (word_key == "") {
				if (line_char == ':') word_key = temporary_word;
				else if(temporary_word != "") temporary_word += line_char;
			} else {
				if (line_char == ',') {
					dictionary_mmap.insert(pair<string, string>(word_key, temporary_word));
					temporary_word = "";
				} else if (line_char != ' ') temporary_word += line_char;
			}
		}
		if(temporary_word != "") dictionary_mmap.insert(pair<string, string>(word_key, temporary_word));
	}
}	

