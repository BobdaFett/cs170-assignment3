#include <iostream>
#include <fstream>
using namespace std;

#pragma warning(disable : 4996)

// This program may not use the library class string or vectors.

int main() {
	// Something here...
	/*
	* Input several lines of text from the user as a C-string.
	* Print an alphabetical listing of each word in the text and how many times that word occurred without regard for upper/lowercase.
	* 
	* It may be assumed that there is no punctuation, and that exactly one space separates each word.
	* The number of characters per line along with the total number of lines may be assumed but clearly stated. 
	*/

	// Hint given: keep a pointer to each word within a char* array, or keep the words themselves inside of a 2-dimensional array.
	// Add these pointers through a function maybe?
	// This will require strtok() - this will return a sequence of characters.
	char userInput[100]{};

	cout << "Please input a line of text, no longer than 100 characters long: ";
	cin.getline(userInput, 100); // <- pulls 100 characters from cin... would take more if the array was larger.
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	// TODO: validate inputs, terminate at end of file.

	cout << "Splitting this string into tokens between spaces..." << endl;
	char* strTokens[5] = {};
	strTokens[0] = strtok(userInput, " ");
	for (int i = 1; i < 5; i++) {
		strTokens[i] = strtok(NULL, " ");
	}

	for (char* i : strTokens) {
		cout << i << endl;
	}

	// Get the total number of tokens inside of the input string, multiple lines included:
	int numTokens = 0;
	for (char i : userInput) {
		// This is not actually activating. Are spaces an escape character?
		if (' ' == i) numTokens++;
		else {
			printf("This was false - character \"%c\" was not a space.\n", i);
		}
	}
	cout << "Total number of tokens: " << numTokens << endl;
	// Instead of printing these, store them inside of an array.
	//while (strTokens != NULL) {

	//}

	return 0;
}

void getTokens(char* inputStr, char *tokens[]) {
	// If i were to add extra values to the array, each time i would have to create a new array, copy everything over, then delete the array.

}