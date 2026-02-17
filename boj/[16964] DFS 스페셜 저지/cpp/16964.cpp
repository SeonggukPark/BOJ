#include <iostream>
#include <vector>
#include <stack>
#define endl '\n'
using namespace std;
int N;

vector<int> seq, comp_seq;
vector<vector<int>> adjs, ord_adjs;

void init() {
    cin >> N;
    seq.resize(N), adjs.resize(N + 1), ord_adjs.resize(N + 1);

    int n_1, n_2;
    for(int rpt = 0; rpt < N - 1; ++rpt) {
        cin >> n_1 >> n_2;
        adjs[n_1].push_back(n_2);
        adjs[n_2].push_back(n_1);
    }

    for(int idx = 0; idx < N; ++idx) cin >> seq[idx];

    for(const int & i : seq){
        for(const int & tar : adjs[i]){
            ord_adjs[tar].push_back(i);
        }
    }

}

void run() {
    stack<int> stk;
    vector<bool> visited(N + 1, false);
    stk.push(1);

    while(!stk.empty()){
        auto top = stk.top(); stk.pop();
        visited[top] = true;
        comp_seq.push_back(top);

        for(int idx = (int)ord_adjs[top].size() - 1; idx >= 0; --idx) {
            int next = ord_adjs[top][idx];
            if (visited[next]) continue;
            stk.push(next);
        }
    }

    (comp_seq == seq) ? cout << 1 : cout << 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    run();
    return 0;
}
