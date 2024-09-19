#include <bits/stdc++.h>
#include <deque>
#include <queue>
#include <cstring>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

void solve(){
    int input, rst, acc = 0;
    for (int i = 0; i < 4; ++i) {
        cin >> input;
        acc += input;
    }

    cin >> input;
    rst = (4 * input - acc > 0) ? 4 * input - acc : 0;
    cout << rst;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}