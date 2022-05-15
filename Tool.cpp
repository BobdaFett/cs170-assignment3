//
// Created by lvas4 on 5/14/2022.
//

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Tool.h"

int Tool::getTid() const {
    return tid;
}

void Tool::setTid(int newTid) {
    Tool::tid = newTid;
}

int Tool::getQuantity() const {
    return quantity;
}

void Tool::setQuantity(int newQuantity) {
    Tool::quantity = newQuantity;
}

double Tool::getCost() const {
    return cost;
}

void Tool::setCost(double newCost) {
    Tool::cost = newCost;
}

void Tool::toFile(ofstream &file) {
    if(file)
        file << tid << " " << name << " " << quantity << " " << cost << endl;
}

bool Tool::readFile(ifstream& file) {
    if(file && !file.eof()) {
        file >> tid >> name >> quantity >> cost;
        return true;
    } else return false;
}

void Tool::printFormatted() {
    cout << setw(3) << tid << setw(15) << name << setw(5) << quantity << setw(3) << "$"
        << setprecision(2) << fixed << (double)cost << endl;
}

Tool::Tool(int tid, const char *name, int quantity, double cost) {
    this->tid = tid;
    this->quantity = quantity;
    this->cost = cost;
    strcpy(this->name, name);
}

const char *Tool::getName() const {
    return name;
}
