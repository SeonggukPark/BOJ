#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define pii pair<int, int>
using namespace std;
constexpr size_t MAX_N = 1e5 + 1;
constexpr int INF = 0x7fffffff;
int n, m, arr[MAX_N];

void solve(){
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    sort(arr, arr + n);

    int r = 0, mini = INF;

    for(int l = 0; l < n; ++l){
        while(r < n && arr[r] - arr[l] < m) r++;
        if(r == n) break;
        mini = min(mini, arr[r] - arr[l]);
    }
    cout << mini;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}