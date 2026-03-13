/* ---------------- Headers ----------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#define endl '\n'
using namespace std;
using ll = long long;

/* ---------------- Variablesl ----------------*/

ll N; // 수의 개수, ~ 100,000
ll Q; // 턴의 개수, ~ 100,000

vector<ll> tree, arr;

/* ---------------- Sub-functions ----------------*/
void traverse(const vector<ll>& vec) {
	for (auto i : vec) cout << i << ' ';
	cout << endl;
}

ll build(ll node, ll start, ll end) {
	if (start == end) return tree[node] = arr[start];
	
	int mid = (start + end) / 2;
	return tree[node] = build(node * 2, start, mid) + build(node * 2 + 1, mid + 1, end);
}

ll update(ll node, ll start, ll end, ll idx, ll diff) {
	if (start > idx || idx > end) return tree[node];
	tree[node] += diff;
	if (start == end) return tree[node];
	
	int mid = (start + end) / 2;
	return tree[node] = update(node * 2, start, mid, idx, diff) + update(node * 2 + 1, mid + 1, end, idx, diff);
}

ll query(ll node, ll ts, ll te, ll qs, ll qe) {
	if (ts > qe || te < qs) return 0;
	if (ts >= qs && te <= qe) return tree[node];

	int mid = (ts + te) / 2;
	return query(node * 2, ts, mid, qs, qe) + query(node * 2 + 1, mid + 1, te, qs, qe);
}


/* ---------------- APIs ----------------*/
void init() {
	cin >> N >> Q;
	arr.resize(N);

	for (auto& num : arr) cin >> num;

	// 세그 트리 생성
	tree.resize(N * 4);
	build(1, 0, N - 1);
}

void run() {

	ll x, y, a, b; // [x, y] 합 출력, a번째 수 b로 업데이트
	for (int i = 0; i < Q; ++i) {
		cin >> x >> y >> a >> b;

		// query
		if (x > y) swap(x, y);
		cout << query(1, 0, N - 1, x - 1, y - 1) << endl;

		// update
		update(1, 0, N - 1, a - 1, b - arr[a - 1]);
		arr[a - 1] = b;

		// traverse(tree);
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