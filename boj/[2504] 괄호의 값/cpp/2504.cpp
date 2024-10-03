#include <iostream>
#include <stack>
#define x first
#define y second
#define pii pair<int, int>
#define endl '\n'
#define ll long long
using namespace std;
ll N, Q;

ll solve(){
    stack<char> stk;
    stack<ll> data;
    string str; cin >> str;

    ll acc = 0, tmp = 1;
    char prev;

    for(ll i = 0; i < str.length(); ++i){
        char tar = str[i];
        if(tar == '(' || tar == '[') {
            stk.push(tar);
            if(tar == '(') tmp *= 2;
            else tmp *= 3;
        }

        else if (tar == ')'){
            if(stk.empty() || stk.top() != '(') return 0;
            if(prev == '(') {
                acc += tmp;
                tmp /= 2;
            }
            else {
                tmp /= 2;
            }
            stk.pop();
        }

        else{
            if(stk.empty() || stk.top() != '[') return 0;
            if(prev == '[') {
                acc += tmp;
                tmp /= 3;
            }
            else {
                tmp /= 3;
            }
            stk.pop();
        }

        prev = tar;
    }

    if(!stk.empty()) return 0;
    return acc;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << solve();
    return 0;
}