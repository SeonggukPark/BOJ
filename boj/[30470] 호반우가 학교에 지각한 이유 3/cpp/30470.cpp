#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define endl '\n'
#define x first
#define y second
using namespace std;

void solve(){
    int N;
    cin >> N;
    ll rst = 0;
    ll a, b, pivot, cnt;
    stack<pll> stk; // val, cnt
    while(N--){
        cin >> a >> b;

        switch (a) {
            case 1:
                stk.emplace(b, 1);
                break;

            case 2:
                if(stk.empty()) continue;
                cnt = 0;
                pivot = (stk.top().x > b) ? stk.top().x - b : 0;

                if(pivot == 0){
                    rst = 0, stk = {};
                    continue;
                }

                while(!stk.empty() && (stk.top().x >= pivot)) {
                    cnt += stk.top().y, stk.pop();
                }

                stk.emplace(pivot, cnt);
                break;

            default:
                cout << "error occured.." << endl;
                break;
        }
    }

    while(!stk.empty()){
        rst += stk.top().x * stk.top().y;
        stk.pop();
    }

    cout << rst;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}