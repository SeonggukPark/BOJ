#include <bits/stdc++.h>
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
    fastio;
    int tmp;
    int arr[6] = {1, 1, 2, 2, 2, 8};

    for(int i : arr){
        cin >> tmp;
        cout << i - tmp << ' ';
    }

    return 0;
}