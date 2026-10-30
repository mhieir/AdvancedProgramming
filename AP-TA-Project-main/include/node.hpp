#ifndef NODE_INCLUDE
#define NODE_INCLUDE

#include "global.hpp"

class Node {
public:
    Node();
    ~Node() {};
    void setType(OperationType operation_type);
    void addChild(Node* child, bool force);
    bool processQuery(unordered_set<Node*> query_nodes);
    void setParent(Node* par);

private:
    vector<pair<Node*, bool>> children;
    bool (*validator)(vector <bool>) = nullptr;
    Node* parent;
};

#endif