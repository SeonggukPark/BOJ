#include <iostream>
#include <vector>
#include <algorithm>
#define endl '\n'
#define ll long long
#define pii pair<int, int>
#define ff first
#define ss second
using namespace std;
constexpr size_t MAX_N = 5e5;
int arr[MAX_N];
int seg[MAX_N * 4];
vector<pii> vec;

void seg_update(int n, int s, int e, int idx){
    // 1. 범위 밖
    if(s > idx || e < idx) return;
    if(s == e){
        seg[n] = 1;
        return;
    };

    int m = s + (e - s) / 2;
    seg_update(n*2, s, m, idx);
    seg_update(n*2 + 1, m + 1, e, idx);
    seg[n] = seg[n*2] + seg[n*2 + 1];
}


int seg_query(int n, int s, int e, int qs, int qe){
    // 1. 전혀 안 겹칠 경우
    if(qe < s | e < qs) return 0;

    // 2. 트리가 쿼리에 완전히 겹칠 경우
    if(s >= qs && e <= qe) return seg[n];

    // 3. 일부 겹칠 경우
    int m = s + (e - s) / 2;
    int l = seg_query(n * 2, s, m, qs, qe), r = seg_query(n * 2 + 1, m + 1, e, qs, qe);
    return l + r;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        cin >> arr[i];
        vec.emplace_back(arr[i], i);
    }
    for(int i = 0; i < N * 4; ++i) seg[i] = 0;
    sort(vec.begin(), vec.end());

    ll cnt = 0;
    for(auto & v : vec){
        cnt += seg_query(1, 0, N - 1, v.ss + 1, N - 1);
        seg_update(1, 0, N - 1, v.ss);
    }
    cout << cnt;
    return 0;
}