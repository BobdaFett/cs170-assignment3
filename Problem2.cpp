#include <iostream>
#include <fstream>
using namespace std;

void initFile();
void popFromFile(string inputFile);
void inputData();
void listTools();
void delTool();
void updateTool();

struct Tool {
	int tid; // "Tool identification number"
	string name;
	int quantity;
	double cost;
	Tool() {
		this->tid = 0;
		this->name = "default";
		this->quantity = 0;
		this->cost = 0.00;
	}
	Tool(int tid, string name, int quantity, double cost) {
		this->tid = tid;
		this->name = name;
		this->quantity = quantity;
		this->cost = cost;
	}
};

int main() {

	// For debug:
	initFile();
	listTools();
	inputData();

	int userInput;
	cout << "Menu will go here with options, formatted properly: ";
	cin >> userInput;
	// Validate the input here.
	// USING A STRUCT WILL BE VERY USEFUL HERE.

	switch (userInput) {
	case 1: // Create a file and initialize it with 100 empty objects.
		initFile();
		break;
	case 2: // Populate file with data read from text file. File can be assumed to have the correct formatting.
		// Get the name of the file that should be read from. MUST INCLUDE FILE EXTENSION.
		/*popFromFile();*/
		break;
	case 3: // input data concerning one or more tools from the keyboard.
		inputData();
		break;
	case 4: // List all tools
		listTools();
		break;
	case 5: // Delete a tool completely.
		delTool();
		break;
	case 6: // Update any information for a tool at any location.
		updateTool();
		break;
	}

	// Main shouldn't do any of the logic. This should be split into at least 6 functions.

	return 0;
}

void initFile() {
	fstream file;
	file.open("hardware.txt", ios::binary | ios::in | ios::out | ios::trunc);
	// This will init to 100 empty places, possibly being empty spaces.
	for (int i = 0; i < 100; i++) {
		Tool temp = Tool(i, "default", 0, 0.00);
		file.write((char*)&temp, sizeof(Tool));
	}
	cout << "File write status: " << ((file.good()) ? "good" : "bad") << endl;
}

void popFromFile(string inputFile) {
	// Must iterate through an entire file, pulling a specific structure out of it.
	fstream file;
	ifstream input;
	file.open("hardware.txt", ios::binary | ios::in | ios::out);
	input.open(inputFile, ios::binary);
	for (int i = 0; i < 100; i++) {
		// Must somehow read all of the Tool structs properly.
	}
	cout << "File read/write status: " << ((file.good()) ? "good" : "bad") << endl;
}

void inputData() {
	// might add a name/etc parameter to this.
	fstream file;
	file.open("hardware.txt", ios::binary | ios::in | ios::out);
	int userInput;
	string stringInput;
	cout << "Please enter the TID (tool identification number) of the tool you would like: ";
	cin >> userInput;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// Set where the file should be reading from:
	file.seekg((sizeof(Tool) * userInput), ios::beg);
	Tool temp = Tool();
	file.read((char*)&temp, sizeof(Tool));
	cout << "Currently editing TID " << temp.tid << ", name: " << temp.name << endl;

	cout << "Menu here with all options for editing: ";
	cin >> userInput;
	switch (userInput) {
	case 1: // Change name
		break;
	case 2: // Change quantity
		break;
	case 3: // Change cost
		break;
	default:
		// Go back to beginning
		break;
	}
	file.close();
}

void listTools() {
	// Iterates through the whole file while printing each argument.
	fstream file;
	file.open("hardware.txt", ios::binary | ios::in);
	Tool temp = Tool();
	while(file.good()) {
		file.read((char*)&temp, sizeof(Tool));
		cout << temp.tid << temp.name << temp.quantity << temp.cost << endl; // All in one line, reformat afterwards.
	}
	file.close();
}

void delTool(fstream file) {
	// Might add a name/number parameter.
}

void updateTool(fstream file) {
	// Might add a name/number parameter.
}