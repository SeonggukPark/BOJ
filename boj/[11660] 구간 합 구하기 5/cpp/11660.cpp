#include <string>
#include <vector>
#include <iostream>
#define INF 987654321
#define ll long long
#define endl '\n'
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<vector<int> > arr(N + 1, vector<int>(N + 1, 0)), acc(N + 1, vector<int>(N + 1, 0));
    vector<vector<int> > row_acc(N + 1, vector<int>(N + 1, 0)), col_acc(N + 1, vector<int>(N + 1, 0));

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> arr[i][j];
            acc[i][j] = arr[i][j];
            if (i > 1) acc[i][j] += acc[i - 1][j];
            if (j > 1) acc[i][j] += acc[i][j - 1];
            if (i > 1 && j > 1) acc[i][j] -= acc[i - 1][j - 1];
        }
    }

    int x1, x2, y1, y2;
    while(M--){
        cin >> x1 >> y1 >> x2 >> y2;
        int rst = acc[x2][y2];
        if(x1 > 1) rst -= acc[x1 - 1][y2];
        if(y1 > 1) rst -= acc[x2][y1 - 1];
        if(x1 > 1 && y1 > 1) rst += acc[x1 - 1][y1 - 1];
        cout << rst << endl;
    }

    return 0;
}