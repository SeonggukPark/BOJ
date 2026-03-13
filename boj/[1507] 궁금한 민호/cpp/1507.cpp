/* ---------------- Headers ----------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#define endl '\n'
using namespace std;
/* ---------------- Variables ----------------*/
int N;
constexpr int INF = 987654321;
vector<vector<int>> graph;
vector<vector<bool>> is_erasable;
/* ---------------- Sub-functions ----------------*/

/* ---------------- APIs ----------------*/
void init() {
	cin >> N;
	graph.assign(N, vector<int>(N, INF));
	is_erasable.assign(N, vector<bool>(N, false));

	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < N; ++c) {
			cin >> graph[r][c];
		}
	}
}

void run() {
	for (int k = 0; k < N; ++k) {
		for (int r = 0; r < N; ++r) {
			for (int c = 0; c < N; ++c) {
				if (graph[r][c] > graph[r][k] + graph[k][c]) {
					cout << -1;
					return;
				}
				else if (graph[r][c] == (graph[r][k] + graph[k][c])) {
					if(k != r && k != c) is_erasable[r][c] = true;
				}
			}
		}
	}

	int acc = 0;
	for (int r = 0; r < N; ++r) {
		for (int c = r + 1; c < N; ++c) {
			if (!is_erasable[r][c]) acc += graph[r][c];
		}
	}
	cout << acc;
}

/* ---------------- Main ----------------*/

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	init();
	run();
	return 0;
}