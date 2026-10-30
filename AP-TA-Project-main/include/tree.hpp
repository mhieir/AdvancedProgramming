#ifndef TREE_INCLUDE
#define TREE_INCLUDE

#include "global.hpp"
#include "node.hpp"

class Tree {
public:
    Tree();
    ~Tree();
    void run(InputData inputs);
    vector<bool> getOutput();
private:
    vector<bool> answer;
    bool handleQuery(vector<string> query);
    void handleQueries(vector<vector<string>> queries);
    void makeTree(vector<Equation> equations);
    Node* getNode(string node_name);
    map<string, Node*> nodes;
};

#endif