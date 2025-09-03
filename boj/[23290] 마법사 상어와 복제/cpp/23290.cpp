#include <iostream>
#include <cstring>
using namespace std;

struct Pos { int r, c; };

const int N = 4;

// 물고기 8방(문제 정의): ←, ↖, ↑, ↗, →, ↘, ↓, ↙
int fr[8] = { 0,-1,-1,-1, 0, 1, 1, 1 };
int fc[8] = {-1,-1, 0, 1, 1, 1, 0,-1 };

// 상어 4방(사전순): U, L, D, R
int sr[4] = {-1, 0, 1, 0};
int sc[4] = { 0,-1, 0, 1};

int M, S;
int fish[N][N][8];      // 물고기 수
int smell[N][N];        // 냄새 남은 턴(카운트 방식)

// 경계 확인
inline bool in(int r, int c) {
    return (0 <= r && r < N && 0 <= c && c < N);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> M >> S;

    memset(fish, 0, sizeof(fish));
    memset(smell, 0, sizeof(smell));

    // 물고기 정보 (M줄) → 1-based 입력을 0-based로 변환
    for (int i = 0; i < M; ++i) {
        int r, c, d;
        cin >> r >> c >> d;
        --r; --c; --d;                  // d: 1..8 → 0..7
        fish[r][c][d]++;                // 동일 칸/방향에 여러 마리 누적 가능
    }

    // 상어 위치 (마지막 줄)
    Pos shark;
    cin >> shark.r >> shark.c;
    --shark.r; --shark.c;

    // S번 턴 진행
    for (int turn = 1; turn <= S; ++turn) {
        // 1) 복제 마법 (복제본 저장)
        int copyFish[N][N][8];
        memcpy(copyFish, fish, sizeof(fish));

        // 2) 물고기 이동
        int nextFish[N][N][8];
        memset(nextFish, 0, sizeof(nextFish));
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                for (int d = 0; d < 8; ++d) {
                    int cnt = fish[r][c][d];
                    if (cnt == 0) continue;

                    bool moved = false;
                    // 반시계로 최대 8번 회전
                    for (int rot = 0; rot < 8; ++rot) {
                        int nd = (d - rot + 8) % 8;
                        int nr = r + fr[nd];
                        int nc = c + fc[nd];
                        if (!in(nr, nc)) continue;
                        if (smell[nr][nc] > 0) continue;         // 냄새 있는 칸 X
                        if (nr == shark.r && nc == shark.c) continue; // 상어 칸 X
                        nextFish[nr][nc][nd] += cnt;
                        moved = true;
                        break;
                    }
                    if (!moved) {
                        // 제자리
                        nextFish[r][c][d] += cnt;
                    }
                }
            }
        }
        memcpy(fish, nextFish, sizeof(nextFish));

        // 3) 상어 이동 (3칸, U/L/D/R 사전순, 먹은 물고기 합 최대)
        int bestEat = -1;
        int bestPath[3] = {0,0,0};
        Pos bestStep[3];

        // 현재 칸별 물고기 총합(방향 합)
        int sumCell[N][N];
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                int s = 0;
                for (int d = 0; d < 8; ++d) s += fish[r][c][d];
                sumCell[r][c] = s;
            }
        }

        for (int d1 = 0; d1 < 4; ++d1) {
            int r1 = shark.r + sr[d1], c1 = shark.c + sc[d1];
            if (!in(r1, c1)) continue;

            for (int d2 = 0; d2 < 4; ++d2) {
                int r2 = r1 + sr[d2], c2 = c1 + sc[d2];
                if (!in(r2, c2)) continue;

                for (int d3 = 0; d3 < 4; ++d3) {
                    int r3 = r2 + sr[d3], c3 = c2 + sc[d3];
                    if (!in(r3, c3)) continue;

                    // 3칸 방문 중복 방지(한 칸은 한 번만 집계)
                    bool used[N][N] = {};
                    int eat = 0;
                    if (!used[r1][c1]) { eat += sumCell[r1][c1]; used[r1][c1] = true; }
                    if (!used[r2][c2]) { eat += sumCell[r2][c2]; used[r2][c2] = true; }
                    if (!used[r3][c3]) { eat += sumCell[r3][c3]; used[r3][c3] = true; }

                    if (eat > bestEat) {
                        bestEat = eat;
                        bestPath[0] = d1; bestPath[1] = d2; bestPath[2] = d3;
                        bestStep[0] = {r1,c1};
                        bestStep[1] = {r2,c2};
                        bestStep[2] = {r3,c3};
                    }
                    // 동률이면 기존(사전순 먼저 탐색된 경로) 유지
                }
            }
        }

        // 상어 이동 및 먹기/냄새 남기기
        for (int k = 0; k < 3; ++k) {
            int r = bestStep[k].r, c = bestStep[k].c;
            if (sumCell[r][c] > 0) {
                // 해당 칸 물고기 제거
                for (int d = 0; d < 8; ++d) fish[r][c][d] = 0;
                // 냄새 2턴 유지: 이번 턴 끝에 smell-- 할 것이므로 3으로 세팅
                smell[r][c] = 3;
            }
        }
        // 상어 위치 갱신(3번째 칸)
        shark = bestStep[2];

        // 4) 냄새 감소
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (smell[r][c] > 0) --smell[r][c];
            }
        }

        // 5) 복제 마법 완료(초기 복제본을 더해줌)
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                for (int d = 0; d < 8; ++d) {
                    fish[r][c][d] += copyFish[r][c][d];
                }
            }
        }
    }

    // 남은 물고기 수 출력
    int answer = 0;
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            for (int d = 0; d < 8; ++d)
                answer += fish[r][c][d];

    cout << answer << '\n';
    return 0;
}
