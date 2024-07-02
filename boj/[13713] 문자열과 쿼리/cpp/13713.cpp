#include <bits/stdc++.h>
using namespace std;
#define endl '\n' 
constexpr size_t MAX_N = 3e5, INF = 1e9+1;
int answer;

vector<int> z_algorithm(const string & s){
    vector<int> z(s.size());
    int n = (int)s.size();
    z[0] = n;

    for(int i = 1, l = 0, r = 0; i < n; i++) {
        if(i <= r)z[i] = min(r - i, z[i - l]);
        for(;s[i + z[i]] == s[z[i]];)z[i]++;
        if(i > r)l = i;
        r = max(r, i + z[i] - 1);
    }

    return z;
}


int main(int argc, char** argv){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string str;
    cin >> str;
    reverse(str.begin(), str.end());

    vector<int> rst = z_algorithm(str);
    int N = rst.size();

    int n, op; cin >> n;

    while(n--){
        cin >> op;
        cout << rst[N - op] << endl;
    }

    return 0;//Your program should return 0 on normal termination.
}