#include <string>
#include <vector>
#include <iostream>
#define INF 987654321
#define endl '\n'
using namespace std;
constexpr size_t MAX_N = 125;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, a, b; cin >> N >> M;
    vector<int> vec(N + 1), acc(N + 1, 0);

    acc[0] = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> vec[i];
        acc[i] = acc[i - 1] + vec[i];
    }

    while(M--){
        cin >> a >> b;
        cout << acc[b] - acc[a - 1] << endl;
    }

    return 0;
}