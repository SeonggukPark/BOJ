#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define pii pair<int, int>
using namespace std;
constexpr size_t MAX_N = 1e6;
constexpr int INF = 1e9 + 1;

void solve(){
    int N; cin >> N;
    vector<int> vec(N), two;
    for (int i = 0; i < N; ++i) {
        cin >> vec[i];
    }

    sort(vec.begin(), vec.end());

    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            two.push_back(vec[i] + vec[j]);
        }
    }

    sort(two.begin(), two.end());

    for (int i = N - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if(binary_search(two.begin(), two.end(), vec[i] - vec[j])) {
                cout << vec[i];
                return;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}