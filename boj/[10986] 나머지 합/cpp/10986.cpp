#include <string>
#include <vector>
#include <iostream>
#define INF 987654321
#define ll long long
#define endl '\n'
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<ll> input(N), acc(N, 0), cnt(M, 0);

    for (int i = 0; i < N; ++i) {
        cin >> input[i];
    }

    acc[0] = input[0];
    for (int i = 1; i < N; ++i) {
        acc[i] = acc[i - 1] + input[i];
    }

    for(ll i : acc) cnt[i % M]++;
    ll rst = cnt[0];

    for(ll i : cnt){
        if(i != 0) rst += i * (i - 1) / 2;
    }

    cout << rst;
    return 0;
}