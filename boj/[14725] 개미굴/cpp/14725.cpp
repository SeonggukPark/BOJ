#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdio>
#include <stack>
#include <map>
#define endl '\n'
using namespace std;
constexpr size_t MAX_NODE = 15001;
int N, node_idx;

struct TrieNode {
	string data;
	map<string, int, greater<>> kids;
	int dep;

	void init(int cur_dep) {
		kids.clear();
		dep = cur_dep;
	}
};

TrieNode node_pool[MAX_NODE];
TrieNode* cur_node, * root = &node_pool[0];

void print(int d, const string & str) {
	d *= 2;
	while (d--) cout << '-';
	cout << str << endl;
}

void traverse() {
	// stack 선언 후 0 (root node idx) 삽입
	stack<int> stk;
	stk.push(0);

	while (!stk.empty()) {	
		// top 추출
		auto top = stk.top(); stk.pop();
		TrieNode* top_node = &node_pool[top];

		// (dep * 2)회 '-' + data 출력 + 개행
		if(top != 0) print(top_node->dep, top_node->data);
		
		// top의 kids 순환하면서 stack에 넣기
		for (auto& kid : top_node->kids) {
			stk.push(kid.second);
		}
	}
}


void init() {
	cin >> N;
	node_idx = 1;
	root->init(0);
}


void run() {
	int dep;
	string word;
	while (N--) {
		cur_node = root;
		cin >> dep;
		for (int cur_dep = 0; cur_dep < dep; ++cur_dep) {
			cin >> word;

			// cur_node의 kids에 word 키 값이 존재하지 않으면 
			if (cur_node->kids.count(word) == 0) {
				// {word, node_idx++} 추가
				cur_node->kids[word] = node_idx++;
				node_pool[cur_node->kids[word]].data = word;
				node_pool[cur_node->kids[word]].dep = cur_dep;
			}

			// cur_node 이동
			cur_node = &node_pool[cur_node->kids[word]];
		}
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