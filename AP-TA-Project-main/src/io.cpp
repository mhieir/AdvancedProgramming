#include "io.hpp"

Interface::Interface() {

}

OperationType Interface::getType(string line){
    OperationType result;
    for(char c : line){
        if(c == '+')
            result = OperationType::_AND;
        if(c == '|')
            result = OperationType::_OR;
        if(c == '^')
            result = OperationType::_XOR;
    }
    return result;
}

string Interface::getRoot(string line){
    string res = "";
    for(char c : line){
        if(c == ' ')
            continue;
        if(c == '=')
            break;
        res += c;
    }
    return res;
}

vector<bool> Interface::getForce(string line){
    vector < bool > force;
    string cur = "";
    bool is_force = 1;
    for(char c : line){
        if(c == '=')
            cur = "";
        else if(c == ' ')
            continue;
        else if(c == '?')
            is_force = 0;
        else if(c == '^' || c == '+' || c == '|')
            force.push_back(is_force), cur = "", is_force = 1;
        else
            cur += c;
    }
    if(cur.size())force.push_back(is_force);
    return force;
}

vector<string> Interface::getChildren(string line){
    vector < string > children;
    string cur = "";
    for(char c : line){
        if(c == '=')
            cur = "";
        else if(c == ' ' || c == '?')
            continue;
        else if(c == '^' || c == '+' || c == '|')
            children.push_back(cur), cur = "";
        else
            cur += c;
    }
    if(cur.size())children.push_back(cur);
    return children;
}

Equation Interface::tokenizeEquation(string line){
    string cur = "";
    Equation result;
    result.root = getRoot(line);
    result.operation_type = getType(line);
    result.children = getChildren(line);
    if(result.operation_type == OperationType::_AND)
        result.force = getForce(line);
    else
        result.force = AllOne;
    return result;
}


vector<string> Interface::tokenizeQueries(string line){
    string cur = NULL_STRING;
    vector <string> result;
    for(char c : line){
        if(c == CURLY_BRACE_LEFT || c == CURLY_BRACE_RIGHT || c == SPACE) {
            continue;
        }
        if(c == COMMA){
            result.push_back(cur);
            cur = NULL_STRING;
        }
        else {
            cur += c;
        }
    }
    if(cur.size())result.push_back(cur);
    return result;
}

InputData Interface::makeInput(vector<string> inputs) {
    bool ask = false;
    vector<vector<string>> query;
    vector<Equation> equation;
    for(string input : inputs) {
        if(input == END_OF_CONFIG) {
            ask = true;
            continue;
        }
        if(!ask) {
            equation.push_back(tokenizeEquation(input));
        }
        else {
            query.push_back(tokenizeQueries(input));
        }
    }
    return make_pair(equation, query);
}

vector<string> Interface::getInput() {
    vector<string> inputs;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) {
            continue;
        }
        if (line == END_OF_PROBLEM || line == END_OF_TEST) {
            break;
        }
        inputs.push_back(line);
    }
    return inputs;
}

void Interface::showOutput(vector<bool> outputs) {
    for(bool output : outputs) {
        cout << ((output) ? VALID : INVALID);
        cout << endl;
    }
    cout << END_LINE << endl;
}

void Interface::run() {
    while(true) {
        vector<string> inputs = getInput();
        InputData input_data = makeInput(inputs);
        if(inputs.empty()) {
            break;
        }
        Tree* tree = new Tree;
        tree->run(input_data);
        showOutput(tree->getOutput());
        delete tree;
    }
}