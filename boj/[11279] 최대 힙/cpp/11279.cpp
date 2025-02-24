#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
int N;
 
void solve(){
    cin >> N;
    int x;
    priority_queue<int> pq; 

    while(N--){
        cin >> x;

        if(x == 0){
            if(pq.empty()){
                cout << 0 << endl;
                continue;
            }
            
            cout << pq.top() << endl;
            pq.pop();
        } 

        else if(x > 0){
            pq.push(x);            
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}