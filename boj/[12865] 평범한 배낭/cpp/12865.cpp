#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define endl '\n'
#define x first
#define y second
using namespace std;
constexpr size_t MAX_K = 1e5 + 1, MAX_N = 101;
int dp[MAX_N][MAX_K];
void solve(){
   int N, K;
   cin >> N >> K;
   memset(dp, 0, sizeof(dp));
   vector<pii> v(N + 1);
   v[0] = {0, 0};

   for (int i = 1; i <= N; ++i) {
        cin >> v[i].x >> v[i].y;

       for (int j = 0; j <= K; ++j) {
           if(v[i].x > j) dp[i][j] = dp[i - 1][j];
           else dp[i][j] = max(dp[i - 1][j - v[i].x] + v[i].y, dp[i - 1][j]);
       }
   }

   cout << dp[N][K] << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}