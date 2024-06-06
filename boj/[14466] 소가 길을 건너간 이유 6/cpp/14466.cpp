#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
constexpr size_t MAX_N = 101;
int grid[MAX_N][MAX_N];
int wall[MAX_N][MAX_N][4];
bool visited[MAX_N][MAX_N];
int dx[] = {0, 0, 1, -1}; // 동, 서, 남, 북 순
int dy[] = {1, -1, 0, 0};
int N, K, R;

struct Pos{
    int x, y;
};

queue<Pos> idx_q;

void init(){
    memset(grid, 0, sizeof(grid));
    memset(wall, 0, sizeof(wall));
    memset(visited, false, sizeof(visited));
    idx_q = {};
}

bool valid_pos(int x, int y){
    if(x <= 0 || y <= 0 || x > N || y > N) return false;
    return true;
}

int main() {
    init();

    int r, c, r_t, c_t, r_diff, c_diff;
    int rst = 0;
    cin >> N >> K >> R;

    for (int i = 1; i <= R; ++i) {
        cin >> r >> c >> r_t >> c_t;
        r_diff = r - r_t, c_diff = c - c_t;

        if(c_diff < 0) wall[r][c][0] = wall[r_t][c_t][1] = 1;
        else if(c_diff > 0) wall[r][c][1] = wall[r_t][c_t][0] = 1;
        else if(r_diff < 0) wall[r][c][2] = wall[r_t][c_t][3] = 1;
        else if(r_diff > 0) wall[r][c][3] = wall[r_t][c_t][2] = 1;
    }

    for (int i = 1; i <= K; ++i) {
        cin >> r >> c;
        grid[r][c] = i;
        idx_q.push({r, c});
    }

    for(int i = 1; i < K; i++){
        auto p = idx_q.front();
        idx_q.pop();

        int cnt = K - i;
        memset(visited, false, sizeof(visited));
        int x = p.x, y = p.y;
        if(grid[x][y] == K) continue;

        queue<Pos> q;
        q.push({x, y});
        visited[x][y] = true;

        while(!q.empty()){
            auto top = q.front();
            q.pop();
            if(grid[top.x][top.y] > grid[x][y]) cnt--;

            for (int k = 0; k < 4; ++k) {
                int nx = top.x + dx[k], ny = top.y + dy[k];
                if(!valid_pos(nx, ny)) continue;
                if(wall[top.x][top.y][k]) continue;
                if(visited[nx][ny]) continue;

                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }

        rst += cnt;
    }

    cout << rst;
    return 0;
}
