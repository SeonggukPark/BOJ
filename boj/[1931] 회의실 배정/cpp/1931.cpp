#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;
int N;

bool cmp(pll a, pll b){
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

int main(){
    cin >> N;
    vector<pll> meets(N);

    for (int i = 0; i < N; ++i) {
        cin >> meets[i].x >> meets[i].y;
    }

    sort(meets.begin(), meets.end(), cmp);

    int cnt = 0, cur_time = 0;
    for(int i = 0; i < N; ++i){
        if(cur_time > meets[i].x) continue;
        cnt++, cur_time = meets[i].y;
    }

    cout << cnt;
    return 0;
}