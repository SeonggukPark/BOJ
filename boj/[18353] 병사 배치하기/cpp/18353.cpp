#include <bits/stdc++.h>
using namespace std;
constexpr int MAX_N = 2e3, INF = -987654321;
int n, arr[MAX_N + 1];
vector<int> v;

void run(){
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        arr[i] = -arr[i];
    }
    v.push_back(INF);

    for (int i = 1; i <= n; ++i) {
        int idx = (int)(lower_bound(v.begin(), v.end(), arr[i]) - v.begin());
        if(idx >= v.size()){
            v.push_back(arr[i]);
        }

        else{
            v[idx] = arr[i];
        }
    }

    cout << n - v.size() + 1;
}

int main(int argc, char** argv){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    run();
    return 0;
}