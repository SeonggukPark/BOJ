#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
constexpr size_t MAX_SIZE = 8;
int N, M, rst;
int grid[MAX_SIZE][MAX_SIZE], cp_grid[MAX_SIZE][MAX_SIZE];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct Pos{
    int x, y;
};

vector<Pos> v, virus;

void init(){
    memset(grid, 0, sizeof(grid));
    rst = 0;
}

void traverse(){
    for(int i = 0; i < N; i++){
        for (int j = 0; j < M; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void input(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for (int j = 0; j < M; ++j) {
            cin >> grid[i][j];
            
            if(grid[i][j] == 0){ // 벽 위치 후보에 추가
                v.push_back({i, j});
            }

            else if(grid[i][j] == 2){
                virus.push_back({i, j});
            }
        }
    }
}

void spread_out(){
    int cnt = 0;
    for(int i = 0; i < N; i++){
        for (int j = 0; j < M; ++j) {
            cp_grid[i][j] = grid[i][j];
        }
    }

    for(auto i : virus) {
        queue<Pos> q;
        q.push({i.x, i.y});

        while(!q.empty()){
            auto tar = q.front();
            q.pop();

            for (int j = 0; j < 4; ++j) {
                int nx = tar.x + dx[j], ny = tar.y + dy[j];

                if(nx < 0 || ny < 0 || nx >= N || ny >= M) continue;

                if(cp_grid[nx][ny] == 0){
                    q.push({nx, ny});
                    cp_grid[nx][ny] = 2;
                }
            }
        }
    }

    // 안전 영역 count
    for(int i = 0; i < N; i++){
        for (int j = 0; j < M; ++j) {
            if(cp_grid[i][j] == 0) cnt++;
        }
    }
    
    // 안전 영역 최대로 되면 저장
    if (cnt > rst) {
        rst = cnt;
    }
}

void run(){
    int max_idx = (int)v.size();

    // 빈(0) 좌표 3개 골라서 brute-fore
    for(int i = 0; i < max_idx; i++){
        for(int j = i + 1; j < max_idx; j++){
            for(int k = j + 1; k < max_idx; k++){
                auto p_1 = v[i], p_2 = v[j], p_3 = v[k];
                grid[p_1.x][p_1.y] = 1;
                grid[p_2.x][p_2.y] = 1;
                grid[p_3.x][p_3.y] = 1;
                spread_out();
                grid[p_1.x][p_1.y] = 0;
                grid[p_2.x][p_2.y] = 0;
                grid[p_3.x][p_3.y] = 0;
            }
        }
    }
    cout << rst;
}

int main() {
    init();
    input();
    run();
    return 0;
}