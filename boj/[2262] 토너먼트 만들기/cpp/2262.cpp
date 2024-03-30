#include <bits/stdc++.h>
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;
vector<int> v;
int rst;

int main(){
    fastio
    rst = 0;
    int n, tmp;
    cin >> n;

    while(n--){
        cin >> tmp;
        v.push_back(tmp);
    }

    if(v.size() == 1){
        cout << 0;
        return 0;
    }

    while(v.size() > 2){
        auto tar = max_element(v.begin(), v.end());

        // 맨 앞일 경우
        if(tar == v.begin()){
            rst += *tar - *(tar + 1);
        }

        // 맨 뒤일 경우
        else if(tar == v.end() - 1){
            rst += *tar - *(tar - 1);
        }

        else{
            rst += *tar - max(*(tar+1), *(tar-1));
        }


        v.erase(tar);
    }

    rst += abs(v[0] - v[1]);
    cout << rst;

    return 0;
}