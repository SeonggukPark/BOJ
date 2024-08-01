#include <bits/stdc++.h>
#define endl '\n'
#define pii pair<int, int>
#define x first
#define y second
using namespace std;
constexpr size_t MAX_N = 1e5;
constexpr int INF = 1e9 + 1;
int arr[MAX_N + 1];
pii seg_node[MAX_N * 4 + 1]; // max, min 순

void traverse(int n){
    for (int i = 1; i <= 4 * n; ++i) {
        cout << "seg[" << i << "]: " << seg_node[i].first << ' ' <<seg_node[i].second << endl;
    }

}

pii init_seg(int node, int l, int r){
    if(l == r) return seg_node[node] = {arr[l], arr[l]};
    int m = l + (r - l) / 2;
    pii a = init_seg(node * 2, l, m);
    pii b = init_seg(node * 2 + 1, m + 1, r);
    return seg_node[node] = {max(a.x, b.x), min(a.y, b.y)};
}

pii query(int node, int tl, int tr, int ql, int qr){
    // 1. 아예 안 겹침
    if(tr < ql || tl > qr) return {0, INF};

    // 2. 완전 포함
    if (tl >= ql && tr <= qr) return seg_node[node];

    // 3. 일부 포함
    int m = tl + (tr - tl) / 2;
    pii a = query(node * 2, tl, m, ql, qr);
    pii b = query(node * 2 + 1, m + 1, tr, ql, qr);
    return {max(a.x, b.x), min(a.y, b.y)};
}

pii update(int node, int l, int r, int ti, int val){
    // 1. out of bound
    if(l > ti || r < ti) return seg_node[node];
    // 2. in bound
    // 업데이트 노드 그 자체일 경우
    if(l == r) {
        return seg_node[node] = {val, val};
    }

    int m = l + (r - l) / 2;
    pii a = update(node * 2, l, m, ti, val);
    pii b = update(node * 2 + 1, m + 1, r, ti, val);

    // if(node == 2) cout << "a, b: " << a.x << ' ' << a.y << ' ' << b.x << ' ' << b.y << endl;

    return seg_node[node] = {max(a.x, b.x), min(a.y, b.y)};
}


void init(){
    memset(arr, 0, sizeof(arr));
}

void solve(){
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    init_seg(1, 0, n - 1);

    int que, a, b;
    pii tmp;
    for (int i = 0; i < q; ++i) {
        cin >> a >> b;
        cout << query(1, 1, n, a, b).y << ' ' << endl;
        // cout << query(1, 1, n, a, b).y << ' ' << query(1, 1, n, a, b).x << endl;
    }
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}