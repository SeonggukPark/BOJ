/* ---------------- Headers ---------------- */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#define endl '\n'
using namespace std;

/* ---------------- Variables ---------------- */
struct NODE {
	int dest;
	long long cost;
};

struct cmp {
	bool operator()(const NODE& a, const NODE& b) const {
		return a.cost > b.cost;
	}
};

int V; // 도시 수
int E; // 도로 수
int M, x; // 맥세권 수, 조건
int S, y; // 스세권 수, 조건

const long long INF = 987654321;

vector<vector<NODE>> graph;
vector<int> dist_macs, dist_stars, macs, stars, can_house;

/* ---------------- APIs ---------------- */
void traverse(const vector<int>& vec) {
	for (auto& i : vec) cout << i << ' ';
	cout << endl;
}

void init() {
	cin >> V >> E;
	graph.assign(V + 1, vector<NODE>());
	dist_macs.assign(V + 1, INF);
	dist_stars.assign(V + 1, INF);
	can_house.assign(V + 1, true);

	int u, v, w;
	for (int i = 0; i < E; ++i) {
		cin >> u >> v >> w;
		graph[u].push_back({ v, w });
		graph[v].push_back({ u, w });
	}

	cin >> M >> x;
	macs.resize(M);
	for (int i = 0; i < M; ++i) {
		cin >> macs[i];
		can_house[macs[i]] = false;
 	}

	cin >> S >> y;
	stars.resize(S);
	for (int i = 0; i < S; ++i) {
		cin >> stars[i];
		can_house[stars[i]] = false;
	}
}

void dijkstra(bool is_macs) {
	auto& dists = (is_macs) ? dist_macs : dist_stars;

	priority_queue<NODE, vector<NODE>, cmp> dijk_pq;

	if (is_macs) {
		for (auto& mac : macs) {
			dists[mac] = 0;
			dijk_pq.push({ mac, 0 });
		}
	}

	else {
		for (auto& star : stars) {
			dists[star] = 0;
			dijk_pq.push({ star, 0 });
		}
	}


	while (!dijk_pq.empty()) {
		auto top = dijk_pq.top(); dijk_pq.pop();
		if (dists[top.dest] != top.cost) continue; // lazy deletion

		for (auto& next : graph[top.dest]) {
			if (dists[next.dest] > top.cost + next.cost) {
				dists[next.dest] = top.cost + next.cost;
				dijk_pq.push({ next.dest, dists[next.dest] });
			}
		}
	}

}

void run() {
	dijkstra(true); // mac
	dijkstra(false); // stars

	// traverse(dist_macs);
	// traverse(dist_stars);

	int rst = INF;
	for (int i = 1; i <= V; ++i) {
		// cout << i << ' ' << dist_macs[i] << ' ' <<  dist_stars[i] << ' ' << can_house[i] << endl;
		if ((can_house[i] != 0) && (dist_macs[i] <= x) && (dist_stars[i] <= y) && (rst > (dist_macs[i] + dist_stars[i]))) {
			rst = dist_macs[i] + dist_stars[i];
			// cout << rst << endl;
		}
	}

	cout << (rst == INF ? -1 : rst);
}

/* ---------------- Main ---------------- */
int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	init();
	run();
	return 0;
}