#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#define INF 987654321
#define ll long long
#define x first
#define y second
#define pll pair<ll, ll>
#define endl '\n'
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<pll> towns(N);
    for (int i = 0; i < N - 1; ++i) {
        cin >> towns[i].y;
    }
    for (int i = 0; i < N; ++i) {
        cin >> towns[i].x;
    }

    for (int i = N - 3; i >= 0; --i) {
        towns[i].y += towns[i + 1].y;
    }

    sort(towns.begin(), towns.end());

    ll rst = 0, cur = 0;
    for(pll i : towns){
        if(i.y <= cur) continue;
        rst += i.x * (i.y - cur);
        cur = i.y;
    }

    cout << rst;
    return 0;
}