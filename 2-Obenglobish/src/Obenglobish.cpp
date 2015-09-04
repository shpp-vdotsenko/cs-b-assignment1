#include <iostream>
#include <string>
#include <locale>

using namespace std;

string 	obenglobish(string);
bool 	is_vovel(char);
void 	cast(string);

/**
 * [obenglobish description]
 * Function transforms english words into "Obenglobish" pig-latin language
 * @param  english - input word (or text), that must be transformed
 * @return         - obenglobish analog of input word
 */
string obenglobish(string english) {

	string 	result = "";

	int 	length = english.size(),
			current = 0;

	char	currchar = ' ',
			nextchar = ' ',
			prevchar = ' ';

	bool	doit_flag = false;

	// parsing input word
	while (current < length) {

		currchar = english.at(current);

		// when we found vovel letter in the word
		if (is_vovel(currchar)) {
			doit_flag = true;
			nextchar = (current+1 < length) ? english.at(current+1) : ' ';
			
			// dropping down doit_flag, if we meet two vovels one by one...
			if (is_vovel(prevchar))
				doit_flag = false;
			// ...or if there is an 'e' letter in the end of word
			if (currchar == 'e' && !isalpha(nextchar))
				doit_flag = false;

			// adding "ob" letters to result string, if doit_flag is true
			if (doit_flag) {
				result.push_back('o');
				result.push_back('b');
			}
		}

		// adding checked character in result string...
		result.push_back(currchar);

		// ...and making some looping magic.
		prevchar = currchar;
		current ++;
	}

	return result;

}

/**
 * [is_vovel description]
 * Function returns true, if input character is a latin vowel letter. A, O, I, U, E or Y
 * @param  letter - character to check
 * @return        - buulean value
 */
bool is_vovel(char letter) {
	return (
		letter == 'a' ||
		letter == 'o' ||
		letter == 'i' ||
		letter == 'u' ||
		letter == 'e' ||
		letter == 'y'
	) ? true : false ;
}

int main(int argc, char const *argv[]) {

	// I was confused, when I couldn`t copy your interface example from Google Docks T_T
	while (true) {
		string word;
		cout << "Enter word: ";
		getline(cin, word);
		if (word == "") break;
		cout << word << " --> " << obenglobish(word) << endl;
	}

	return 0;
}
