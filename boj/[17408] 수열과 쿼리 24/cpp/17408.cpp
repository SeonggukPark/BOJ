#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define pii pair<int, int>
#define x first
#define y second
using namespace std;
constexpr size_t MAX_N = 1e6;
constexpr int INF = 1e9 + 1;
int arr[MAX_N + 1];
pii seg_node[MAX_N * 4 + 1]; // max, min 순

pii init_seg(int node, int l, int r){
    if(l == r) return seg_node[node] = {arr[l], 0};
    int m = l + (r - l) / 2;
    pii a = init_seg(node * 2, l, m);
    pii b = init_seg(node * 2 + 1, m + 1, r);

    int max_f = max(a.x, b.x);
    int max_s = (max_f == a.x) ? b.x : a.x;
    max_s = max(max_s, max(a.y, b.y));

    return seg_node[node] = {max_f, max_s};
}

pii query(int node, int tl, int tr, int ql, int qr){
    // 1. 아예 안 겹침
    if(tr < ql || tl > qr) return {0, 0};

    // 2. 완전 포함
    if (tl >= ql && tr <= qr) return seg_node[node];

    // 3. 일부 포함
    int m = tl + (tr - tl) / 2;
    pii a = query(node * 2, tl, m, ql, qr);
    pii b = query(node * 2 + 1, m + 1, tr, ql, qr);

    int max_f = max(a.x, b.x);
    int max_s = (max_f == a.x) ? b.x : a.x;
    max_s = max(max_s, max(a.y, b.y));

    return {max_f, max_s};
}

pii update(int node, int l, int r, int ti, int val){
    // 1. out of bound
    if(l > ti || r < ti) return seg_node[node];
    // 2. in bound
    // 업데이트 노드 그 자체일 경우
    if(l == r) {
        return seg_node[node] = {val, 0};
    }

    int m = l + (r - l) / 2;
    pii a = update(node * 2, l, m, ti, val);
    pii b = update(node * 2 + 1, m + 1, r, ti, val);

    int max_f = max(a.x, b.x);
    int max_s = (max_f == a.x) ? b.x : a.x;
    max_s = max(max_s, max(a.y, b.y));

    return seg_node[node] = {max_f, max_s};
}


void init(){
    memset(arr, 0, sizeof(arr));
}

void solve(){
    int n, q;
    cin >> n;
    for (ll i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    init_seg(1, 0, n - 1);

    cin >> q;
    pii top;
    for (int i = 0; i < q; ++i) {
        int a, b, c;
        cin >> a >> b >> c;

        switch (a) {
            case 1:
                update(1, 1, n, b, c);
                break;

            case 2:
                top = query(1, 1, n, b, c);
                cout << top.x + top.y << endl;
                break;

            default:
                break;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}