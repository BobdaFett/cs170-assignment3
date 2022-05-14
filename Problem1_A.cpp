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
	string userInputString, temp;
	int numTokens = 0;
	cout << "Please input a string, using ^Z on a separate line to end: ";
	while (!cin.eof()) {
		if (cin >> temp) {
			userInputString += temp + " ";
			numTokens++;
		}
	}

	char* inputCString = new char[userInputString.length() + 1];
	strcpy(inputCString, userInputString.c_str());

	// Get tokens from full string (dynamic list return)
	char** allTokens = getTokens(inputCString, numTokens);
	qsort(allTokens, numTokens + 1, sizeof(char*), cmpTokens);

	for (int i = 0; i < numTokens; i++)
		cout << allTokens[i];

	// Print all the tokens one by one (with the number of times each of them happens)
	// Debating if the sortTokens function should also print these out.

	return 0;
}

char** getTokens(char inputString[], const int numTokens) {
	char** tokensList = new char*[numTokens];
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