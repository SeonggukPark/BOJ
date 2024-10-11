#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define pii pair<int, int>
#define x first
#define y second
constexpr int MAP_SIZE = 25;
constexpr int INF = 1e9 + 1;
int n, k, rst, mini, s_dir, grid[MAP_SIZE][MAP_SIZE], inc_map[MAP_SIZE][MAP_SIZE];
bool visited[MAP_SIZE][MAP_SIZE];
vector<int> vec;
pii center = { 12, 12 };
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
queue<pii> q;

void init() {
    cin >> n >> k;
    vec.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }
    // 시작 방향 찾기
    int acc = 0, dir = 3;
    for (int inc = 1; inc < 20; ++inc) {
        for (int rpt = 0; rpt < 2; ++rpt) {
            if (acc + inc <= n) acc += inc, dir = (dir + 1) % 4;
        }
    }

    s_dir = dir;
}

bool is_valid(int nx, int ny) {
    if (nx < 0 || ny < 0 || nx >= MAP_SIZE || ny >= MAP_SIZE) return false;
    return true;
}

void op_1() {
    for (int& tar : vec) if (tar == mini) tar++;
}

void op_2() {
    for (int i = 0; i < MAP_SIZE; ++i) fill(grid[i], grid[i] + MAP_SIZE, 0);
    pii cur = center;
    int acc = 0, dir = (s_dir + 1) % 4, v_idx = 0;

    for (int inc = 1; inc < 20; ++inc) {
        for (int i = 0; i < 2; ++i) {
            if (acc + inc > n) {
                // 방향 전환 안하고 남은거 털기
                for (int rpt = 0; rpt < n - acc; ++rpt) {
                    grid[cur.x][cur.y] = vec[v_idx++];
                    cur.x += dx[dir], cur.y += dy[dir];
                }
                return;
            }

            acc += inc, dir = (dir + 3) % 4;
            for (int rpt = 0; rpt < inc; ++rpt) {
                grid[cur.x][cur.y] = vec[v_idx++];
                cur.x += dx[dir], cur.y += dy[dir];
            }
        }
    }
}

void op_3(bool is_rpt) {
    for (int i = 0; i < MAP_SIZE; ++i) {
        fill(visited[i], visited[i] + MAP_SIZE, false);
        fill(inc_map[i], inc_map[i] + MAP_SIZE, 0);
    }

    q = {};
    if (is_rpt) q.push({ 0, 0 });
    else q.push(center);
    visited[q.front().x][q.front().y] = true;

    while (!q.empty()) {
        pii top = q.front(); q.pop();
        for (int dir = 0; dir < 4; ++dir) {
            int nx = top.x + dx[dir], ny = top.y + dy[dir];
            if (!is_valid(nx, ny) || grid[nx][ny] == 0) continue;

            if (abs(grid[nx][ny] - grid[top.x][top.y]) >= 5) {
                inc_map[top.x][top.y] -= (grid[top.x][top.y] - grid[nx][ny]) / 5;
            }

            if (visited[nx][ny]) continue;
            visited[nx][ny] = true;
            q.push({ nx, ny });
        }
    }

    vec.clear();
    for (int c = 0; c < MAP_SIZE; ++c) {
        for (int r = MAP_SIZE -1; r >= 0; --r) {
            grid[r][c] += inc_map[r][c];
            if (grid[r][c] != 0) vec.push_back(grid[r][c]);
        }
    }
}

void op_4() {
    for (int i = 0; i < MAP_SIZE; ++i) fill(grid[i], grid[i] + MAP_SIZE, 0);
    int len = n / 4;
    for (int i = 0; i < len; ++i) {
        grid[0][i] = vec[3 * len - 1 - i];
        grid[1][i] = vec[len + i];
        grid[2][i] = vec[len - 1 - i];
        grid[3][i] = vec[3 * len + i];
    }
}


bool check_answer() { // vec min-max 차이 k 이하인지 check
    int maxi = 0;
    mini = INF;
    for (int tar : vec) mini = min(mini, tar), maxi = max(maxi, tar);
    if (maxi - mini <= k) return true;
    return false;
}


void solve() {
    rst = 0;
    while (!check_answer()) {
        rst++;
        op_1();
        op_2();
        op_3(false);
        op_4();
        op_3(true);
    }
    cout << rst;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}