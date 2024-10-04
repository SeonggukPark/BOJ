#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define pii pair<int, int>
#define endl '\n'
#define ll long long
constexpr size_t MAX_N = 1002;
string grid[MAX_N];
int N, M, per[MAX_N][MAX_N], fire[MAX_N][MAX_N];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
pii pos_fire, pos_per;

inline bool fire_valid(int cx, int cy){
    if(cx < 0 || cy < 0 || cx >= N || cy >= M) return false;
    if(fire[cx][cy] >= 0 || grid[cx][cy] == '#') return false;
    return true;
}

inline bool per_valid(int cx, int cy, int time){
    if(grid[cx][cy] == '#' || per[cx][cy] >= 0) return false;
    if(fire[cx][cy] != -1 && time >= fire[cx][cy]) return false;
    return true;
}

void solve(){
    cin >> N >> M;
    queue<pii> q_per;
    queue<pii> q_fire;

    for (int i = 0; i < N; ++i) {
        fill(per[i], per[i] + M, -1);
        fill(fire[i], fire[i] + M, -1);
    }

    for (int i = 0; i < N; ++i) cin >> grid[i];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if(grid[i][j] == 'F') {
                q_fire.push({i, j});
                fire[i][j] = 0;
            }

            if(grid[i][j] == 'J'){
                q_per.push({i, j});
                pos_per = {i, j};
                per[i][j] = 0;
            }
        }
    }

    // 1. fire spread
    while(!q_fire.empty()){
        pii top = q_fire.front();
        q_fire.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = top.x + dx[i], ny = top.y + dy[i];
            if(!fire_valid(nx, ny)) continue;
            fire[nx][ny] = fire[top.x][top.y] + 1;
            q_fire.push({nx, ny});
        }
    }

    // 2. person escape
    while(!q_per.empty()){
        pii top = q_per.front(); q_per.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = top.x + dx[i], ny = top.y + dy[i];
            if(nx < 0 || ny < 0 || nx >= N || ny >= M){
                cout << per[top.x][top.y] + 1;
                return;
            }

            if(!per_valid(nx, ny, per[top.x][top.y] + 1)) continue;
            per[nx][ny] = per[top.x][top.y] + 1;
            q_per.push({nx, ny});
        }
    }

    cout << "IMPOSSIBLE";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}