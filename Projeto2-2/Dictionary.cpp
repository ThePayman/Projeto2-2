#include "stdafx.h"
#include "Dictionary.h"


Dictionary::Dictionary(ifstream* file, string file_name) {
	dictionary_file_name = file_name;
	dictionary_file = file;
	this->read_dictionary();
}

//The following function reads the dictionary file that is given to it and stores the usable words in a vector

vector<string> Dictionary::read_dictionary() {
	string word;
	ifstream& file = *dictionary_file;
	while (file >> word) {
		string newWord = "";
		bool ignore_word = false;
		for (unsigned int i = 0; i < word.length(); i++) {
			if ((word[word.length()-1] != ':')){		//If cicle used to separate the words being defined from their sinonims
				ignore_word = true;
				break;
			}
		}
		if (!ignore_word) {
			if (word.length() > 1) {
				for (unsigned int i = 0; i < word.length() - 1 ; i++){		//this for cicle is used to capitalize the lower case characters and remove the ':'
					if (word[i] >= 'a' && word[i] <= 'z'){
						newWord = newWord + char(word[i] - 32);
					}
					else {
						newWord = newWord + word[i];
					}
				}
				usable_words.push_back(newWord);
			}
		}
	}
	return usable_words;
}

vector<string> Dictionary::usable_words_sort(){		//This function is used to sort the usable_words vector in order to ease the use of future functions
	string c, d;

	for (unsigned int b = 0; b < usable_words.size(); b++) {
		for (unsigned int i = 0; i < (usable_words.size() - 1 - b); i++) {
			if (usable_words[i] > usable_words[i + 1]) {
				c = usable_words[i];
				usable_words[i] = usable_words[i + 1];
				usable_words[i + 1] = c;
			}
		}
		//if (b % 100 == 0) cout << b << " of " << usable_words.size() << " --- " << (int)((100 * b) / usable_words.size()) << "% Complete" << endl;  (uncomment this line to show progress)
	}
	return usable_words;
}


Dictionary::~Dictionary(){}
