#include <bits/stdc++.h>
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
    fastio;
    string input, rev;

    cin >> input;
    rev = input;
    reverse(rev.begin(), rev.end());

    input == rev ? cout << 1 : cout << 0;
    return 0;
}