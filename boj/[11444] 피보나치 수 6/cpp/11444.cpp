#include <iostream>
#include <utility>
#define f first
#define s second
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
constexpr ll DIV = 1000000007;
ll N;

pll fibo_calc(ll n){ // f_n, f_n+1
    if(n == 0) return {0, 1};

    ll k = n / 2;
    pll fibo_n = fibo_calc(k); // f_k, f_k+1

    ll a = fibo_n.f % DIV; // F(k)
    ll b = fibo_n.s % DIV; // F(k+1)

    ll t = (2LL * b) % DIV;
    t = (t - a + DIV) % DIV; // (2*b - a) mod DIV (음수 방지)

    ll f_2k   = (a * t) % DIV;
    ll f_2k_1 = ( (b * b) % DIV + (a * a) % DIV ) % DIV;

    if(n % 2 == 0) return {f_2k, f_2k_1};
    return {f_2k_1, (f_2k + f_2k_1) % DIV};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("input.txt", "r", stdin);
    cin >> N;
    cout << fibo_calc(N).f % DIV;
    return 0;
}
