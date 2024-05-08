#include <iostream>
#include <unordered_set>
#include <queue>
#include <cstring>
using namespace std;
constexpr size_t MAX_SIZE = 200;
int N, K, S, X, Y, rst;
int grid[MAX_SIZE][MAX_SIZE], cp_grid[MAX_SIZE][MAX_SIZE];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct Pos{
    int x, y;
};

void traverse(){
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}


void init(){
    memset(grid, 0, sizeof(grid));
    rst = 0;
}

void input(){
    cin >> N >> K;
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }

    cin >> S >> X >> Y;
}

void run(){
    while(S--){
        for(int i = 0; i < N; i++){
            for (int j = 0; j < N; ++j) {
                cp_grid[i][j] = grid[i][j];
            }
        }

        for(int i = 0; i < N; i++){
            for (int j = 0; j < N; ++j) {
                if(grid[i][j] != 0) continue;

                int mini = K + 1;

                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
                    if (grid[nx][ny] == 0) continue;
                    if (mini > grid[nx][ny]) mini = grid[nx][ny];
                }

                if (mini < K + 1) {
                    cp_grid[i][j] = mini;
                }
            }
        }


        for(int i = 0; i < N; i++){
            for (int j = 0; j < N; ++j) {
                grid[i][j] = cp_grid[i][j];
            }
        }
        // traverse();
    }

    cout << grid[X - 1][Y - 1];
}

int main() {
    init();
    input();
    run();
    return 0;
}