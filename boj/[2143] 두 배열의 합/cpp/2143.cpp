#include <bits/stdc++.h>
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define ll long long
using namespace std;
constexpr size_t MAX_N = 1000;
vector<int> va, vb;
int a[MAX_N + 1], b[MAX_N + 1];
int T, n, m;
ll cnt;

void init(){
    va.clear();
    vb.clear();
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    cnt = 0;
}

void input(){
    cin >> T >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> b[i];
    }

    for (int i = 1; i <= n; ++i) {
        int sum = 0;
        for (int j = i; j <= n; ++j) {
            sum += a[j];
            va.push_back(sum);
        }
    }

    for (int i = 1; i <= m; ++i) {
        int sum = 0;
        for (int j = i; j <= m; ++j) {
            sum += b[j];
            vb.push_back(sum);
        }
    }

    sort(va.begin(), va.end());
    sort(vb.begin(), vb.end());
}

void run(){
    for(auto i : va){
        int one_b = T - i;
        int b_upper = upper_bound(vb.begin(), vb.end(), one_b) - vb.begin();
        int b_lower = lower_bound(vb.begin(), vb.end(), one_b) - vb.begin();
        cnt += (b_upper - b_lower);
    }

    cout << cnt;
}

int main(){
    fastio
    init();
    input();
    run();
    return 0;
}