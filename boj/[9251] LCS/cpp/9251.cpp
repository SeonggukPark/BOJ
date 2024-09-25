#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define endl '\n'
#define x first
#define y second
using namespace std;
constexpr size_t MAX_LEN = 1001;
int dp[MAX_LEN][MAX_LEN];
void solve(){
   string str1, str2;
   cin >> str1 >> str2;
   int len1 = (int)str1.size(), len2 = (int)str2.size();
   memset(dp, 0, sizeof(dp));

    for (int i = 0; i < len1; ++i) {
        for (int j = 0; j < len2; ++j) {
            if(str2[j] == str1[i]) dp[i + 1][j + 1] = dp[i][j] + 1;
            else dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
        }
    }

    cout << dp[len1][len2];
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}