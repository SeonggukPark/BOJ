#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define endl '\n'
using namespace std;

int N;
vector<long long> energys;

struct Edge {
    int to;
    int w;
};

vector<vector<Edge>> adj;

int LOGN;
vector<vector<int>> up;              // up[k][v]
vector<vector<long long>> distUp;    // distUp[k][v]
vector<int> depth;

void init() {
    cin >> N;
    energys.assign(N + 1, 0);
    for (int i = 1; i <= N; ++i) cin >> energys[i];

    adj.assign(N + 1, {});
    for (int i = 0; i < N - 1; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        adj[a].push_back({b, d});
        adj[b].push_back({a, d});
    }

    LOGN = 1;
    while ((1 << LOGN) <= N) LOGN++;
    up.assign(LOGN, vector<int>(N + 1, 0));
    distUp.assign(LOGN, vector<long long>(N + 1, 0));
    depth.assign(N + 1, -1);

    // 루트(1) 기준으로 부모/깊이 설정 (BFS)
    queue<int> q;
    depth[1] = 0;
    up[0][1] = 1;
    distUp[0][1] = 0;
    q.push(1);

    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (auto &e : adj[cur]) {
            int nxt = e.to;
            if (depth[nxt] != -1) continue;
            depth[nxt] = depth[cur] + 1;
            up[0][nxt] = cur;
            distUp[0][nxt] = e.w;
            q.push(nxt);
        }
    }

    // 바이너리 리프팅 전처리
    for (int k = 1; k < LOGN; ++k) {
        for (int v = 1; v <= N; ++v) {
            int mid = up[k - 1][v];
            up[k][v] = up[k - 1][mid];
            distUp[k][v] = distUp[k - 1][v] + distUp[k - 1][mid];
        }
    }
}

void run() {
    for (int i = 1; i <= N; ++i) {
        int cur = i;
        long long energy = energys[i];

        for (int k = LOGN - 1; k >= 0; --k) {
            int anc = up[k][cur];
            long long need = distUp[k][cur];
            if (anc == 0) continue;
            if (cur == 1) break;
            if (need <= energy) {
                energy -= need;
                cur = anc;
            }
        }
        cout << cur << endl;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    run();
    return 0;
}
