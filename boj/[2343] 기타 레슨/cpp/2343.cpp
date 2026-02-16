#include <iostream>
#include <vector>
using namespace std;
vector<int> vec;
int N, M;

void init(){
    cin >> N >> M;
    vec.resize(N);
    for(auto & i : vec) cin >> i;
}

void run(){
    int l = 0, r = 0;
    for (const auto &x : vec) {
        if (x > l) l = x;   // 최소 용량: max(lecture)
        r += x;             // 최대 용량: sum(lecture)
    }

    while(l <= r){
        int mid = l + (r - l) / 2, acc = 0, cnt = 1;
        for(const auto & i : vec){
            if(acc + i <= mid) acc += i;
            else{
                cnt++, acc = i;
            }
        }

        if(cnt > M) l = mid + 1;
        else r = mid - 1;
    }

    cout << l;
}

int main(){
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    run();

    return 0;
}