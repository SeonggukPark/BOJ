#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
int N;

struct num{
    int abs, is_minus; // -1: minus, 1: plus
};

struct cmp{
    bool operator()(const num & a, const num & b){
        if(a.abs != b.abs) return a.abs > b.abs;
        return a.is_minus > b.is_minus;
    }
};
 
void solve(){
    cin >> N;
    int x;
    priority_queue<num, vector<num>, cmp> pq; 

    while(N--){
        cin >> x;
        
        if(!x){
            if(pq.empty()) {
                cout << 0 << endl;
                continue;
            }

            cout << pq.top().abs * pq.top().is_minus << endl;
            pq.pop();
        }

        else{
            x > 0 ? pq.push({abs(x), 1}) : pq.push({abs(x), -1});
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}