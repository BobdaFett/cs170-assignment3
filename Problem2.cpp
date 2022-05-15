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
             << "Please input your choice: ";
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
    // Add warning that this will overwrite original file if there is one.
    file.open("hardware.dat", ios::binary | ios::out | ios::in | ios::trunc);
    for(int i = 0; i < 100; i++) {
        Tool temp = Tool(i+1, "default", 0, 0);
        file.write((char*)&temp, sizeof(Tool));
    }
}

void fromTxt(fstream& file) {
    if(!file.is_open()) {
        file.open("hardware.dat", ios::binary | ios::out | ios::in);
        if(!file) {
            cout << "Please create a new file from the main menu first." << endl;
            file.clear();
            main();
        }
    }
    ifstream toRead;
    string userInput;
    cout << "Please enter the name of the \"*.txt\" to read: ";
    cin >> userInput;
    toRead.open(userInput + ".txt", ios::in);

    Tool temp = Tool(0, "", 0, 0);

    if(toRead) {
        while (temp.readFile(toRead)) {
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

    cout << "Please input the data you would like to input in \"ID name quantity cost\" format: ";
    if (cin >> tid >> name >> quantity >> cost) {
        Tool temp = Tool(tid, name, quantity, cost);
        if(file.read((char*)&temp, sizeof(Tool)) && temp.getTid() == tid) {
            cout << "This will overwrite another tool. Please use the \"Update Tool\" function from the main menu." << endl;
            file.clear();
        } else {
            temp = Tool(tid, name, quantity, cost);
            file.clear();
            file.seekg(-sizeof(Tool), ios::cur);
            file.write((char*)&temp, sizeof(Tool));
        }
    }
}

void listTools(fstream& file) {
    if(!file.is_open())
        file.open("hardware.dat", ios::binary | ios::out | ios::in);
    file.seekg(0, ios::beg);
    string name;
    int id, quantity;
    double cost;
    Tool temp = Tool(0, "", 0, 0);
    file.seekg(0, ios::beg);
    while(file.read((char*)&temp, sizeof(Tool))) {
        if (file.fail()) break;
        temp.printFormatted();
    }
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

        while(file.read((char*)&temp, sizeof(Tool))) {
            if (file.fail()) break;
            if(temp.getTid() != userInput) {
                newFile.write((char*)&temp, sizeof(Tool));
            }
        }

        // Neither the remove nor rename functions are working?
        remove("hardware.dat");
        int naming = rename("hardwareTemp.dat", "hardware.dat");
        if (naming == 0) cout << "Operation successful." << endl;
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
        file.seekg(sizeof(Tool) * (tid - 1), ios::beg);
        cout << "Input the new info in (name quantity cost) format: ";
        if (cin >> name >> quantity >> cost) {
            Tool temp = Tool(tid, name, quantity, (double)cost);
            file.write((char*)&temp, sizeof(Tool));
        }
    }
}