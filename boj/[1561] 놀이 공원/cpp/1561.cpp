#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
vector<ll> vec;
ll N, M;

void init(){
    cin >> N >> M;
    vec.resize(M);
    for(auto & i : vec) cin >> i;
}

void run(){
    if(N <= M){
        cout << N;
        return;
    }

    ll l = 0, r = (ll)6e10;
    while(l <= r){
        ll mid = l + (r - l) / 2, acc = 0;
        for(auto & x : vec) acc += 1 + mid / x;
        if(acc >= N) r = mid - 1;
        else l = mid + 1;
    }

    ll ans = -1, kids = 0;
    for(auto & x : vec) kids += 1 + r / x;


    for(int idx = 0; idx < M; ++idx){
        if(l % vec[idx] == 0) kids++;
        if(kids == N){
            ans = idx + 1;
            break;
        }
    }

    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    run();

    return 0;
}