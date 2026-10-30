// in God we trust <3

#ifndef GLOBAL_INCLUDE
#define GLOBAL_INCLUDE

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <cstring>
#include <sstream>

using namespace std;

const string END_OF_PROBLEM = "###";
const string END_OF_TEST = "##";
const string END_OF_CONFIG = "#";
const string END_LINE = "+++";
const string NULL_STRING = "";
const string VALID = "Valid";
const string INVALID = "Invalid";
const char SPACE = ' ';
const char CURLY_BRACE_LEFT = '{';
const char CURLY_BRACE_RIGHT = '}';
const char COMMA = ',';
const int FIRST_WORD = 0;

enum OperationType {
    _AND,
    _OR,
    _XOR
};

struct Equation {
    string root;
    vector<string> children;
    vector<bool> force;
    OperationType operation_type;
};

typedef pair<vector<Equation>, vector<vector<string>>> InputData;
#define AllOne vector<bool> (result.children.size(), true);

#endif