#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

void sol(){
    int n; cin >> n;
    vector<int> v;

    int tmp;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        v.push_back(tmp);
    }

    sort(v.begin(), v.end());
    int idx = ((int)v.size() + 1) / 2 - 1;
    cout << v[idx] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sol();
    return 0;
}
