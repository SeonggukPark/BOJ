#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define x first
#define y second
using namespace std;
int N;

int main(){
    cin >> N;
    vector<int> lst_a(N), lst_b(N);

    for (int i = 0; i < N; ++i) {
        cin >> lst_a[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> lst_b[i];
    }

    sort(lst_a.begin(), lst_a.end());
    sort(lst_b.begin(), lst_b.end(), greater<>());

    int rst = 0;
    for(int i = 0; i < N; ++i){
        rst += lst_a[i] * lst_b[i];
    }

    cout << rst;
    return 0;
}
