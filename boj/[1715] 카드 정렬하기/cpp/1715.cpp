#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

void sol(){
    int n; cin >> n;
    priority_queue<int, vector<int>, greater<>> pq;

    int tmp;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        pq.push(tmp);
    }

    int rst = 0;
    while(pq.size() >= 2){
        int l = pq.top(); pq.pop();
        int r = pq.top(); pq.pop();
        rst += (l + r);
        pq.push(l + r);
    }
    cout << rst << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sol();
    return 0;
}
