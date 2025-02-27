#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
using namespace std;
constexpr int p = 1e9 + 7;
ll N, K;
 
ll facto(ll input){
    ll rst = 1;
    for (ll i = 2; i <= input; i++)
    {
        rst = (rst * i) % p;
    }

    return rst;
}

ll power(ll n, ll k){
    if(k == 1) return n % p;
    ll dev = power(n, k / 2);
    
    if(k % 2 == 1) return (dev * dev % p)* n % p;
    return dev * dev % p;
}

void solve(){
    cin >> N >> K;
    cout << (facto(N) % p) * (power(facto(N - K) * facto(K) % p, p - 2) % p) % p;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}