#include <iostream>
#include <stack>
#define x first
#define y second
#define pii pair<int, int>
#define endl '\n'
using namespace std;
int N, Q;


void solve(){
    stack<char> stk;
    string str; cin >> str;

    int cnt = 0;
    char prev = str[0];
    stk.push(prev);

    for(int i = 1; i < str.length(); ++i){
        char tar = str[i];
        if(tar == '('){
            stk.push('(');
        }

        else {
            if(prev == '('){
                stk.pop();
                cnt += (int)stk.size();
            }

            else{
                cnt += 1;
                stk.pop();
            }
        }

        prev = tar;
    }

    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}