#include <iostream>
using namespace std;

constexpr size_t MAX_NN = 100000;
int tree[MAX_NN * 4], lazy[MAX_NN * 4];

void seg_init(int n, int s, int e){
    if (s == e) { tree[n] = 0; return; }
    int m = s + (e - s) / 2;
    seg_init(n * 2, s, m);
    seg_init(n * 2 + 1, m + 1, e);
    tree[n] = tree[n * 2] + tree[n * 2 + 1];
}

inline void push_down(int n, int s, int e){
    if (lazy[n] & 1){
        tree[n] = (e - s + 1) - tree[n];   // 구간 길이 - 현재 1의 개수
        if (s != e){
            lazy[n * 2] ^= 1;
            lazy[n * 2 + 1] ^= 1;
        }
        lazy[n] = 0;
    }
}

void seg_update(int n, int s, int e, int l, int r){
    push_down(n, s, e);
    if (e < l || r < s) return;                   // 미포함
    if (l <= s && e <= r){                        // 완전 포함
        lazy[n] ^= 1;
        push_down(n, s, e);
        return;
    }
    int m = s + (e - s) / 2;
    seg_update(n * 2, s, m, l, r);
    seg_update(n * 2 + 1, m + 1, e, l, r);
    tree[n] = tree[n * 2] + tree[n * 2 + 1];
}

int seg_query(int n, int s, int e, int l, int r){
    push_down(n, s, e);
    if (e < l || r < s) return 0;                 // 미포함
    if (l <= s && e <= r) return tree[n];         // 완전 포함
    int m = s + (e - s) / 2;
    return seg_query(n * 2, s, m, l, r) +
           seg_query(n * 2 + 1, m + 1, e, l, r);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M; 
    if (!(cin >> N >> M)) return 0;
    seg_init(1, 0, N - 1);

    while (M--){
        int cmd, s, t;
        cin >> cmd >> s >> t;
        if (s > t) swap(s, t); // 혹시 모를 역순 방지
        --s; --t;              // 0-based 변환
        if (cmd == 0) seg_update(1, 0, N - 1, s, t);
        else          cout << seg_query(1, 0, N - 1, s, t) << '\n';
    }
    return 0;
}
