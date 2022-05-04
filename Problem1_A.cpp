#include <iostream>
using namespace std;

// Lucas Vas
// This class may not use #include <string>

char* getTokens(char inputString[]);
void sortTokens(char* tokens);

int main() {
	// Get input from user
	char userInput[1000] = {};
	cout << "Please input a string, using ctrl + Z to end:" << endl;
	cin.get(userInput, '\x1A');

	// Get tokens from full string (dynamic list return)
	char* allTokens = getTokens(userInput);

	// Sort tokens by first letter in every word (function)
	sortTokens(allTokens);

	// Print all of the tokens one by one (with the number of times each of them happens)
	// Debating if the sortTokens function should also print these out.

	return 0;
}