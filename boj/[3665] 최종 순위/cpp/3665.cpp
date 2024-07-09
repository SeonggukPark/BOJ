#include <bits/stdc++.h>
// #define endl '\n'
using namespace std;
constexpr size_t MAX_N = 500;
int indegree[MAX_N + 1];
bool graph[MAX_N + 1][MAX_N + 1];
queue<int> q, rst;

void init(){
    memset(indegree, 0, sizeof(indegree));
    memset(graph, false, sizeof(graph));
    q = {}, rst = {};
}

void sol(){
    int n, m, x, y; cin >> n;
    vector<int> v_rank;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        v_rank.push_back(x);
    }

    for(int i = 0; i < v_rank.size(); i++){
        auto tar = v_rank[i];
        indegree[tar] = i;
        for (int j = i + 1; j < v_rank.size(); ++j) {
            graph[tar][v_rank[j]] = true;
        }
    }

    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        if(graph[x][y]){
            graph[x][y] = false, graph[y][x] = true;
            indegree[x]++, indegree[y]--;
        }

        else{
            graph[x][y] = true, graph[y][x] = false;
            indegree[x]--, indegree[y]++;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if(indegree[i] == 0) q.push(i);
    }

    for(int i = 1; i <= n; ++i){
        // 1. q가 빈 경우 -> 사이클 발생시
        if(q.empty()){
            cout << "IMPOSSIBLE" << endl;
            return;
        }

        // 2. q 원소가 2개 이상일 경우 -> 확실한 순위 X
        if(q.size() >= 2){
            cout << "?" << endl;
            return;
        }

        auto top = q.front();
        q.pop();
        rst.push(top);

        for (int j = 1; j <= n; ++j) {
            if(graph[top][j]) {
                indegree[j]--;
                if(indegree[j] == 0) q.push(j);
            }
        }
    }

    while(!rst.empty()){
        cout << rst.front() << ' ';
        rst.pop();
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        init();
        sol();
    }
    return 0;
}
