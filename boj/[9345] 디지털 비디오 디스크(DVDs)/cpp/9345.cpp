#include <iostream>
#include <climits>
#define endl '\n'
#define ll long long
#define pll pair<ll, ll>
#define ff first
#define ss second
using namespace std;
constexpr size_t MAX_N = 1e5;
ll arr[MAX_N];
pll seg[MAX_N * 4];
ll N, K;

pll seg_init(ll n, ll s, ll e){
    if(s == e) return seg[n] = {arr[s], arr[s]};
    ll m = s + (e - s) / 2;
    pll l = seg_init(n*2, s, m), r = seg_init(n*2 + 1, m + 1, e);
    return seg[n] = {min(l.ff, r.ff), max(l.ss, r.ss)};
}

void seg_update(ll n, ll s, ll e, ll idx){
    // 1. 범위 밖
    if(s > idx || e < idx) return;
    if(s == e) {
        seg[n] = {arr[idx], arr[idx]};
        return;
    }

    ll m = s + (e - s) / 2;
    seg_update(n*2, s, m, idx);
    seg_update(n*2 + 1, m + 1, e, idx);

    seg[n] = {min(seg[n*2].ff, seg[n*2 + 1].ff), max(seg[n*2].ss, seg[n*2 + 1].ss)};
    return;
}


pll seg_query(ll n, ll s, ll e, ll qs, ll qe){
    // 1. 전혀 안 겹칠 경우
    if(qe < s || e < qs) return {INT_MAX, INT_MIN};

    // 2. 트리가 쿼리에 완전히 겹칠 경우
    if(s >= qs && e <= qe) return seg[n];

    // 3. 일부 겹칠 경우
    ll m = s + (e - s) / 2;
    pll l = seg_query(n * 2, s, m, qs, qe), r = seg_query(n * 2 + 1, m + 1, e, qs, qe);

    return {min(l.ff, r.ff), max(l.ss, r.ss)};
}

void run(){
    cin >> N >> K;
    for(ll i = 0; i < N; ++i) arr[i] = i;
    seg_init(1, 0, N - 1);

    ll q, a, b;
    while(K--){
        cin >> q >> a >> b;
        switch (q) {
            case 0: // update
                swap(arr[a], arr[b]);
                seg_update(1, 0, N - 1, a);
                seg_update(1, 0, N - 1, b);
                break;

            case 1: // query
                pll qry = seg_query(1, 0, N - 1, a, b);
                (qry.ff == a && qry.ss == b) ? cout << "YES" << endl : cout << "NO" << endl;
                break;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll T; cin >> T;

    while(T--){
        run();
    }

    return 0;
}