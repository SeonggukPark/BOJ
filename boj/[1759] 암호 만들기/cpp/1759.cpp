#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
int l, c;
vector<char> v, rst;

bool is_possible() {
    int cnt = 0;
    char lst[5] = {'a', 'e', 'i', 'o', 'u'};
    for(auto tar : rst) {
        for (char i: lst) {
            if (tar == i) cnt++;
        }
    }
    if(cnt >= 1 && cnt <= l - 2) return true;
    return false;
}

void dfs(int idx, int dep){
    if(dep == l){
        if(is_possible()){
            for(auto i : rst){
                cout << i;
            }
            cout << endl;
        }
        return;
    }

    for (int i = idx; i < c - l + dep; ++i) {
        rst.push_back(v[i + 1]);
        dfs(i + 1, dep + 1);
        rst.pop_back();
    }
}

void run(){
    cin >> l >> c;
    char data;
    for (int i = 0; i < c; ++i) {
        cin >> data;
        v.push_back(data);
    }

    sort(v.begin(), v.end());
    dfs(-1, 0);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    run();
    return 0;
}