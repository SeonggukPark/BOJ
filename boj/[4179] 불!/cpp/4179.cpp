#include <iostream>
#include <string>
#include <queue>
using namespace std;

#define pii pair<int, int>
constexpr size_t MAX_N = 1000;

// 그리드: -1은 벽, 0은 빈 공간
int grid[MAX_N][MAX_N];
// fire_time: 불의 도착 시간을 저장, -1은 아직 도달하지 않음
int fire_time[MAX_N][MAX_N];
// person_time: 지훈이의 이동 시간을 저장, -1은 아직 방문하지 않음
int person_time[MAX_N][MAX_N];

int N, M;
char input;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

// 불의 이동 가능 여부를 판단하는 함수
inline bool fire_valid(int cx, int cy){
    if(cx < 0 || cy < 0 || cx >= N || cy >= M) return false;
    if(fire_time[cx][cy] != -1 || grid[cx][cy] == -1) return false;
    return true;
}

// 지훈이의 이동 가능 여부를 판단하는 함수
inline bool per_valid(int cx, int cy, int time){
    // 범위를 벗어난 경우는 탈출 성공
    if(cx < 0 || cy < 0 || cx >= N || cy >= M) return true;
    if(grid[cx][cy] == -1 || person_time[cx][cy] != -1) return false;
    if(fire_time[cx][cy] != -1 && time >= fire_time[cx][cy]) return false;
    return true;
}

void solve(){
    cin >> N >> M;
    queue<pii> q_fire, q_per;

    // 초기화
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> input;
            if(input == '#') {
                grid[i][j] = -1;
                fire_time[i][j] = -1;
                person_time[i][j] = -1;
            }
            else {
                grid[i][j] = 0;
                fire_time[i][j] = -1;
                person_time[i][j] = -1;
                if(input == 'F') {
                    q_fire.push({i, j});
                    fire_time[i][j] = 0;
                }
                else if(input == 'J') {
                    q_per.push({i, j});
                    person_time[i][j] = 0;
                }
            }
        }
    }

    // 1. 불의 전파 (BFS)
    while(!q_fire.empty()){
        pii current = q_fire.front(); q_fire.pop();
        for(int dir=0; dir<4; dir++){
            int nx = current.first + dx[dir], ny = current.second + dy[dir];
            if(fire_valid(nx, ny)){
                fire_time[nx][ny] = fire_time[current.first][current.second] + 1;
                q_fire.push({nx, ny});
            }
        }
    }

    // 2. 지훈이의 탈출 (BFS)
    while(!q_per.empty()){
        pii current = q_per.front(); q_per.pop();
        for(int dir=0; dir<4; dir++){
            int nx = current.first + dx[dir], ny = current.second + dy[dir];
            int next_time = person_time[current.first][current.second] + 1;

            // 탈출 성공 (경계에 도달)
            if(nx < 0 || ny < 0 || nx >= N || ny >= M){
                cout << next_time;
                return;
            }

            // 이동 가능 여부 검사
            if(per_valid(nx, ny, next_time)){
                person_time[nx][ny] = next_time;
                q_per.push({nx, ny});
            }
        }
    }

    // 탈출 실패
    cout << "IMPOSSIBLE";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
   // freopen("input.txt", "r", stdin);
    solve();
    return 0;
}
