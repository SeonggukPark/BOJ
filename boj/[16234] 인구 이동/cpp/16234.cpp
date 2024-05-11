#include <iostream>
#include <unordered_set>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
constexpr size_t MAX_SIZE = 50;
int N, L, R, grid[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

struct Pos{
    int x, y;
};

void traverse(){
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void init(){
}

bool is_valid(int x, int y){
    if (x < 0 || y < 0 || x >= N || y >= N) return false;
    return true;
}

void input(){
    cin >> N >> L >> R;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }
}

void run(){
    bool flag = true;
    int days = -1;

    while(flag) {
        days++;
        flag = false;
        memset(visited, false, sizeof(visited));

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (visited[i][j]) continue;
                vector<Pos> v;
                queue<Pos> q;
                int acc = 0, cnt = 0;
                q.push({i, j});
                visited[i][j] = true;

                while (!q.empty()) {
                    auto top = q.front();
                    acc += grid[top.x][top.y], cnt++;
                    v.push_back({top.x, top.y});
                    q.pop();

                    for (int k = 0; k < 4; ++k) {
                        int nx = top.x + dx[k], ny = top.y + dy[k];
                        if (!is_valid(nx, ny) || visited[nx][ny]) continue;
                        int diff = abs(grid[nx][ny] - grid[top.x][top.y]);

                        if(diff < L || diff > R) continue;

                        visited[nx][ny] = true;
                        flag = true;
                        q.push({nx, ny});
                    }
                }

                if (cnt == 0) continue;
                int rpl = acc / cnt;

                for (auto p: v) {
                    grid[p.x][p.y] = rpl;
                }
            }
        }
    }

    cout << days;
}

int main() {
    init();
    input();
    run();
    return 0;
}