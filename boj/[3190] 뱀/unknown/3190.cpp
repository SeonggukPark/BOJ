#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
constexpr size_t MAX_N = 102;
int n, k, l;
int grid[MAX_N][MAX_N]; // 0: 빈 공간, 1: 벽 or 뱀, 2: 사과
int dir; // 0: E, 1: S, 2: W, 3: N
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int cur_t;
int head_x, head_y;

queue<pair<int, char> > rotate; // time, direction
queue<pair<int, int> > snake;

void init(){
    memset(grid, 0, sizeof(grid));
    rotate = {};
    snake = {};
    grid[1][1] = 1;
    snake.emplace(1, 1);
    cur_t = 0;
    head_x = head_y = 1;
}

void input(){
    int r, c, tmp1;
    char tmp2;
    cin >> n >> k;

    while(k--){
        cin >> r >> c;
        grid[r][c] = 2;
    }

    cin >> l;
    while(l--){
        cin >> tmp1 >> tmp2;
        rotate.emplace(tmp1, tmp2);
    }

    for (int i = 0; i <= n + 1; ++i) {
        grid[0][i] = grid[i][0] = 1;
        grid[n + 1][i] = grid[i][n + 1] = 1;
    }
}

void run(){
    int nx, ny;
    auto rot = rotate.front();
    rotate.pop();

    while(true){
        cur_t++;
        nx = head_x + dx[dir], ny = head_y + dy[dir];

        if(grid[nx][ny] == 1) return;

        if(grid[nx][ny] == 0){
            auto tail = snake.front();
            snake.pop();
            grid[tail.first][tail.second] = 0;
        }

        grid[nx][ny] = 1;
        snake.emplace(nx, ny);
        head_x = nx, head_y = ny;
        
        if(rot.first == cur_t && rot.first > 0){
            if(rot.second == 'D'){
                dir = (dir + 1) % 4;
            }

            else{
                dir = (dir + 3) % 4;
            }

            if(rotate.empty()) rot = {-1, -1};

            else{
                rot = rotate.front();
                rotate.pop();
            }
        }
    }
}

int main() {
    init();
    input();
    run();
    cout << cur_t << endl;
    return 0;
}
