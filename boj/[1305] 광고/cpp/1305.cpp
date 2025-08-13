#include <iostream>
#include <string>
#include <vector>
#define endl '\n'
using namespace std;

void build_lps(const string & p){
    int m = (int)p.size();
    vector<int> lps(m, 0);
    int len = 0;
    for(int i = 1; i < m; ++i){
        while(len > 0 && p[i] != p[len]) len = lps[len - 1];
        if(p[i] == p[len]) ++len;
        lps[i] = len;
    }

    cout << m - lps[m - 1];
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    string str;
    cin >> N >> str;
    build_lps(str);
    return 0;
}
