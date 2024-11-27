#include <vector>
#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K, cnt = 0; cin >> N >> K;
    vector<int> coins(N);
    for (int i = 0; i < N; ++i) {
        cin >> coins[i];
    }

    while(!coins.empty()){
        while(K >= coins.back()){
            K -= coins.back();
            cnt++;
        }
        coins.pop_back();
    }

    cout << cnt;
    return 0;
}