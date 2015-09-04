#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main () {
	int	coinDrop = 0,		// code of coin side
		heads = 0;			// number of heads, dropped one by one

	srand (time(NULL));		// initialize random seed:

	/*
		0 - heads
		1 - tails
	*/

	// continue to drop the coin, while head won't be achived 3 times in a row
	while (heads < 3) {
		coinDrop = rand() % 2;			// calculetes random drop
		if (coinDrop == 1) {			// if tailes
			heads = 0;
			cout << "tails" << endl;
		} else {						// if heads
			heads++;
			cout << "heads" << endl;
		}
	}
	
	return 0;
}
