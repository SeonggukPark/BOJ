/* ---------- Headers ---------- */
#include <iostream>
#define endl '\n'
#define ll long long
using namespace std;
constexpr size_t MAX_N = 1e5;
int N, M;
ll arr[MAX_N], tree[MAX_N*4], lazy[MAX_N*4];

ll seg_build(int n, int s, int e){
    if(s == e) return tree[n] = arr[s];
    int m = s + (e - s) / 2;
    return tree[n] = seg_build(n*2, s, m) + seg_build(n*2 + 1, m + 1, e);
}

void push_down(int n, int s, int e){
    if(lazy[n] == 0) return;
    tree[n] += (e - s + 1) * lazy[n];
    if(s != e) {
        lazy[n*2] += lazy[n];
        lazy[n*2 + 1] += lazy[n];
    }
    lazy[n] = 0;
}

void seg_update(int n, int s, int e, int l, int r, int val){
    push_down(n, s, e);
    if(r < s || l > e) return; // 1. 완전 불일치

    if(s >= l && r >= e) {// 2. 트리가 쿼리 구간에 완전 포함
        lazy[n] += val;
        push_down(n, s, e);
        return;
    }

    int m = s + (e - s) / 2; // 3. 일부 겹침
    seg_update(n*2, s, m, l, r, val);
    seg_update(n*2 + 1, m+1, e, l, r, val);
    tree[n] = tree[n*2] + tree[n*2 + 1];
}

ll seg_query(int n, int s, int e, int l, int r){
    push_down(n, s, e);
    if(r < s || l > e) return 0; // 1. 완전 불일치
    if(s >= l && r >= e) return tree[n];
    int m = s + (e - s) / 2; // 3. 일부 겹침
    return seg_query(n*2, s, m, l, r) + seg_query(n*2 + 1, m + 1, e, l, r);
}

void solve(){
    cin >> N;
    for(int i = 0; i < N; ++i) cin >> arr[i];
    seg_build(1, 0, N - 1);

    cin >> M;
    int cmd, a, b, c;
    while(M--){
        cin >> cmd;
        switch (cmd) {
            case 1: // update
                cin >> a >> b >> c;
                seg_update(1, 0, N - 1, a - 1, b - 1, c);

                break;
            case 2: // query
                cin >> a;
                cout << seg_query(1, 0, N - 1, a - 1, a - 1) << endl;
                break;

            default: // error case
                cout << "Error!" << endl;
                break;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
