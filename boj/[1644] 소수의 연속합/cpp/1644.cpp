#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define endl '\n'
#define ll long long
int N;
constexpr int MAX_N = 4e6;

// n까지의 소수 구하기 (에라토스테네스의 체)
void find_primes(int end, vector<int>& vec){
    int root = (int)sqrt(end);
    vector<bool> nest(end + 1, true);

    for(int i = 2; i <= root; ++i){
        if(!nest[i]) continue;
        for(int j = i * i; j <= end; j += i){
            nest[j] = false;
        }
    }

    for(int i = 2; i <= end; ++i){
        if(nest[i]) vec.push_back(i);
    }
}

void input(){
    cin >> N;
}

int solve(){
    // 소수 리스트 구하기
    vector<int> primes; // maximum 283146개
    find_primes(MAX_N, primes);

    // 소수 구간합 구하기
    vector<long long> acc_primes(primes.size() + 1, 0);
    for(int i = 1; i <= (int)primes.size(); ++i)
        acc_primes[i] = acc_primes[i - 1] + primes[i - 1];

    int r = 1, l = 0, cnt = 0;
    while(r < (int)acc_primes.size()){
        if (l >= r) {
            r = l + 1;
            continue;
        }
        long long sum = acc_primes[r] - acc_primes[l];
        if(sum < (long long)N) r++;
        else{
            if(sum == (long long)N) cnt++;
            l++;
        }
    }

    return cnt;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    input();
    cout << solve();
    return 0;
}