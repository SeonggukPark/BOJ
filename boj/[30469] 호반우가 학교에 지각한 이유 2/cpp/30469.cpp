#include <bits/stdc++.h>
#define pii pair<int, int>
#define endl '\n'
#define x first
#define y second
using namespace std;

void solve(){
    int A, B, N;
    cin >> A >> B >> N;

    if((B / 10) % 2 == 0 || (B / 10) == 5){
        cout << -1;
        return;
    }
    
    cout << A;
    int front = A % 10;
    N -= 4;

    if(front == 9) {
        cout << 7;
        N--;
    }

    while(N--){
        cout << 1;
    }

    cout << B;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}