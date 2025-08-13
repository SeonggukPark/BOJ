#include <iostream>
#include <string>
#include <vector>
#define endl '\n'
using namespace std;

vector<int> build_lps(const string & p){
    int m = (int)p.size();
    vector<int> lps(m, 0);
    int len = 0;
    for(int i = 1; i < m; ++i){
        while(len > 0 && p[i] != p[len]) len = lps[len - 1];
        if(p[i] == p[len]) ++len;
        lps[i] = len;
    }
    return lps;
}

void kmp(const string & t, const string & p){
    int n = (int)t.size(), m = (int)p.size();
    vector<int> pos;

    if(m == 0 || n < m){
        cout << 0 << endl << endl; // 빈 줄 포함
        return;
    }

    vector<int> lps = build_lps(p);
    int len = 0;
    for(int i = 0; i < n; ++i){
        while(len > 0 && t[i] != p[len]) len = lps[len - 1];
        if(t[i] == p[len]) ++len;
        if(len == m){
            pos.push_back(i - m + 1); // 0-based
            len = lps[len - 1];       // 겹치는 매치 허용
        }
    }

    cout << (int)pos.size() << endl;
    for(size_t i = 0; i < pos.size(); ++i){
        if(i) cout << ' ';
        cout << pos[i] + 1;           // 1-based 출력
    }
    cout << endl;                      // ✅ 둘째 줄 개행
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string t, p;
    getline(cin, t);
    getline(cin, p);
    kmp(t, p);
    return 0;
}
