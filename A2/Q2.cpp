// in God we trust <3

#include <iostream>
#include <string> 
#include <vector>

using namespace std;

#define maxN 100
#define shape1 "|  "
#define shape2 "   "
#define shape3 "|__"
#define start 1
#define childless -1
#define null -1

void get_input(vector<string>& name, vector<int>& parent, int n) {
    for(int i = 1; i <= n; i++) cin >> name[i] >> parent[i];
}

void find_last_child(int current, int n, vector<int>& lastChild, vector<int>& stringLen, vector<bool>& beLastChild, vector<int>& parent) {
    if(current == n + 1) return;
    int dad = parent[current];
    stringLen[current] = 1 + stringLen[dad];
    if(lastChild[dad] != -1) {
        beLastChild[lastChild[dad]] = false;
    }
    lastChild[dad] = current;
    beLastChild[current] = true;
    
    find_last_child(current + 1, n, lastChild, stringLen, beLastChild, parent);
}

void print(vector<int>& stringLen, int& current, vector<string>& name, vector<bool>& flag) {
    for(int i = 0; i < stringLen[current]; i++) {
        if(flag[i]) cout << shape1;
        else cout << shape2;
    }
    cout << shape3 << name[current] << endl;
}

void check_conditions(vector<bool>& beLastChild, vector<int>& lastChild, int& current, vector<bool>& flag, vector<int>& parent, vector<int>& stringLen) {
    if(beLastChild[current]) flag[stringLen[current]] = false;
    if(lastChild[current] != -1) flag[stringLen[current] + 1] = true;
}

void solve(int current, int n, int k, vector<string>& name, vector<int>& parent, vector<bool>& flag, vector<int> stringLen, vector<bool> beLastChild, vector<int> lastChild) {
    if(current >= n + 1) return;
    if(stringLen[current] >= k) {
        solve(current + 1, n, k, name, parent, flag, stringLen, beLastChild, lastChild);
        return;
    }
    
    print(stringLen, current, name, flag);
    check_conditions(beLastChild, lastChild, current, flag, parent, stringLen);
    solve(current + 1, n, k, name, parent, flag, stringLen, beLastChild, lastChild);
}

int main() {
 
    int n, k; cin >> n >> k;
    
    vector<int> parent(maxN, 0), lastChild(maxN, childless), stringLen(maxN, null);
    vector<string> name(maxN);
    vector<bool> beLastChild(maxN, false), flag(maxN, false);

    flag[0] = true;
    get_input(name, parent, n);
    find_last_child(start, n, lastChild, stringLen, beLastChild, parent);
    solve(start, n, k, name, parent, flag, stringLen, beLastChild, lastChild);
    
    return 0;
}
