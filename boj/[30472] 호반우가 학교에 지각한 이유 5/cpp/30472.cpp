#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define endl '\n'
#define x first
#define y second
using namespace std;

struct tup{
    ll inc, dif;
};

struct cmp{
    bool operator()(const tup & a, const tup & b){
        if(a.dif != b.dif) return a.dif < b.dif;
        return a.inc < b.inc;
    }
};

priority_queue<tup, vector<tup>, cmp> pq;

void solve(){
    ll N, a, b;
    cin >> N;

    for (int i = 0; i < N; ++i) {
        cin >> a >> b;
        pq.push({a, a - b});
    }

    ll cur_hei = 0, acc = 0;
    while(!pq.empty()){
        tup top = pq.top();
        pq.pop();

        acc += cur_hei + top.inc;
        cur_hei += top.dif;
    }

    if(cur_hei < 0) acc -= N * cur_hei;
    cout << acc;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}