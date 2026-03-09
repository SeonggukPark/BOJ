#include <iostream>
#include <vector>
#include <unordered_set>
#define endl '\n'
using namespace std;
int N, M;
constexpr size_t MAX_N = 51;
int par[MAX_N], ran[MAX_N];

class UF {
public:
    int par[MAX_N], ran[MAX_N];

    UF(){
        for(int i = 1; i < MAX_N; ++i) par[i] = i;
        fill_n(ran, MAX_N, 0);
    }

    int Find(int a) {
        if (par[a] == a) return a;
        return par[a] = Find(par[a]);
    }

    void Union(int a, int b) {
        int par_a = Find(a), par_b = Find(b);
        if (par_a == par_b) return;
        if (ran[a] > ran[b]) par[par_b] = par_a;
        else if(ran[a] < ran[b]) par[par_a] = par_b;
        else par[par_b] = par_a, ran[par_a]++;
    }
};

void init() {
    cin >> N >> M;
}

void run() {
    UF uf;
    vector<vector<int>> parties(M + 1);
    int num;
    for(int i = 0; i <= M; ++i){
        cin >> num;
        parties[i].resize(num);
        for(int j = 0; j < num; ++j){
            cin >> parties[i][j];
        }
        for(int j = 0; j < num - 1; ++j){
            uf.Union(parties[i][j], parties[i][j + 1]);
        }
    }

    unordered_set<int> us;
    for(auto i : parties[0]) us.insert(uf.Find(i));

    int rst = 0;
    for(int i = 1; i <= M; ++i){
        bool flag = true;
        for(auto tar : parties[i]){
            if(us.find(uf.Find(tar)) != us.end()) {
                flag = false;
                break;
            }
        }

        if(flag) rst++;
    }

    cout << rst << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    run();
    return 0;
}
