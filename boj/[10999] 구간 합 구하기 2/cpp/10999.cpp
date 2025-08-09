/* ---------- Headers ---------- */
#include <iostream>
#define endl '\n'
#define ll long long
using namespace std;
constexpr size_t MAX_N = 1e6;
ll arr[MAX_N], tree[MAX_N*4], lazy[MAX_N*4];

ll seg_build(ll n, ll s, ll e){
    if(s == e) return tree[n] = arr[s];
    ll m = s + (e - s) / 2;
    return tree[n] = seg_build(n*2, s, m) + seg_build(n*2 + 1, m + 1, e);
}


void push_down(ll n, ll s, ll e){
    if(lazy[n] == 0) return;
    tree[n] += (e - s + 1) * lazy[n];
    if(s != e) {
        lazy[n*2] += lazy[n];
        lazy[n*2 + 1] += lazy[n];
    }
    lazy[n] = 0;
}

void seg_update(ll n, ll s, ll e, ll l, ll r, ll val){
    push_down(n, s, e);
    if(r < s || l > e) return; // 1. 완전 불일치

    if(s >= l && r >= e) {// 2. 트리가 쿼리 구간에 완전 포함
        lazy[n] += val;
        push_down(n, s, e);
        return;
    }

    ll m = s + (e - s) / 2; // 3. 일부 겹침
    seg_update(n*2, s, m, l, r, val);
    seg_update(n*2 + 1, m+1, e, l, r, val);
    tree[n] = tree[n*2] + tree[n*2 + 1];
}

ll seg_query(ll n, ll s, ll e, ll l, ll r){
    push_down(n, s, e);
    if(r < s || l > e) return 0; // 1. 완전 불일치
    if(s >= l && r >= e) return tree[n];
    ll m = s + (e - s) / 2; // 3. 일부 겹침
    return seg_query(n*2, s, m, l, r) + seg_query(n*2 + 1, m + 1, e, l, r);
}

void solve(){
    ll N, M, K;
    cin >> N >> M >> K;
    for(ll i = 0; i < N; ++i) cin >> arr[i];
    seg_build(1, 0, N - 1);

    ll cmd, a, b, c;
    for(ll i = 0; i < M + K; ++i){
        cin >> cmd >> a >> b;
        switch (cmd) {
            case 1:
                cin >> c;
                seg_update(1, 0, N - 1, a - 1, b - 1, c);
                break;
            case 2:
                cout << seg_query(1, 0, N - 1, a - 1, b - 1) << endl;
                break;
            default:
                cout << "Error.." << endl;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
