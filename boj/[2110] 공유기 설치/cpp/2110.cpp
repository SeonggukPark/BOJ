#include <bits/stdc++.h>
using namespace std;
vector<int> v;
int n, c;

void b_search(int tar){
    int l = 1, r = v[v.size() - 1] - v[0] + 1;
    while(l + 1 < r){
        int mid = l + (r - l) / 2, cnt = 1;
        int prev = v[0];
        for(auto i : v){
            if(i - prev >= mid){
                prev = i;
                cnt++;
            }
        }
        if(cnt >= tar) l = mid;
        else r = mid;
    }
    cout << l;
}

void run(){
   cin >> n >> c;
    int tmp;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());
    b_search(c);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    run();
    return 0;
}