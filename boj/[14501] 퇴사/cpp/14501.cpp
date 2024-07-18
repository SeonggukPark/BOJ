#include <bits/stdc++.h>
using namespace std;
int n;
constexpr size_t MAX_N = 15;
int arr[MAX_N + 2], dp[MAX_N + 2][MAX_N + 2];

struct node{
    int s, e, c;
};
vector<node> v(MAX_N + 1);

int max_finder(int col, int cnt){
    int rst = 0;
    for (int i = 1; i < cnt; ++i) {
        rst = max(rst, dp[i][col]);
    }
    return rst;
}

void run(){
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> v[i].e >> v[i].c;
        v[i].s = i, v[i].e += i;
    }

    for (int i = 1; i <= n; ++i) {
        auto tar = v[i];
        if(tar.e > n + 1) continue;

        for(int j = 1; j < tar.e; ++j){
            dp[i][j] = 0;
        }

        dp[i][tar.e] = max_finder(tar.s, i) + v[i].c;

        for(int j = tar.e + 1; j <= n + 1; ++j){
            dp[i][j] = dp[i][j - 1];
        }
    }
/*
    for (int i = 1; i <= n; ++i) {
        cout << dp[i][n + 1] << ' ';
    }
    cout << endl;
*/
    cout << max_finder(n + 1, (int)v.size() + 1);
}

int main(int argc, char** argv){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    run();

    return 0;
}