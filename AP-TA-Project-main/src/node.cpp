#include "node.hpp"

Node::Node() {

}

bool Node::processQuery(unordered_set<Node*> query_nodes) {
    if(!query_nodes.count(parent))return 0;
    vector<bool> result;
    for(auto child : children) {
        if(child.second) result.push_back(query_nodes.count(child.first));
    }
    if(validator == nullptr)return 1;
    return validator(result);
}

bool andValidator(vector<bool> status) {
    bool ans = 1;
    for(auto st : status) {
        ans &= st;
    }
    return ans;
}

bool orValidator(vector<bool> status) {
    bool ans = 1;
    for(auto st : status) {
        ans |= st;
    }
    return ans;
}

bool xorValidator(vector<bool> status) {
    int cnt = 0;
    for(auto st : status) {
        cnt += st;
    }
    return cnt == 1;
}

void Node::setParent(Node* par){
    parent = par;
}

void Node::setType(OperationType operation_type) {
    switch (operation_type) {
    case _AND:
        validator = andValidator;
        break;
    case _OR:
        validator = orValidator;
        break;
    case _XOR:
        validator = xorValidator;
        break;
    default:
        break;
    }
}

void Node::addChild(Node* child, bool force) {
    children.push_back({child, force});
}