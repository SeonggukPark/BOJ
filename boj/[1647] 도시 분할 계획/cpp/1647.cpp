#include <iostream>
#include <queue>
using namespace std;
constexpr size_t MAX_N = 1e5;
int n, m;
int parent[MAX_N + 1], ran[MAX_N + 1], min_dist, max_dist;

int Find(int u){
    if(u == parent[u]) return u;
    return parent[u] = Find(parent[u]);
}

void Merge(int u, int v){
    u = Find(u), v = Find(v);
    if (u == v) return;
    if (ran[u] > ran[v]) swap(u, v);
    parent[u] = v;
    if (ran[u] == ran[v]) ran[v]++;
}

struct graph{
    int s, e, w;
};

struct cmp{
    bool operator()(const graph & a, const graph & b){
        if(a.w != b.w) return a.w > b.w;
        return a.s > b.s;
    }
};

void init(){
    for(int i = 1; i <= n; i++){
        parent[i] = i;
        ran[i] = 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    init();
    int l, r, w;

    priority_queue<graph, vector<graph>, cmp> pq;
    while(m--){
        cin >> l >> r >> w;
        pq.push({l, r, w});
    }

    while(!pq.empty()){
        auto top = pq.top();
        pq.pop();
        if(Find(top.s) == Find(top.e)) continue;
        min_dist += top.w;
        Merge(top.s, top.e);
        max_dist = max(max_dist, top.w);
    }

    min_dist -= max_dist;
    cout << min_dist << endl;
    return 0;
}