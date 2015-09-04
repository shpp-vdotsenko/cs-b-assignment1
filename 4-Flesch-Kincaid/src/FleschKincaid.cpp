#include <iostream>
#include <fstream>
#include <cctype>

#include "console.h"
#include "tokenscanner.h"

using namespace std;

bool 	isSentenceClosure(string token);
bool 	isWord(string token);
int 	calcSyllables(string word);
bool 	is_vovel(char);


int main(int argc, char const *argv[]) {

	string	file_name = " ";
	int 	countWords = 0,
			countSenten = 0,
			countSyllabels = 0;

	double 	C0 = 0,
			C1 = 0,
			C2 = 0;

	cout << "Choose your file: " ;
	cin >> file_name;

	// Token scanner initialization
	ifstream file(file_name);
	TokenScanner scanner(file);

	while (scanner.hasMoreTokens()) {

		string token = scanner.nextToken();

		// if we met an 'end of centence' symbol - increment sentences counter
		if (isSentenceClosure(token)) {
			countSenten++;
			continue;
		}

		// if current token is a word - incrementing word counter 
		if (isWord(token)) {
			countSyllabels += calcSyllables(token);
			countWords++;
			continue;
		}

		// some magic with an apostrophe bag
		// words in single brackets are counted too now
		if (token == "'") {

			// skipping two tokens afrer ' anyway.
			// checking them and trying to find...
			string wordInBrackets = scanner.nextToken();
			string following_token = scanner.nextToken();

			// ...closing brackets, ...
			if (following_token == "'") {
				countSyllabels += calcSyllables(wordInBrackets);
				countWords++;
				continue;
			}

			// ...or "end of sentence" symbols
			if (isSentenceClosure(following_token)) {
				countSenten++;
				cout << " (end of sentence)" << endl;
				continue;
			}
		}

	}

	// echo the counted results
	cout << "Words: " << countWords << endl;
	cout << "Sentences: " << countSenten << endl;
	cout << "Syllabels: " << countSyllabels << endl;
	int grade = C0 + C1*(countWords/countSenten) + C2*(countSyllabels/countWords);
	cout << "Grade level: " << grade << endl;

	return 0;

}

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

bool isSentenceClosure(string token){
	return (
		token == "." || 
		token == "!" || 
		token == "?"
	) ? true : false;
}

bool isWord(string token){
	return (isalpha(tolower(token[0]))) ? true : false;
}

int calcSyllables(string word) {

	int syllables = 0;

	// Here we have a loop, that parsing an input word.
	for (int i = 0; i < word.size(); i++) {
		if (is_vovel(word.at(i)))					// Looking for vovels
			if (i+1 < word.size()) {				// checking to stay in range while looking to the next symbol
				if (!is_vovel(word.at(i)))			// ignoring paired vovels
					syllables++;
			} else {								// if this is the last letter - it counts anyway
				syllables++;
			}
	}

	if (word.at(word.size()-1) == 'e')				// fixing result, if the word ends with letter 'e'
		syllables --;

	return (syllables == 0) ? 1 : syllables;

}
