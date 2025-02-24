#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
int N;

struct cmp{
    bool operator()(int & a, int & b){
        return a > b;
    }
};
 
void solve(){
    cin >> N;
    int x;
    priority_queue<int, vector<int>, cmp> pq; 

    while(N--){
        cin >> x;
        
        if(!x){
            if(pq.empty()) {
                cout << 0 << endl;
                continue;
            }

            cout << pq.top() << endl;
            pq.pop();
        }

        else pq.push(x);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}