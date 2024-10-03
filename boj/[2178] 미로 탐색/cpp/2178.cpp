#include <iostream>
#include <stack>
#include <string>
#include <queue>
using namespace std;

#define x first
#define y second
#define pii pair<int, int>
#define endl '\n'
#define ll long long
constexpr size_t MAX_N = 100;
string input[MAX_N];
int grid[MAX_N][MAX_N];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int N, M;

inline bool is_valid(int cx, int cy){
    if(cx < 0 || cy < 0 || cx >= N || cy >= M) return false;
    if(grid[cx][cy] == -1 || grid[cx][cy] > 0) return false;
    return true;
}

void solve(){
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        cin >> input[i];
        for (int j = 0; j < M; ++j) {
            switch (input[i][j]) {
                case '1':
                    grid[i][j] = 0;
                    break;

                case '0':
                    grid[i][j] = -1;
                    break;

                default:
                    break;
            }
        }
    }
    queue<pii> q;
    q.push({0, 0});
    grid[0][0] = 1;

    while(!q.empty()){
        pii top = q.front();
        q.pop();

        if(top.x == N - 1 && top.y == M - 1) break;

        for (int i = 0; i < 4; ++i) {
            int nx = top.x + dx[i], ny = top.y + dy[i];
            if(!is_valid(nx, ny)) continue;
            grid[nx][ny] = grid[top.x][top.y] + 1;
            q.push({nx, ny});
        }
    }
    cout << grid[N - 1][M - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}