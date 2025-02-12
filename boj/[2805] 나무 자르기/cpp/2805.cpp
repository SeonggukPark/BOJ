#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
using namespace std;
constexpr int MAX_M = 2e9 + 1;
ll N, M;
 
void solve(){
    cin >> N >> M;
    vector<ll> vec(N);
    for(int i = 0; i < N; ++i){
        cin >> vec[i];
    }

    ll lo = 0, hi = MAX_M;

    while(lo + 1 < hi){
        ll acc = 0, hei = lo + (hi - lo) / 2;
        
        for(int i = 0; i < N; ++i){
            if (vec[i] > hei) acc += vec[i] - hei;
        }

        if(acc < M) hi = hei;
        else lo = hei;
    }

    cout << lo;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}