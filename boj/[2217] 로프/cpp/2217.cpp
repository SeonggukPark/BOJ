#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;
int N;

int main(){
    cin >> N;
    vector<ll> ropes(N);

    for (int i = 0; i < N; ++i) {
        cin >> ropes[i];
    }

    sort(ropes.begin(), ropes.end(), greater<>());

    ll rst = 0;
    for(int i = 0; i < N; ++i){
        rst = max(rst, ropes[i] * (i + 1));
    }

    cout << rst;
    return 0;
}
