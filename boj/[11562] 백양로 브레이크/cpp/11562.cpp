/* ---------------- Headers ----------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#define endl '\n'
using namespace std;
/* ---------------- Variables ----------------*/
int N, M;
constexpr int INF = 987654321;
vector<vector<int>> graph;
vector<vector<bool>> is_erasable;
/* ---------------- Sub-functions ----------------*/
void traverse() {
	for (auto& row : graph) {
		for (auto& c : row) cout << c << ' ';
		cout << endl;
	}
}

/* ---------------- APIs ----------------*/
void init() {
	cin >> N >> M;
	graph.assign(N, vector<int>(N, INF));

	int u, v, b;
	for (int rpt = 0; rpt < M; ++rpt) {
		cin >> u >> v >> b; u--, v--;
		graph[u][v] = 0;
		graph[v][u] = (b == 1) ? 0 : 1;
	}

	for (int k = 0; k < N; ++k) {
		for (int r = 0; r < N; ++r) {
			for (int c = 0; c < N; ++c) {
				if (graph[r][c] > graph[r][k] + graph[k][c]) graph[r][c] = graph[r][k] + graph[k][c];
			}
		}
	}
}

void run() {
	int K, x, y; cin >> K;
	while (K--){
		cin >> x >> y; x--, y--;
		if (x == y) {
			cout << 0 << endl;;
			continue;
		}
		cout << graph[x][y] << endl;
	}
}

/* ---------------- Main ----------------*/

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	init();
	run();
	return 0;
}