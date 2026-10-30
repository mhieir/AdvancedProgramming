// in God we trust <3

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<int>> VVI;

#define maxN 100
#define inf 10000000

void get_input(int& n, int& srcLine, int& srcStation, int& dstLine, int& dstStation, VVI& line) {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> line[i][0];
        for(int j = 1; j <= line[i][0]; j++) {
            cin >> line[i][j];
        }
    }
    cin >> srcLine >> srcStation >> dstLine >> dstStation;
}

void add_edge(int u, int v, VVI& edge) {
    edge[u].push_back(v);
    edge[v].push_back(u);
}

void normal_edges(int n, int& cnt, VVI& line, VVI& edge, VVI& intersection) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= line[i][0]; j++, cnt++) {
            if(j + 1 <= line[i][0]) add_edge(cnt, cnt + 1, edge);
            if(line[i][j]) intersection[i][line[i][j]] = cnt;
        }
    }
}

void add_intersection_edges(int n, int& cnt, VVI& intersection, VVI& edge) {
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if(intersection[i][j]) {
                add_edge(intersection[i][j], cnt, edge);
                add_edge(intersection[j][i], cnt++, edge);
            }
        }
    }
}

void make_graph(int n, int& cnt, VVI& line, VVI& edge, VVI& intersection) {
    normal_edges(n, cnt, line, edge, intersection);
    add_intersection_edges(n, cnt, intersection, edge);
}

void dfs(int v, int dis, vector<int>& ans, VVI& edge) {
    ans[v] = dis;
    for(int u : edge[v]) {
        if(ans[u] > dis + 1) dfs(u, dis + 1, ans, edge);
    }
}

int find_number(int& lineNumber, int stationNumber, VVI& line) {
    int answer = 0;
    for(int i = 1; i < lineNumber; i++) answer += line[i][0];
    return answer + stationNumber;
}

void make_src_dst(int& srcNum, int& dstNum, int srcLine, int dstLine, int srcStation, int dstStation, VVI& line) {
    srcNum = find_number(srcLine, srcStation, line);
    dstNum = find_number(dstLine, dstStation, line);
}

void output(int srcNum, int dstNum, vector<int>& ans, VVI& edge) {
    ans[srcNum] = 0;
    dfs(srcNum, 0, ans, edge);
    cout << ans[dstNum];
}

int main() {
    
    int n, cnt = 1, srcLine, srcStation, srcNum, dstLine, dstStation, dstNum;
    VVI intersection(maxN, vector<int> (maxN)), line(maxN, vector<int> (maxN)), edge(maxN);
    vector<int> ans(maxN, inf); 
    vector<bool> seen(maxN, false);

    get_input(n, srcLine, srcStation, dstLine, dstStation, line);   
    make_graph(n, cnt, line, edge, intersection);
    make_src_dst(srcNum, dstNum, srcLine, dstLine, srcStation, dstStation, line);
    output(srcNum, dstNum, ans, edge);

    return 0;
}
