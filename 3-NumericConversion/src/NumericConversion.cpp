#include <iostream>
#include <string>
#include "math.h"

using namespace std;

string 	intToStr(int);
int 	strToInt(string);
int 	strToInt_backstage(string, int*);

int main(int argc, char const *argv[]) {
	
	// I just dropped here some critical test examples
	
	int myInt1 = 135;
	int myInt2 = 0;
	int myInt3 = -2345;
	int myInt4 = 1000;
	string myString1 = "135";
	string myString2 = "0";
	string myString3 = "-2345";
	string myString4 = "1000";
	string myString5 = "53dsd44";	// challenge accepted!

	cout << "String: " << myString1 << " converted to int: " << strToInt(myString1) << endl;
	cout << "Int: " << myInt1 << " converted to string: " << intToStr(myInt1) << endl;
	cout << "String: " << myString2 << " converted to int: " << strToInt(myString2) << endl;
	cout << "Int: " << myInt2 << " converted to string: " << intToStr(myInt2) << endl;
	cout << "String: " << myString3 << " converted to int: " << strToInt(myString3) << endl;
	cout << "Int: " << myInt3 << " converted to string: " << intToStr(myInt3) << endl;
	cout << "String: " << myString4 << " converted to int: " << strToInt(myString4) << endl;
	cout << "Int: " << myInt4 << " converted to string: " << intToStr(myInt4) << endl;
	cout << "I can do even so!" << endl;
	cout << "String: " << myString5 << " converted to int: " << strToInt(myString5) << endl;

	return 0;
}

/**
 * [intToStr description]
 * Function returns a text representation of an input signed integer
 * @param  num - input signed integer
 * @return     - text representation
 */
string intToStr(int num) {

	bool 	negative_integer_flag = false;
	int 	lastDigit;
	string 	result;

	// if input integer is negative - saving minus and working with absolute value
	if (num < 0) {
		negative_integer_flag = true;
		num *= -1;
	}

	// getting the last digit
	lastDigit = num % 10;
	result = "";

	// while we have 2 and more digits in input value - continue recursion calls
	// (we still have digits to cut off)
	if (num >= 10)
		result = intToStr(num/10);

	// connecting digit character to our result value
	result.push_back(lastDigit+'0');

	// adding minus character, if the minus was saved
	if (negative_integer_flag)
		result.insert(0, "-");

	return result;
}

/**
 * [strToInt  description]
 * Function returns numeric representation of given string.
 * Wrapper for recursion.
 * @param  input - input string with digit characters
 * @return       - integer representation of a string
 */
int strToInt (string input) {

	bool 	negative_integer_flag = false;
	int 	result = 0,
			level = 1;

	if (input.size() == 0)
		return 0;

	// storing the minus
	if (input.at(0) == '-') {
		negative_integer_flag = true;
		input = input.erase(0,1);
	}

	// launching service function with recursion
	result = strToInt_backstage(input, &level);
	
	// trying not to forget abour stored minus
	if (negative_integer_flag)
		result *= -1;

	return result;
}

/**
 * [strToInt_backstage description]
 * Service function for strToInt. Basic recursion logic.
 * @param  input - input string to convert
 * @param  level - a ahndler of level counter. Stored in recursion wrapper and allows to count recursion levels.
 *               Everithing would me easier without this, if only I parse string from behind, but I wanted to 
 *               create function, witch would work propertly with the "broken" strings, that consist not only digit chars.
 *               For example: "54f5" would be converted to 54;
 * @return       [description]
 */
int strToInt_backstage(string input, int* level) {

	int 	result = 0,
			digitInteger = 0;

	char 	digitCharacter = input.at(0);

	// You told me not to use type transformations, and I won't!
	switch (digitCharacter) {
		case '0':
			digitInteger = 0;
			break;
		case '1':
			digitInteger = 1;
			break;
		case '2':
			digitInteger = 2;
			break;
		case '3':
			digitInteger = 3;
			break;
		case '4':
			digitInteger = 4;
			break;
		case '5':
			digitInteger = 5;
			break;
		case '6':
			digitInteger = 6;
			break;
		case '7':
			digitInteger = 7;
			break;
		case '8':
			digitInteger = 8;
			break;
		case '9':
			digitInteger = 9;
			break;
		default:
			return -1;
	}

	// new recursion levels, if we still have what to parse
	if (input.size() > 1) {
		// gaining recursion result
		result = strToInt_backstage(input.erase(0,1), level);
		// if strange symbol was met, result would be -1
		// in that case we only resurn digit of current level, recursion result must be ignored
		if (result == -1) {
			result = digitInteger;
		} else {
			// othrewise - adding some zeroes to the current level digit, then summing it with recursion result
			result += digitInteger * pow(10, *level);
			// and do not forget to rise level counter
			// P.S. I don`t even know why do I calld this thing "level". 
			// 		It's just a power of digit we're working with, when recursion rolls back;
			*level = *level + 1;
		}
	} else {
		// when we reach the end of input string - stopping recursion growing
		result = digitInteger;
	}

	return result;

} 
