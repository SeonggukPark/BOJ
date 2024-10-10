#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define pii pair<int, int>
using namespace std;
constexpr size_t MAX_N = 1e6;
constexpr int INF = 1e9 + 1;
ll k, n;

void solve(){
    cin >> k >> n; // assert k <= n
    vector<ll> vec(k);
    for (int i = 0; i < k; ++i) {
        cin >> vec[i];
    }

    ll cnt, l = 0, r = *max_element(vec.begin(), vec.end()) + 1;

    while(l + 1 < r){
        ll mid = l + (r - l) / 2;
        // cnt 구하기
        cnt = 0;
        for(ll data : vec){
            cnt += data / mid;
        }

        if(cnt >= n) l = mid;
        else r = mid;
    }

    cout << l;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}