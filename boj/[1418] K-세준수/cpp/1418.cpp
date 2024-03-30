#include <bits/stdc++.h>
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr size_t MAX_N = 100000;
int N, K, cnt;
bool table[MAX_N + 1];
priority_queue<int> pq;

void make_table(){
    memset(table, 0, sizeof(table));

    for(int i = 2; i <= MAX_N; ++i){
        if(!table[i]){
            for(int j = 2; j * i <= MAX_N; j++){
                table[i * j] = true;
            }
        }
    }
}

void traverse(int n){
    for(int i = 2; i <= n; ++i){
        if(!table[i]){
            while(n % i == 0){
                pq.push(i);
                n /= i;
            }
        }
    }

    if(pq.top() <= K) cnt++;
}

int main() {
    fastio;
    cin >> N >> K;
    make_table();
    cnt = 1;

    for(int i = 2; i <= N; i++){
        pq = {};
        traverse(i);
    }

    cout << cnt;
    return 0;
}