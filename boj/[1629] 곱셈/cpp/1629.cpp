#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>
#define INF 987654321
#define ll long long
#define endl '\n'
using namespace std;
unordered_map<ll, ll> um;

ll pow(ll a, ll b, ll c){
    if(b == 1) return a % c;
    if(um.find(b) != um.end()) return um[b];

    um[b] = (pow(a, b / 2, c) % c) * (pow(a, b - b / 2, c) % c) % c;
    return um[b];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b, c; cin >> a >> b >> c;
    cout << pow(a, b, c);
    return 0;
}