#include <vector>
#include <iostream>
#include <algorithm>
#define endl '\n'
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<int> seq(N);
    for (int i = 0; i < N; ++i) {
        cin >> seq[i];
    }

    sort(seq.begin(), seq.end());

    int i = 0, rst = 0;
    while(i < N){
        rst += seq.back() * (i + 1);
        seq.pop_back();
        i++;
    }

    cout << rst;
    return 0;
}