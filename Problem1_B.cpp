#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#pragma warning(disable : 4996)

// Lucas Vas
// This class may not use #include <string>


const int LINE_MAX = 1000;


char** getTokens(char inputString[], const int numTokens);
int cmpTokens(const void* a, const void* b);
char* inputToCstring(string inputString);

int main() {
	// Get input from user
	string userInput, inputLine;
	int numTokens = 0;
	while (true) {
		cout << "Please input the name of the text file, including the file extension.\n"
			<< "The name must be all one word, with no spaces: ";
		cin >> userInput;

		ifstream userFile;
		userFile.open(userInput, ios::in | ios::out);

		// get each line of characters from the file, then add it to a string.
		string temp;
		if (userFile.good()) {
			while (!userFile.eof()) {
				userFile >> temp;
				inputLine += temp + ' ';
				numTokens++;
			}
			break;
		}
		else {
			cout << "File could not be opened. Please enter a new file name.\n\n";
		}
	}

	cout << "Contents of file \"" << userInput << "\":\n\n"
		<< inputLine << endl;

	// Convert inputLine into a C-String
	char* inputCString = new char[inputLine.length() + 1];
	strcpy(inputCString, inputLine.c_str());

	char** allTokens = getTokens(inputCString, numTokens);

	// As of right now, this doesn't sort anything. I don't know how to write the compare function properly.
	qsort(allTokens, numTokens, sizeof(char*), cmpTokens);
	
	// Print every token afterwards.
	for (int i = 0; i < numTokens; i++)
		cout << allTokens[i];

	return 0;
}

char** getTokens(char* inputString, const int numTokens) {
	char** tokensList = new char* [numTokens];
	char* temp = strtok(inputString, " "); // It is assumed that there is no punctuation
	int currentIndex = 0;
	while (temp != NULL) {
		tokensList[currentIndex++] = temp; // Could overrun, however I don't think the program will reach that point. Unless something else increments currentIndex.
		/*cout << temp << endl;*/
		temp = strtok(NULL, " ");
	}
	return tokensList;
}

// Not at all sure where I went wrong here. Any pointers would be helpful.
int cmpTokens(const void* a, const void* b) {
	// Should compare each token to each other and then swap based on number that is returned.
	const char* arg1 = (const char*)a;
	const char* arg2 = (const char*)b;

	// I know that this needs to be a lot more complex, but i'm not quite sure the logic behind it.
	return *(char*)arg1[1] - *(char*)arg2[1];
}