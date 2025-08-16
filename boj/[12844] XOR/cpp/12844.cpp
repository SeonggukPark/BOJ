#include <iostream>
#include <string>
#include <vector>
#define endl '\n'
using namespace std;
constexpr size_t MAX_NN = 5e5;
int arr[MAX_NN], tree[MAX_NN*4], lazy[MAX_NN*4];

void seg_init(int n, int s, int e){
    if(s == e) {
        tree[n] = arr[s];
        return;
    }
    int m = s + (e - s) / 2;
    seg_init(n * 2, s, m), seg_init(n * 2 + 1, m + 1, e);
    tree[n] = tree[n*2] ^ tree[n*2+1];
}

void push_down(int n, int s, int e){
    if(lazy[n] != 0){
        int len = e - s + 1;
        if(len % 2 == 1) tree[n] ^= lazy[n];  // 홀수일 때만 변화
        if(s != e){
            lazy[n*2] ^= lazy[n];
            lazy[n*2+1] ^= lazy[n];
        }
        lazy[n] = 0;
    }
}


void seg_update(int n, int s, int e, int l, int r, int diff){
    push_down(n, s, e);
    // 1. 완전히 안 겹칠 경우
    if(l > e || s > r) return;
    // 2. tree가 query에 완전히 포함
    if (s >= l && r >= e){
        lazy[n] ^= diff;
        push_down(n, s, e);
        return;
    }

    // 3. 일부 포함
    int m = s + (e - s) / 2;
    seg_update(n*2, s, m, l, r, diff), seg_update(n*2+1, m+1, e, l, r, diff);
    tree[n] = tree[n*2] ^ tree[n*2+1];
}

int seg_query(int n, int s, int e, int l, int r){
    push_down(n, s, e);
    // 1. 완전히 안 겹칠 경우
    if(l > e || s > r) return 0;
    // 2. tree가 query에 완전히 포함
    if (s >= l && r >= e){
        push_down(n, s, e);
        return tree[n];
    }

    // 3. 일부 포함
    int m = s + (e - s) / 2;
    return seg_query(n*2, s, m, l, r) ^ seg_query(n*2+1, m+1, e, l, r);
}


void run(){
    int N; cin >> N;
    for(int i = 0; i < N; ++i) cin >> arr[i];
    int M, cmd, i, j, k; cin >> M;
    seg_init(1, 0, N - 1);

    while(M--){
        cin >> cmd;
        switch (cmd) {
            case 1: // [i, j] 전체에 xor k
                cin >> i >> j >> k;
                seg_update(1, 0, N-1, i, j, k);
                break;

            case 2: // [i, j]를 모두 xor 한 결과 출력
                cin >> i >> j;
                cout << seg_query(1, 0, N-1, i, j) << endl;
                break;

            default:
                cout << "Error.." << endl;
                break;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    run();
    return 0;
}
