/* ---------------- Headers ----------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#define endl '\n'
using namespace std;
using ll = long long;

/* ---------------- Variablesl ----------------*/

ll N; // 집의 개수, ~ 100,000
ll T; // 색의 개수, ~ 30
ll D; // 작업의 개수, ~ 100,000

vector<ll> tree, arr, lazy;

/* ---------------- Sub-functions ----------------*/
void traverse(const vector<ll>& vec) {
	for (auto i : vec) cout << i << ' ';
	cout << endl;
}

void propagate(ll node, ll start, ll end) {
	if (lazy[node] == 0) return;
	tree[node] = lazy[node];

	if (start != end) {
		lazy[node * 2] = lazy[node];
		lazy[node * 2 + 1] = lazy[node];
	}

	lazy[node] = 0;
}

ll build(ll node, ll start, ll end) {
	if (start == end) return tree[node] = arr[start];
	
	ll mid = (start + end) / 2;
	return tree[node] = build(node * 2, start, mid) | build(node * 2 + 1, mid + 1, end);
}

void update(ll node, ll start, ll end, ll left_idx, ll right_idx, ll data) {
	propagate(node, start, end);

	// 1. 아예 안 겹침
	if (start > right_idx || left_idx > end) return;
	
	// 2. 완전히 겹침
	if (left_idx <= start && end <= right_idx) {
		lazy[node] = data;
		propagate(node, start, end);
		return;
	}

	// 3. 일부 겹침
	ll mid = (start + end) / 2;
	update(node * 2, start, mid, left_idx, right_idx, data);
	update(node * 2 + 1, mid + 1, end, left_idx, right_idx, data);
	tree[node] = tree[node * 2] | tree[node * 2 + 1];
}

ll query(ll node, ll start, ll end, ll left_idx, ll right_idx) {
	propagate(node, start, end);

	// 1. 아예 안 겹침
	if (start > right_idx || left_idx > end) return 0;

	// 2. 완전히 겹침
	if (left_idx <= start && end <= right_idx) return tree[node];
	
	// 3. 일부 겹침
	ll mid = (start + end) / 2;
	return query(node * 2, start, mid, left_idx, right_idx) | query(node * 2 + 1, mid + 1, end, left_idx, right_idx);
}

ll bit_masker(ll x) {
	return (1 << (x - 1));
}


// x에서 1인 bit 개수 반환
int mask_count(ll x) {
	int cnt = 0;

	while (x != 0) {
		cnt += (x & 1);
		x >>= 1;
	}

	return cnt;
}


/* ---------------- APIs ----------------*/
void init() {
	cin >> N >> T >> D;
	arr.assign(N, 1);

	// 세그 트리 생성
	tree.resize(N * 4), lazy.resize(N * 4);
	build(1, 0, N - 1);
}

void run() {
	char cmd;
	ll x, y, z;
	

	while (D--) {
		cin >> cmd;
		switch (cmd) {
			case 'C':
				cin >> x >> y >> z;
				if (x > y) swap(x, y);
				update(1, 0, N - 1, x - 1, y - 1, bit_masker(z));
				break;

			case 'Q':
				cin >> x >> y;
				if (x > y) swap(x, y);
				cout << mask_count(query(1, 0, N - 1, x - 1, y - 1)) << endl;
				break;

			default:
				break;
		}
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