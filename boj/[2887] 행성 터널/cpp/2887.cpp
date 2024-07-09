#include <bits/stdc++.h>
// #define endl '\n'
using namespace std;
constexpr size_t MAX_N = 2e5;
struct edge{
    int s, e, d;
};

struct pos{
    int p, idx;
};

struct cmp1{
    bool operator()(const edge & a, const edge & b){
        return a.d > b.d;
    }
};

bool cmp2(const pos & a, const pos & b){
    return a.p < b.p;
}

priority_queue<edge, vector<edge>, cmp1> pq;
vector<pos> v[3];

int par[MAX_N], ran[MAX_N];

void init(){
    for (int i = 0; i < MAX_N; ++i) {
        par[i] = i;
    }
}

int Find(int x){
    if(par[x] == x) return x;
    return par[x] = Find(par[x]);
}

void Union(int x, int y){
    x = Find(x), y = Find(y);
    if(x == y) return;
    if(ran[x] > ran[y]) swap(x, y);
    par[x] =  y;
    if(ran[x] == ran[y]) ran[y]++;
}

bool is_cycle(int x, int y){
    x = Find(x), y = Find(y);
    return x == y;
}


void sol(){
    int n; cin >> n;
    pq = {};
    for(auto & i : v) i.clear();

    int x, y, z, tot = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y >> z;
        v[0].push_back({x, i}), v[1].push_back({y, i}), v[2].push_back({z, i});
    }

    for(auto & i : v){
        sort(i.begin(), i.end(), cmp2);
    }

    for (int i = 0; i < n - 1; ++i) {
        for (auto & j : v) {
            pq.push({j[i].idx, j[i + 1].idx, abs(j[i].p - j[i + 1].p)});
        }
    }

    int acc = 0;
    while(!pq.empty()){
        auto top = pq.top();
        pq.pop();

        if(!is_cycle(top.s, top.e)){
            // cout << top.s << ' ' <<top.e << ' ' <<top.d << endl;
            acc += top.d;
            Union(top.s, top.e);
        }
    }

    cout << acc << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    sol();
    return 0;
}
