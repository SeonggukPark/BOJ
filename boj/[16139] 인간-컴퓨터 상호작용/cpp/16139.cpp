#include <string>
#include <vector>
#include <iostream>
#define INF 987654321
#define endl '\n'
#define ALPHA 26
using namespace std;
constexpr size_t MAX_N = 125;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string str; cin >> str;
    int q, N = (int)str.size(); cin >> q;

    vector<vector<int> > cnt(ALPHA + 1, vector<int>(N + 1, 0)), acc(ALPHA + 1, vector<int>(N + 1, 0));

    for(int idx = 1; idx <= N; ++idx){
        char c = str[idx - 1];
        cnt[c - 'a'][idx] = 1;

        for(int i = 0; i < ALPHA; ++i){
            acc[i][idx] = acc[i][idx - 1] + cnt[i][idx];
        }
    }
/*
    for(int idx = 1; idx <= N; ++idx){
        for(int i = 0; i < ALPHA; ++i){
            cout << acc[i][idx] << ' ';
        }
        cout << endl;
    }
*/
    char query;
    int l, r;
    while(q--){
        cin >> query >> l >> r;
        cout << acc[query - 'a'][r + 1] - acc[query - 'a'][l] << endl;
    }

    return 0;
}