#include <iostream>
#include <deque>
#include <queue>
#include <algorithm>
using namespace std;

#define x first
#define y second
using pii = pair<int,int>;

constexpr size_t MAX_N = 21;

int n, m, k;
int rst, cur_dir, dice_bot;
int grid[MAX_N][MAX_N], score[MAX_N][MAX_N];
int dx[4] = {0, 1, 0, -1}; // E S W N
int dy[4] = {1, 0, -1, 0};

deque<int> row_deq, col_deq; // row: [bottom, east, top, west], col: [bottom, south, top, north]
bool visited[MAX_N][MAX_N];
queue<pii> q;
pii dice;

bool is_valid(int nx, int ny){
    if (nx <= 0 || ny <= 0 || nx > n || ny > m) return false; // 열 상한은 m
    return true;
}

void init() {
    // ★ 문제 조건과 일치하는 초기 주사위 상태
    row_deq = {6, 3, 1, 4};
    col_deq = {6, 5, 1, 2};

    dice = {1, 1};
    cur_dir = 0;  // East
    rst = 0;
    dice_bot = 6;

    cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> grid[i][j];

    // 점수 전처리 (컴포넌트 크기 * 값). 비효율이지만 N,M<=20이라 충분.
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int r = 1; r <= n; ++r)
                fill(visited[r], visited[r] + m + 1, false);

            visited[i][j] = true;
            q = {};
            q.push({i, j});
            int cnt = 1, val = grid[i][j];

            while (!q.empty()) {
                auto cur = q.front(); q.pop();
                for (int d = 0; d < 4; ++d) {
                    int nx = cur.x + dx[d], ny = cur.y + dy[d];
                    if (!is_valid(nx, ny) || visited[nx][ny] || grid[nx][ny] != val) continue;
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                    ++cnt;
                }
            }

            int sc = val * cnt;
            for (int r = 1; r <= n; ++r)
                for (int c = 1; c <= m; ++c)
                    if (visited[r][c]) score[r][c] = sc;
        }
    }
}

void move_dice(){
    int nx = dice.x + dx[cur_dir], ny = dice.y + dy[cur_dir];
    if (!is_valid(nx, ny)) {
        cur_dir = (cur_dir + 2) % 4; // 반대
        nx = dice.x + dx[cur_dir];
        ny = dice.y + dy[cur_dir];
    }
    dice = {nx, ny};

    // ★ 방향별 올바른 회전 (E/W는 row, N/S는 col)
    switch (cur_dir) {
        case 0: { // East: row left-rotate
            row_deq.push_back(row_deq.front());
            row_deq.pop_front();
            col_deq[0] = row_deq[0];
            col_deq[2] = row_deq[2];
            break;
        }
        case 2: { // West: row right-rotate
            row_deq.push_front(row_deq.back());
            row_deq.pop_back();
            col_deq[0] = row_deq[0];
            col_deq[2] = row_deq[2];
            break;
        }
        case 1: { // South: col left-rotate
            col_deq.push_back(col_deq.front());
            col_deq.pop_front();
            row_deq[0] = col_deq[0];
            row_deq[2] = col_deq[2];
            break;
        }
        case 3: { // North: col right-rotate
            col_deq.push_front(col_deq.back());
            col_deq.pop_back();
            row_deq[0] = col_deq[0];
            row_deq[2] = col_deq[2];
            break;
        }
    }

    dice_bot = row_deq[0];
    rst += score[dice.x][dice.y];
}

void change_dir(){
    int A = dice_bot;                 // 주사위 바닥
    int B = grid[dice.x][dice.y];     // 칸의 값
    if (A > B) cur_dir = (cur_dir + 1) % 4;      // 시계
    else if (A < B) cur_dir = (cur_dir + 3) % 4; // 반시계
}

void solve(){
    while (k--) {
        move_dice();
        change_dir();
    }
    cout << rst << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}
