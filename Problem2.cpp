#include <iostream>
#include <fstream>
using namespace std;

void initFile();
void popFromFile(string fileName);
void inputData();
void listTools();
void delTool();
void updateTool();

struct Tool {
private:
	int tid; // "Tool identification number"
	string name;
	int quantity;
	double cost;

public:
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
	void setName(string name) { this->name = name; }
	void setCost(double cost) { this->cost = cost; }
	void setQuantity(int quantity) { this->quantity = quantity; }
	void setTid(int tid) { this->tid = tid; }
	int getTid() { return this->tid; }
	string getName() { return this->name; }
	int getQuantity() { return this->quantity; }
	double getCost() { return this->cost; }

};

int main() {
	
	// Program is assumed to be working ONLY with hardware.dat.
	// Other files will not work, nor will I make them work.

	int userInput;
	string fileNameInput;
	while (true) {
		cout << "1: Create a file hardware.dat\n"
			<< "2: Populate hardware.dat with data from another file\n"
			<< "3: Input data for any tool\n"
			<< "4: List all tools\n"
			<< "5: Delete a tool from the list\n"
			<< "6: Update any tool from the list\n"
			<< "7: Exit the program\n\n"
			<< "Please input your choice: ";
		cin >> userInput;
		// Validate the input here.
		// USING A STRUCT WILL BE VERY USEFUL HERE.

		switch (userInput) {
		case 1: // Create a file and initialize it with 100 empty objects.
			initFile();
			break;
		case 2: // Populate file with data read from text file. File can be assumed to have the correct formatting.
			// Get the name of the file that should be read from. MUST INCLUDE FILE EXTENSION.
			cout << "Please input the name of the file you would like to read: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> fileNameInput;
			popFromFile(fileNameInput);
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
		case 7:
			cout << "Good bye!" << endl;
			return 0;
			break;
		}
	}
}

void initFile() {
	fstream file;
	file.open("hardware.txt", ios::binary | ios::out | ios::trunc);
	// This will init to 100 empty places, possibly being empty spaces.
	for (int i = 1; i <= 100; i++) {
		Tool temp = Tool(i, "default", 0, 0.00);
		file.write((char*)&temp, sizeof(Tool));
		/*cout << "Created tool TID " << i << endl;*/
	}
	cout << "\n" << ((file.good()) ? "File created successfully." : "Operation failed - file was not created.") << "\n\n" << endl;
	file.close();
}

void popFromFile(string fileName) {
	// Must iterate through an entire file, pulling a specific structure out of it.
	fstream file;
	ifstream inputFile;
	file.open("hardware.txt", ios::binary | ios::in | ios::out);
	inputFile.open(fileName, ios::binary);
	for (int i = 1; i <= 100; i++) {
		// Must somehow read all of the Tool structs properly.
	}
	cout << "File read/write status: " << ((file.good()) ? "good" : "bad") << endl;
	file.close();
}

void inputData() {
	// might add a name/etc parameter to this.
	cout << "Starting data input..." << endl;
	fstream file;
	file.open("hardware.txt", ios::binary | ios::in | ios::out);
	int userInput;
	string stringInput;
	cout << "Please enter the TID (tool identification number) of the tool you would like: ";
	cin >> userInput;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// Set where the file should be reading from:
	file.seekg((sizeof(Tool) * userInput - 1), ios::beg);
	Tool temp = Tool();
	file.read((char*)&temp, sizeof(Tool));
	cout << "Currently editing TID " << temp.getTid() << ", name: " << temp.getName() << endl;

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
	ifstream file;
	file.open("hardware.txt", ios::binary | ios::in);
	Tool* temp = new Tool();
	try {
		while (!file.eof()) { // Needs to check that bits are good before doing anything with them.
			file.read((char*)&temp, sizeof(Tool));
			if (file.fail()) { throw(2); }
			cout << temp.getTid() << temp.getName() << temp.getQuantity() << temp.getCost() << endl; // All in one line, reformat later.
		}
	}
	catch (int e) {
		if (e == 2) {
			cout << "file.fail() is true." << endl;
		}
	}
	file.close();
	cout << "File closed successfully." << endl;
}

void delTool() {
	// Might add a name/number parameter.
}

void updateTool() {
	// Might add a name/number parameter.
}