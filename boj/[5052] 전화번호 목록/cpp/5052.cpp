#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <unordered_map>
#include <cstdio>

#define endl '\n'
using namespace std;
constexpr size_t MAX_CHILD = 10, MAX_NODE = 100'002;
int t, n; // n ~ 10,000

struct TrieNode {
	int cnt, child[MAX_CHILD];
	bool is_end;

	void init() {
		cnt = 0;
		is_end = false;
		for (int i = 0; i < MAX_CHILD; ++i) child[i] = -1;
	}
};

TrieNode node_pool[MAX_NODE];
TrieNode *cur_node, *root = &node_pool[0];
int node_idx = 0;

void init() {
	cin >> n;
	node_idx = 1;
	root->init();
}

void run() {
	string nums;
	bool is_ok = true;

	while (n--) {
		cin >> nums;
		cur_node = root;
		
		if (!is_ok) continue;
		
		for (auto num : nums) {
			int digit = num - '0';
			if (cur_node->is_end) {
				is_ok = false;
				break;
			}

			if (cur_node->child[digit] == -1) {
				node_pool[node_idx].init();
				cur_node->child[digit] = node_idx++;
			}
			cur_node = &node_pool[cur_node->child[digit]];
		}

		for (int i = 0; i < MAX_CHILD; ++i) {
			if (cur_node->child[i] != -1) {
				is_ok = false;
			}
		}

		cur_node->is_end = true;
	}

	cout << (is_ok ? "YES" : "NO") << endl;
	return;
}


int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	cin >> t;
	while (t--) {
		init();
		run();
	}

	return 0;
}