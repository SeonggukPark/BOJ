#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
constexpr size_t MAX_N = 6;

struct Pos{
    int x, y;
};

int N;
bool possible;
int grid[MAX_N][MAX_N];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
string rst;
vector<Pos> v, teacher;

/*
    1. 좌상단: (1, 1)
    2. 빈 공간: 0, 학생: 1, 교사: 2, 장애물: 3
 */

void init(){
    memset(grid, 0, sizeof(grid));
    v.clear();
    teacher.clear();
    possible = false;
}

void input(){
    char c;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> c;
            switch(c){
                case 'X':
                    grid[i][j] = 0;
                    v.push_back({i, j});
                    break;

                case 'S':
                    grid[i][j] = 1;
                    break;

                case 'T':
                    grid[i][j] = 2;
                    teacher.push_back({i, j});
                    break;
            }
        }
    }
}

void traverse(){

}

bool is_valid(int x, int y){
    if(x < 0 || y < 0 || x >= N || y >= N) return false;
    if(grid[x][y] == 3) return false;
    return true;
}

// cp_grid traverse
void is_possible(){
    for(auto t : teacher) {
        int x = t.x, y = t.y;

        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];

            while(is_valid(nx, ny)){
                if(grid[nx][ny] == 1){ // 학생 발견한 경우
                    possible = false;
                    return;
                }

                nx += dx[i], ny += dy[i];
            }
        }
    }

    possible = true;
}


void run(){
    int len = (int)v.size();

    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            for (int k = j + 1; k < len; ++k) {
                auto p1 = v[i], p2 = v[j], p3 = v[k];

                grid[p1.x][p1.y] = grid[p2.x][p2.y] = grid[p3.x][p3.y] = 3;

                is_possible();
                if(possible) return;

                grid[p1.x][p1.y] = grid[p2.x][p2.y] = grid[p3.x][p3.y] = 0;
            }
        }
    }
}

int main() {
    init();
    input();
    run();

    rst = (possible) ? "YES" : "NO";
    cout << rst;
    return 0;
}