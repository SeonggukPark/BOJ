#include <iostream>
#include <vector>
#define ll long long
using namespace std;
constexpr size_t MAX_N = 1e6;
ll arr[MAX_N], seg[MAX_N * 4];

ll seg_init(ll n, ll s, ll e){
    if(s == e) return seg[n] = arr[s];
    ll m = s + (e - s) / 2;
    ll l = seg_init(n * 2, s, m), r = seg_init(n * 2 + 1, m + 1, e);
    return seg[n] = l + r;
}
/*
ll seg_update(ll n, ll s, ll e, ll idx, ll val){
    // 1. 범위 밖
    if(s > idx || e < idx) return 0;
    seg[n] += val;
    if(s == e) return seg[n];

    ll m = s + (e - s) / 2;
    return seg_update(n*2, s, m, idx, val) + seg_update(n*2 + 1, m + 1, e, idx, val);
}
*/
void seg_update(ll n, ll s, ll e, ll idx, ll val){
    // 1. 범위 밖
    if(s > idx || e < idx) return;
    if(s == e){
        seg[n] = val;
        return;
    };

    ll m = s + (e - s) / 2;
    seg_update(n*2, s, m, idx, val);
    seg_update(n*2 + 1, m + 1, e, idx, val);
    seg[n] = seg[n*2] + seg[n*2 + 1];
}

ll seg_query(ll n, ll s, ll e, ll qs, ll qe){
    // 1. 전혀 안 겹칠 경우
    if(qe < s | e < qs) return 0;

    // 2. 트리가 쿼리에 완전히 겹칠 경우
    if(s >= qs && e <= qe) return seg[n];

    // 3. 일부 겹칠 경우
    ll m = s + (e - s) / 2;
    return seg_query(n * 2, s, m, qs, qe) + seg_query(n * 2 + 1, m + 1, e, qs, qe);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("input.txt", "r", stdin);
    ll N, M, K;
    cin >> N >> M >> K;
    for(int i = 0; i < N; ++i) cin >> arr[i];
    seg_init(1, 0, N - 1);

    ll a, b, c;
    for(ll i = 0; i < M + K; ++i){
        cin >> a >> b >> c;
        switch (a) {
            case 1: // update
                seg_update(1, 0, N - 1, b - 1, c);
                break;

            case 2: // query
                cout << seg_query(1, 0, N - 1, b - 1, c - 1) << endl;
                break;

            default:
                cout << "Error Occured.." << endl;
                break;
        }
    }

    return 0;
}