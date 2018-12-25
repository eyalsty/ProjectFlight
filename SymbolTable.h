#ifndef PROJECT1_SYMBOLTABLE_H
#define PROJECT1_SYMBOLTABLE_H

#include <map>
#include <string>
#include <vector>
#include <set>
#include "ConnectCommand.h"

using namespace std;

class SymbolTable {
private:
    map<string, double> symTbl;
    map<string, string> pathTbl;
    ConnectCommand *client;

    vector<string> splitVars(string s);

public:
    explicit SymbolTable(ConnectCommand *client) : client(client) {}
    void setVar(string var, double val);

    void setPath(string var, string path);

    double getVal(string var);

    string getPath(string var);

    bool isVarExist(string var);

    bool isPathExists(string var);

    string switchVarsToVals(string s);

    void updateFromSimulator(double num, string path);

};

#endif