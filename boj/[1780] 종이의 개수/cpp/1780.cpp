#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define INF 987654321
#define endl '\n'
using namespace std;
int cnt[3];

void cut_paper(const vector<vector<int>> & grid, int x, int y, int len){
    int color = grid[x][y];
    bool is_same = true;

    // 격자 색 모두 같은지 check
    for (int i = x - len + 1; i <= x; ++i) {
        for (int j = y - len + 1; j <= y; ++j) {
            if(grid[i][j] != color){
                is_same = false;
                break;
            }
        }
        if(!is_same) break;
    }

    if(is_same){
        if(color == -1) cnt[0]++;
        else if(color == 0) cnt[1]++;
        else cnt[2]++;
    }

    else{
        int new_len = len / 3;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cut_paper(grid, x - new_len * i, y - new_len * j, new_len);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<vector<int>> grid(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }

    cut_paper(grid, N - 1, N - 1, N);

    for(int i : cnt) cout << i << endl;
    return 0;
}