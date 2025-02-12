
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
int N, M;
 
void solve(){
    cin >> N;
    vector<int> vec(N);
    for(int rpt = 0; rpt < N; ++rpt){
        cin >> vec[rpt];
    }

    sort(vec.begin(), vec.end());

    cin >> M;
    int tar;
    for(int rpt = 0; rpt < M; ++rpt){
        cin >> tar;

        int lo = 0, hi = N - 1, flag = 0;

        while(lo <= hi){
            // cout << lo << ' ' << hi << endl;
            int mid = lo + (hi - lo) / 2;
            if (vec[mid] == tar){
                flag = 1;
                break;
            }
            else if(vec[mid] > tar) hi = mid - 1;
            else lo = mid + 1;
        }

        cout << flag << endl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}