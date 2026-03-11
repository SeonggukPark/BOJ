#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdio>
#include <stack>
#include <map>

#define endl '\n'
using namespace std;
int N, node_idx;
constexpr size_t MAX_NODE = 25000;

struct TrieNode {
	string data;
	map<string, int, greater<>> kids;
	int dep;

	void init(const string & str, int in_dep) {
		data = str;
		kids.clear();
		dep = in_dep;
	}
};

TrieNode node_pool[MAX_NODE];
TrieNode* cur_node, * root_node = &node_pool[0];

void print(const string & str, int dep) {
	while (dep--) cout << ' ';
	cout << str << endl;
}

void new_node(const string& str, int dep) {
	cur_node->kids[str] = node_idx;
	node_pool[node_idx++].init(str, dep);
}

void traverse() {
	stack<int> stk;
	stk.push(0);

	while (!stk.empty()) {
		auto top = stk.top(); stk.pop();
		TrieNode* node = &node_pool[top];
		if(top != 0) print(node->data, node->dep);
		for (auto & kid : node->kids) {
			stk.push(kid.second);
		}
	}
}

void init() {
	cin >> N;
	node_idx = 1;
	root_node->init("", 0);
}

void run() {
	string dirs;
	while (N--) {
		cin >> dirs;
		int prev = 0, cur_dep = 0, len = (int)dirs.length();
		cur_node = root_node;

		for (int idx = 1; idx < len; ++idx) {
			if (dirs[idx] == '\\') {
				string dir = dirs.substr(prev, idx - prev);
				prev = idx + 1;
				if(cur_node->kids.count(dir) == 0) new_node(dir, cur_dep);
				cur_dep++;
				cur_node = &node_pool[cur_node->kids[dir]];
			}
		}

		string dir = dirs.substr(prev, len - prev);
		if (cur_node->kids.count(dir) == 0) new_node(dir, cur_dep);
	}

	traverse();
}


int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	init();
	run();

	return 0;
}