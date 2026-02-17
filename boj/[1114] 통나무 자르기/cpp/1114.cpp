#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int L, C, K;
vector<int> vec;

void init(){
    cin >> L >> K >> C;
    vec.resize(K);
    for(auto & i : vec) cin >> i;
    vec.push_back(0);
    vec.push_back(L);
    sort(vec.begin(), vec.end());
}

bool check(int mid){
    int last = L, cuts = 0;
    for(int i = (int)vec.size() - 2; i >= 0; --i){
        if(vec[i + 1] - vec[i] > mid) return false;
        if(last - vec[i] > mid){
            last = vec[i + 1], cuts++;
            if(cuts > C) return false;
        }
    }
    return true;
}

int firstCutPos(int mid){
    int last = L;
    int cuts = 0;
    int first = 0; // 실제로 자른 것 중 가장 왼쪽(최소 좌표)

    for(int i = (int)vec.size() - 2; i >= 0; --i){
        if(last - vec[i] > mid){
            last = vec[i + 1];
            cuts++;
            first = vec[i + 1]; // 오른쪽부터 진행하니 갱신될수록 더 왼쪽
        }
    }

    // 더 자를 수 있으면(필수 cuts < C) 첫 절단을 가장 왼쪽 절단점으로 당길 수 있음
    if(C > cuts){
        if((int)vec.size() >= 3) return vec[1];
        return 0; // 자를 곳이 없음(K=0)
    }
    return first; // 필수 cuts == C인 경우
}

void run(){
    int l = 1, r = L;
    while(l <= r){
        int mid = l + (r - l) / 2;
        if(check(mid)) r = mid - 1;
        else l = mid + 1;
    }
    int bestLen = l;
    int cutPos = firstCutPos(bestLen);
    cout << bestLen << ' ' << cutPos << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    run();
    return 0;
}
