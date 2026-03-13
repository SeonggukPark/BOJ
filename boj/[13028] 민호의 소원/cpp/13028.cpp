/* ---------------- Headers ----------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>
#define endl '\n'
using namespace std;
/* ---------------- Variables ----------------*/
struct QUERY {
	int l, r, idx;
};

int N, Q, block_size;
vector<int> vec;
vector<QUERY> queries;

bool cmp(const QUERY& a, const QUERY& b) {
    int ba = a.l / block_size;
    int bb = b.l / block_size;

    if (ba != bb) return ba < bb;
    return a.r < b.r;
}

/* ---------------- Sub-functions ----------------*/
void query(int l, int r) {

}


/* ---------------- APIs ----------------*/
void init() {
	cin >> N >> Q;
	vec.resize(N + 1), queries.resize(Q);
	for (int i = 1; i <= N; ++i) cin >> vec[i];

	for (int i = 0; i < Q; ++i) {
		cin >> queries[i].l >> queries[i].r;
		queries[i].idx = i;
	}

	block_size = (int)sqrt(N);
	sort(queries.begin(), queries.end(), cmp);
}

void run() {
    vector<int> cnt(100001, 0), ans(Q, 0);

    int curL = 1;
    int curR = 0;
    int curAns = 0;

    for (const auto& q : queries) {
        while (curL > q.l) { // 축소
            int x = vec[--curL];
            if (++cnt[x] == 3) ++curAns;
        }

        while (curR < q.r) { // 확장
            int x = vec[++curR];
            if (++cnt[x] == 3) ++curAns;
        }

        while (curL < q.l) { // 확장
            int x = vec[curL++];
            if (--cnt[x] == 2) --curAns;
        }

        while (curR > q.r) {
            int x = vec[curR--];
            if (--cnt[x] == 2) --curAns;
        }

        ans[q.idx] = curAns;
    }

    

    for (int i = 0; i < Q; ++i) {
        cout << ans[i] << '\n';
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