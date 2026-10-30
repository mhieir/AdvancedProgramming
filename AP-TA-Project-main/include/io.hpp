#ifndef IO_INCLUDE
#define IO_INCLUDE

#include "global.hpp"
#include "tree.hpp"

class Interface {
public:
    Interface();
    ~Interface() {};
    void run();
private:
    vector<string> getInput();
    void showOutput(vector<bool> outputs);
    InputData makeInput(vector<string> inputs);
    vector<string> tokenizeQueries(string line);
    OperationType getType(string line);
    string getRoot(string line);
    vector<bool> getForce(string line);
    vector<string> getChildren(string line);
    Equation tokenizeEquation(string line);
};

#endif