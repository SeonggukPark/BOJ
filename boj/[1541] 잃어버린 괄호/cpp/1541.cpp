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

    int rst = 0;
    string str, buf; cin >> str;
    bool is_minus = false;

    for(char c : str){
        if(c == '-'){
            int num = stoi(buf);
            if(is_minus) rst -= num;
            else rst += num;
            is_minus = true;
            buf.clear();
        }

        else if(c == '+'){
            int num = stoi(buf);
            if(is_minus) rst -= num;
            else rst += num;
            buf.clear();
        }

        else buf.push_back(c);
    }

    int num = stoi(buf);
    if(is_minus) rst -= num;
    else rst += num;

    cout << rst;
    return 0;
}