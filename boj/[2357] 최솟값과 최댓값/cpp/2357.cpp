#include <iostream>
#include <vector>
#include <climits>
#define endl '\n'
#define ll long long
#define pii pair<int, int>
#define ff first
#define ss second
using namespace std;
constexpr size_t MAX_N = 1e6;
constexpr int DIV = 1000000007;
int arr[MAX_N];
pii seg[MAX_N * 4];

pii seg_init(int n, int s, int e){
    if(s == e) return seg[n] = make_pair(arr[s], arr[s]);
    int m = s + (e - s) / 2;
    pii l = seg_init(n * 2, s, m), r = seg_init(n * 2 + 1, m + 1, e);
    return seg[n] = {min(l.ff, r.ff), max(l.ss, r.ss)};
}
/*
int seg_update(int n, int s, int e, int idx, int val){
    // 1. 범위 밖
    if(s > idx || e < idx) return 0;
    seg[n] += val;
    if(s == e) return seg[n];

    int m = s + (e - s) / 2;
    return seg_update(n*2, s, m, idx, val) + seg_update(n*2 + 1, m + 1, e, idx, val);
}
*/

/*
void seg_update(int n, int s, int e, int idx, int val){
    // 1. 범위 밖
    if(s > idx || e < idx) return;
    if(s == e){
        seg[n] = {};
        return;
    };

    int m = s + (e - s) / 2;
    seg_update(n*2, s, m, idx, val);
    seg_update(n*2 + 1, m + 1, e, idx, val);
    seg[n] = (seg[n*2] * seg[n*2 + 1]) % DIV;
}
*/

pii seg_query(int n, int s, int e, int qs, int qe){
    // 1. 전혀 안 겹칠 경우
    if(qe < s | e < qs) return {INT_MAX, INT_MIN};

    // 2. 트리가 쿼리에 완전히 겹칠 경우
    if(s >= qs && e <= qe) return seg[n];

    // 3. 일부 겹칠 경우
    int m = s + (e - s) / 2;
    pii l = seg_query(n * 2, s, m, qs, qe), r = seg_query(n * 2 + 1, m + 1, e, qs, qe);
    return {min(l.ff, r.ff), max(l.ss, r.ss)};
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    for(int i = 0; i < N; ++i) cin >> arr[i];
    seg_init(1, 0, N - 1);

    int a, b;
    for(int i = 0; i < M; ++i){
        cin >> a >> b;
        pii q = seg_query(1, 0, N - 1, a - 1, b - 1);
        cout << q.ff << ' ' << q.ss << endl;
    }

    return 0;
}