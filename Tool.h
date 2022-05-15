//
// Created by lvas4 on 5/14/2022.
//

#ifndef CS170_ASSIGNMENT3_TOOL_H
#define CS170_ASSIGNMENT3_TOOL_H
#include <string>
#include <fstream>
using namespace std;

class Tool {
private:
    int tid;
    char name[15];
    int quantity;
    double cost;

public:

    Tool(int tid, const char *name, int quantity, double cost);

    int getTid() const;

    void setTid(int newTid);

    const char *getName() const;

    int getQuantity() const;

    void setQuantity(int newQuantity);

    double getCost() const;

    void setCost(double newCost);

    void toFile(ofstream& file);

    bool readFile(ifstream& file);

    void printFormatted();

};


#endif //CS170_ASSIGNMENT3_TOOL_H
