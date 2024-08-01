#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define pii pair<int, int>
#define x first
#define y second
using namespace std;
constexpr size_t MAX_N = 1e6;
constexpr int INF = 1e9 + 1;
ll arr[MAX_N + 1];
ll seg_node[MAX_N * 4 + 1]; // max, min 순

ll init_seg(ll node, ll l, ll r){
    if(l == r) return seg_node[node] = arr[l];
    ll m = l + (r - l) / 2;
    ll a = init_seg(node * 2, l, m);
    ll b = init_seg(node * 2 + 1, m + 1, r);
    return seg_node[node] = a + b;
}

ll query(ll node, ll tl, ll tr, ll ql, ll qr){
    // 1. 아예 안 겹침
    if(tr < ql || tl > qr) return 0;

    // 2. 완전 포함
    if (tl >= ql && tr <= qr) return seg_node[node];

    // 3. 일부 포함
    int m = tl + (tr - tl) / 2;
    ll a = query(node * 2, tl, m, ql, qr);
    ll b = query(node * 2 + 1, m + 1, tr, ql, qr);
    return a + b;
}

ll update(ll node, ll l, ll r, ll ti, ll val){
    // 1. out of bound
    if(l > ti || r < ti) return seg_node[node];
    // 2. in bound
    // 업데이트 노드 그 자체일 경우
    if(l == r) {
        return seg_node[node] = val;
    }

    ll m = l + (r - l) / 2;
    ll a = update(node * 2, l, m, ti, val);
    ll b = update(node * 2 + 1, m + 1, r, ti, val);
    return seg_node[node] = a + b;
}


void init(){
    memset(arr, 0, sizeof(arr));
}

void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    init_seg(1, 0, n - 1);

    ll que, a, b;
    ll tmp;
    for (int i = 0; i < m + k; ++i) {
        cin >> que >> a >> b;

        switch (que) {
            case 1:
                update(1, 1, n, a, b);
                break;
            case 2:
                tmp = query(1, 1, n, a, b);
                // traverse(n);
                cout << tmp << endl;
                break;

            default:
                cout << "error occured.. " << endl;
                break;
        }
    }
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}