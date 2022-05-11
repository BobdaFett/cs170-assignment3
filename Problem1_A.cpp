#include <iostream>
using namespace std;

#pragma warning(disable : 4996)

// Lucas Vas
// This class may not use #include <string>


const int LINE_MAX = 1000;


char** getTokens(char inputString[], const int numTokens);
/*void sortTokens(char* tokens[]);*/

int main() {
	// Get input from user
	char userInput[LINE_MAX] = {};
	cout << "Please input a string, using ctrl + Z to end:" << endl;
	cin.getline(userInput, LINE_MAX, cin.eof()); // this technically shouldn't work.

	int numOfTokens = 0;
	for (int i = 0; i < strlen(userInput); i++)
		if (userInput[i] == ' ' || userInput[i] == '\n')
			numOfTokens++;

	// Get tokens from full string (dynamic list return)
	char** allTokens = getTokens(userInput, numOfTokens + 1);

	// Sort tokens by first letter in every word (function)
	/*sortTokens(allTokens, numOfTokens);*/

	// Print all of the tokens one by one (with the number of times each of them happens)
	// Debating if the sortTokens function should also print these out.

	return 0;
}

char** getTokens(char inputString[], const int numTokens) {
	char** tokensList = new char*[numTokens];
	char* temp = strtok(inputString, " "); // It is assumed that there is no punctuation
	int currentIndex = 0;
	while (temp != NULL) {
		tokensList[currentIndex++] = temp;
		cout << temp << endl;
		temp = strtok(NULL, " ");
	}
	return tokensList;
}

//void sortTokens(char* tokens[], const int size) {
//	for (int i = 0; i < ) {
//
//	}
//}