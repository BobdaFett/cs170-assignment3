#include <iostream>
#include <iomanip>
#include "Tool.h"
using namespace std;

void createFile(fstream& file);
void fromTxt(fstream& file);
void inputData(fstream& file);
void listTools(fstream& file);
void delTool(fstream& file);
void updateTool(fstream& file);

int main() {
    int userInput;
    fstream userFile;
    while(true) {
        cout << "1: Create a file hardware.dat\n"
             << "2: Populate hardware.dat with data from another file\n"
             << "3: Input data for any tool\n"
             << "4: List all tools\n"
             << "5: Delete a tool from the list\n"
             << "6: Update any tool from the list\n"
             << "7: Exit the program\n\n"
             << "Input your choice: ";
        cin >> userInput;

        switch(userInput) {
            case 1:
                createFile(userFile);
                break;
            case 2:
                fromTxt(userFile);
                break;
            case 3:
                inputData(userFile);
                break;
            case 4:
                listTools(userFile);
                break;
            case 5:
                delTool(userFile);
                break;
            case 6:
                updateTool(userFile);
                break;
            case 7:
                cout << "Exiting..." << endl;
                return 0;
            default:
                // Return to beginning
                cout << "Invalid option. Try again.\n" << endl;
                break;
        }
    }

    return 0;
}

void createFile(fstream& file) {
    if(file.is_open()) {
        char choice;
        cout << "WARNING - this will overwrite the previous file. Continue? (Y/n) ";
        if(cin >> choice) {
            if(toupper(choice) == 'Y') {
                file.open("hardware.dat", ios::binary | ios::out | ios::in | ios::trunc);
                if (file) cout << "File created successfully." << endl;
            } else if (toupper(choice) == 'N') {
                cout << "Returning to main menu...\n" << endl;
                main();
            }
        }
    }

    file.open("hardware.dat", ios::binary | ios::out | ios::in | ios::trunc);

    for(int i = 0; i < 100; i++) {
        Tool temp = Tool(i+1, "default", 0, 0);
        file.write((char*)&temp, sizeof(Tool));
    }
}

void fromTxt(fstream& file) {
    if(!file.is_open())
        file.open("hardware.dat", ios::binary | ios::out | ios::in);

    ifstream toRead;
    string userInput;
    Tool temp = Tool(0, "", 0, 0);

    cout << "Enter the name of the \"*.txt\" to read: ";
    cin >> userInput;
    toRead.open(userInput + ".txt", ios::in);

    if(toRead) {
        while (temp.readFile(toRead)) {
            if(toRead.fail()) {
                cout << "End of file has been reached.\n" << endl;
                break;
            }
            file.write((char*)&temp, sizeof(Tool));
        }
    }

    toRead.close();
}

void inputData(fstream& file) {
    if(!file.is_open())
        file.open("hardware.dat", ios::binary | ios::out | ios::in);

    char name[15];
    int tid, quantity;
    double cost;

    cout << "Input the data you would like to create in \"ID name quantity cost\" format: ";
    if (cin >> tid >> name >> quantity >> cost) {
        Tool temp = Tool(tid, name, quantity, cost);
        if(file.read((char*)&temp, sizeof(Tool)) && temp.getTid() == tid) {
            cout << "This will overwrite another tool. Please use the \"Update Tool\" function from the main menu." << endl;
            file.clear();
        } else {
            temp = Tool(tid, name, quantity, cost);
            file.clear();
            file.seekg(-(int)sizeof(Tool), ios::cur);
            file.write((char*)&temp, sizeof(Tool));
        }
    }
}

void listTools(fstream& file) {
    if(!file.is_open())
        file.open("hardware.dat", ios::binary | ios::out | ios::in);

    string name;
    int id, quantity;
    double cost;
    Tool temp = Tool(0, "", 0, 0);

    file.seekg(0, ios::beg);
    while(file.read((char*)&temp, sizeof(Tool))) {
        if (file.fail()) break;
        temp.printFormatted();
    }

    cout << "\n\n";
}

void delTool(fstream& file) {
    if(!file.is_open())
        file.open("hardware.dat", ios::binary | ios::out | ios::in);

    // Not quite sure why this one isn't working.
    int userInput;
    cout << "Input the TID of the tool you would like to remove: ";
    if(cin >> userInput) {

        // Iterate through the whole file and remake it.
        ofstream newFile ("hardwareTemp.dat", ios::binary | ios::out | ios::trunc);
        Tool temp = Tool(0, "", 0, 0);

        file.seekg(0, ios::beg);
        while(file.read((char*)&temp, sizeof(Tool))) {
            if (file.fail()) break;
            if(temp.getTid() != userInput) {
                newFile.write((char*)&temp, sizeof(Tool));
            }
        }

        file.close(); newFile.close();
        remove("hardware.dat");
        int naming = rename("hardwareTemp.dat", "hardware.dat");
        if (naming == 0) { // If naming was successful...
            cout << "Operation successful.\n" << endl;
            file.open("hardware.dat", ios::binary | ios::in | ios::out);
        }
    } else {
        cout << "Invalid input. Returning to main menu...\n" << endl;
    }
}

void updateTool(fstream& file) {
    if(!file.is_open())
        file.open("hardware.dat", ios::binary | ios::out | ios::in);

    int tid, quantity;
    char name[10];
    double cost;
    cout << "Input the TID to be updated: ";
    if(cin >> tid) {
        file.seekg((int)sizeof(Tool) * (tid - 1), ios::beg);
        cout << "Input the new info in \"name quantity cost\" format: ";
        if (cin >> name >> quantity >> cost) {
            Tool temp = Tool(tid, name, quantity, (double)cost);
            file.write((char*)&temp, sizeof(Tool));
        }
    } else {
        cout << "Invalid input. Returning to main menu...\n" << endl;
    }
}