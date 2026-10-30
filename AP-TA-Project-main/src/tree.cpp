#include "tree.hpp"

Tree::Tree() {

}

Tree::~Tree() {
    for(auto [name, node] : nodes) {
        delete node;
    }
}

Node* Tree::getNode(string node_name) {
    if (nodes.count(node_name) == 0) {
        nodes[node_name] = new Node();
    }
    return nodes[node_name];
}

bool Tree::handleQuery(vector<string> query) {
    unordered_set<Node*> query_nodes;
    for(string name : query) {
        Node* node_name = getNode(name);
        query_nodes.insert(node_name);
    }

    bool ans = true;
    for(auto query_node : query_nodes) {
        ans &= query_node-> processQuery(query_nodes);
    }
    return ans;
}

void Tree::handleQueries(vector<vector<string>> queries) {
    for(vector<string> query : queries) {
        answer.push_back(handleQuery(query));
    }
}

void Tree::makeTree(vector<Equation> equations) {
    for(Equation equation : equations) {
        Node* root = getNode(equation.root);
        root->setType(equation.operation_type);
        for(int i = 0; i < equation.children.size(); i++) {
            root->addChild(getNode(equation.children[i]), equation.force[i]);
            getNode(equation.children[i])->setParent(root);
        }
    }
    getNode(equations[0].root)->setParent(getNode(equations[0].root));
}

void Tree::run(InputData inputs) {
    makeTree(inputs.first);
    handleQueries(inputs.second);
}

vector<bool> Tree::getOutput() {
    return answer;
}