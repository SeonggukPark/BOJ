/* ---------- Headers ---------- */
#include <iostream>
#include <algorithm>
#define endl '\n'
#define ll long long
using namespace std;
constexpr size_t MAX_N = 2e6;
ll tree[MAX_N*4];

void seg_build(ll n, ll s, ll e){
    if(s == e) {
        tree[n] = 1;
        return;
    }
    ll m = s + (e - s) / 2;
    seg_build(n*2, s, m), seg_build(n*2 + 1, m + 1, e);
    tree[n] = tree[n*2] + tree[n*2 + 1];
}

void seg_update(ll n, ll s, ll e, ll idx){
    // idx가 범위 밖인 경우
    if(s > idx || e < idx) return;
    if(s == e) {
        tree[n]++;
        return;
    }
    ll m = s + (e - s) / 2;
    seg_update(n*2, s, m, idx);
    seg_update(n*2 + 1, m + 1, e, idx);
    tree[n] = tree[n*2] + tree[n*2 + 1];
    return;
}

ll seg_query(ll n, ll s, ll e, ll idx){
    if(s == e){
        tree[n] -= 1;
        return s;
    }

    ll ans, m = s + (e - s) / 2;
    ll left_cnt = tree[n*2];
    if(idx <= left_cnt) ans = seg_query(n*2, s, m, idx);
    else ans = seg_query(n*2 + 1, m + 1, e, idx-left_cnt);

    tree[n] = tree[n*2] + tree[n*2 + 1];
    return ans;
}

void solve(){
    ll N, K, k = K;
    cin >> N >> K;
    seg_build(1, 1, N);
    cout << "<";

    ll idx = 0;
    for(ll i = N; i >= 1; --i){
        idx = (idx + K - 1) % i;
        cout << seg_query(1, 1, N, idx + 1);
        if(i != 1) cout << ", ";
    }

    cout << ">";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
