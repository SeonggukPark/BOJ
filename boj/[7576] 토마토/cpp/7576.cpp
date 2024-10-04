#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
#define x first
#define y second
#define pii pair<int, int>
#define endl '\n'
#define ll long long
constexpr size_t MAX_N = 1000;
string input[MAX_N];
int grid[MAX_N][MAX_N];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int N, M;
vector<pii> tomato;

inline bool is_valid(int cx, int cy){
    if(cx < 0 || cy < 0 || cx >= N || cy >= M) return false;
    if(grid[cx][cy] == -1 || grid[cx][cy] > 0) return false;
    return true;
}

int solve(){
    cin >> M >> N;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> grid[i][j];
            if(grid[i][j] == 1) tomato.push_back({i, j});
        }
    }

    queue<pii> q;
    for(pii pos : tomato){
        q.push({pos.x, pos.y});
    }

    while(!q.empty()){
        pii top = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = top.x + dx[i], ny = top.y + dy[i];
            if(!is_valid(nx, ny)) continue;
            grid[nx][ny] = grid[top.x][top.y] + 1;
            q.push({nx, ny});
        }
    }

    int max_day = -1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if(grid[i][j] == 0) return -1;
            max_day = max(max_day, grid[i][j]);
        }
    }

    return max_day - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << solve();
    return 0;
}