#include <bits/stdc++.h>
using namespace std;
constexpr size_t MAX_N = 500;
int dp[MAX_N + 1][MAX_N + 1], arr[MAX_N + 1][MAX_N + 1];

void run(){
    int n;
    cin >> n;

    // input
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            cin >> arr[i][j];
        }
    }

    dp[1][1] = arr[1][1];

    // dp traverse
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            if(j == 1) dp[i][j] = dp[i - 1][j] + arr[i][j];
            else if(j == i) dp[i][j] = dp[i - 1][j - 1] + arr[i][j];
            else dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + arr[i][j];
        }
    }

    int rst = 0;
    for(int i = 1; i <= n; i++){
        rst = max(rst, dp[n][i]);
    }

    cout << rst;
}

int main(int argc, char** argv){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    run();
    return 0;
}