#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define INF 987654321
#define endl '\n'
using namespace std;
constexpr size_t MAX_N = 128;
int grid[MAX_N][MAX_N], cnt_white, cnt_blue;

void cut_paper(int x, int y, int len){
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
        cout << color;
    }

    else{
        cout << '(';
        cut_paper(x - len / 2, y - len / 2, len / 2);
        cut_paper(x - len / 2, y, len / 2);
        cut_paper(x, y - len / 2, len / 2);
        cut_paper(x, y, len / 2);
        cout << ')';
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    string str;
    for (int i = 0; i < N; ++i) {
        cin >> str;
        for (int j = 0; j < N; ++j) {
            grid[i][j] = str[j] - '0';
        }
    }

    cut_paper(N - 1, N - 1, N);
    return 0;
}