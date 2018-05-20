#include "stdafx.h"
#include "Dictionary.h"

Dictionary::Dictionary(ifstream* file, string file_name) {
	dictionary_file_name = file_name;
	dictionary_file = file;
	this->read_dictionary();
}


bool Dictionary::read_dictionary() {
	dictionary_mmap = {};
	ifstream& file = *dictionary_file;
	for (string line; getline(file, line); ) {
		string word_key = "";
		string temporary_word = "";
		for (const char line_char : line) {
			if (word_key == "") {
				if (line_char == ':') word_key = temporary_word;
				else temporary_word += line_char;
			}
			else {
				if (line_char == ',') {
					for (int i = 0; i < word_key.size(); i++) {
						word_key[i] = toupper(word_key[i]);
					}
					for (int i = 0; i < temporary_word.size(); i++) {
						temporary_word[i] = toupper(temporary_word[i]);
					}
					dictionary_mmap.insert(pair<string, string>(word_key, temporary_word));
					temporary_word = "";
				}
				else if (line_char != ' ') temporary_word += line_char;
			}
			usable_words.push_back(word_key);
		}
		if (temporary_word != "") {
			for (int i = 0; i < word_key.size(); i++) {
				word_key[i] = toupper(word_key[i]);
			}
			for (int i = 0; i < temporary_word.size(); i++) {
				temporary_word[i] = toupper(temporary_word[i]);
			}
			dictionary_mmap.insert(pair<string, string>(word_key, temporary_word));
		}
	}
	return true;
}

