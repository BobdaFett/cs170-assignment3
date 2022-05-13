#include <iostream>
using namespace std;

#pragma warning(disable : 4996)

// Lucas Vas
// This class may not use #include <string>


const int LINE_MAX = 1000;


char** getTokens(char inputString[], const int numTokens);
int cmpTokens(const void* a, const void* b);

int main() {
	// Get input from user
	char userInput[LINE_MAX] = {};
	cout << "Please input a string, maximum length 1000 characters, using ctrl + Z to end:" << endl;
	cin.getline(userInput, LINE_MAX, cin.eof()); // this technically shouldn't work, but it kinda does? Must use ^Z on its own line.

	int numOfTokens = 0;
	for (int i = 0; i < strlen(userInput); i++)
		if (userInput[i] == ' ' || userInput[i] == '\n')
			numOfTokens++;

	// Get tokens from full string (dynamic list return)
	char** allTokens = getTokens(userInput, numOfTokens + 1);
	qsort(allTokens, (size_t)numOfTokens + 1, (size_t)sizeof(char), cmpTokens);

	for (int i = 0; i < strlen(userInput); i++)
		cout << allTokens[i];

	// Print all the tokens one by one (with the number of times each of them happens)
	// Debating if the sortTokens function should also print these out.

	return 0;
}

char** getTokens(char inputString[], const int numTokens) {
	char** tokensList = new char* [numTokens];
	char* temp = strtok(inputString, " "); // It is assumed that there is no punctuation
	int currentIndex = 0;
	while (temp != NULL) {
		tokensList[currentIndex++] = temp; // Could overrun, however I don't think the program will reach that point. Unless something else increments currentIndex.
		cout << temp << endl;
		temp = strtok(NULL, " ");
	}
	return tokensList;
}

// Not at all sure where I went wrong here. Any pointers would be helpful.
int cmpTokens(const void* a, const void* b) {
	// Will compare each token to each other and then swap based on number that is returned.
	const char* arg1 = (const char*)a;
	const char* arg2 = (const char*)b;

	return *(char*)arg1 - *(char*)arg2;
}