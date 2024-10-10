#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define pii pair<int, int>
using namespace std;
constexpr size_t MAX_N = 1e5 + 1;
constexpr int INF = 0x7fffffff;
set<string, greater<>> exist_list;

void solve() {
    int N;
    cin >> N;
    string name, stat;
    while (N--) {
        cin >> name >> stat;
        if (stat == "enter") exist_list.insert(name);
        else exist_list.erase(name);
    }

    for (const string &str: exist_list) cout << str << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}