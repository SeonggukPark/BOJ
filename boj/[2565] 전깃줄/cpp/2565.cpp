#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define endl '\n'
#define x first
#define y second
using namespace std;
void solve(){
    int N; cin >> N;
    vector<pii> v(N);
    vector<int> dp(N);
    for (int i = 0; i < N; ++i) {
        cin >> v[i].x >> v[i].y;
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < N; ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if(v[j].y < v[i].y) dp[i] = max(dp[i], dp[j] + 1);
        }
    }

    cout << N - *max_element(dp.begin(), dp.end());
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}