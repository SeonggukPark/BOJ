#include <string>
#include <vector>
#include <iostream>
#define INF 987654321
#define ll long long
#define endl '\n'
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, K; cin >> N >> M >> K;
    vector<vector<int> > acc_b(N + 1, vector<int>(M + 1, 0)), acc_w(N + 1, vector<int>(M + 1, 0));

    char cur;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> cur;
            acc_b[i][j] = acc_b[i - 1][j] + acc_b[i][j - 1] - acc_b[i - 1][j - 1];
            if(((i + j) % 2 == 0 && cur != 'B') || ((i + j) % 2 != 0 && cur == 'B')) acc_b[i][j]++;
            acc_w[i][j] = i * j - acc_b[i][j];
        }
    }

    int rst = INF;
    for (int i = K; i <= N; ++i) {
        for (int j = K; j <= M; ++j) {
            rst = min(rst, acc_b[i][j] + acc_b[i - K][j - K] - acc_b[i][j - K] - acc_b[i - K][j]);
            rst = min(rst, acc_w[i][j] + acc_w[i - K][j - K] - acc_w[i][j - K] - acc_w[i - K][j]);
        }
    }

    cout << rst;
    return 0;
}