#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

/* ------------------ Lazy Segment Tree ------------------ */
/*  - 기능: range add, point query
 *  - 트리 노드는 구간 합을 저장하지만, 우리는 점 질의만 사용
 *    (구간 합을 유지하면 구현이 표준적이고, 범용 확장도 쉬움)
 */
struct SegTree {
    int n;
    vector<long long> t, lazy; // t: 구간합, lazy: 지연 덧셈

    SegTree() : n(0) {}
    explicit SegTree(int n_) { init(n_); }

    void init(int n_) {
        n = 1;
        while (n < n_) n <<= 1;
        t.assign(n << 1, 0LL);
        lazy.assign(n << 1, 0LL);
    }

    // 내부용: 현재 노드에 val을 덧셈 적용
    inline void apply(int node, int nl, int nr, long long val) {
        t[node] += val * (nr - nl + 1);
        lazy[node] += val;
    }

    // 내부용: lazy 전파
    inline void push(int node, int nl, int nr) {
        if (lazy[node] == 0 || nl == nr) return;
        int mid = (nl + nr) >> 1;
        int lc = node << 1, rc = lc | 1;
        apply(lc, nl, mid, lazy[node]);
        apply(rc, mid + 1, nr, lazy[node]);
        lazy[node] = 0;
    }

    // [l, r]에 +val
    void range_add(int l, int r, long long val) { range_add(1, 1, n, l, r, val); }
    void range_add(int node, int nl, int nr, int l, int r, long long val) {
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) { apply(node, nl, nr, val); return; }
        push(node, nl, nr);
        int mid = (nl + nr) >> 1, lc = node << 1, rc = lc | 1;
        range_add(lc, nl, mid, l, r, val);
        range_add(rc, mid + 1, nr, l, r, val);
        t[node] = t[lc] + t[rc];
    }

    // pos의 값(= prefix의 누적 결과)을 질의
    long long point_query(int pos) { return point_query(1, 1, n, pos); }
    long long point_query(int node, int nl, int nr, int pos) {
        if (nl == nr) return t[node];
        push(node, nl, nr);
        int mid = (nl + nr) >> 1;
        if (pos <= mid) return point_query(node << 1, nl, mid, pos);
        else return point_query((node << 1) | 1, mid + 1, nr, pos);
    }
};

/* ------------------ Globals ------------------ */
int N, M, root;
vector<vector<int>> children;
vector<int> in_t, out_t;
int timer_;

/* ------------------ Euler Tour (iterative, entry-only) ------------------ */
void build_euler(int r) {
    in_t.assign(N + 1, 0);
    out_t.assign(N + 1, 0);
    timer_ = 0;

    // 상태: 0=진입, 1=퇴장
    stack<pair<int,int>> st;
    st.push({r, 0});

    while (!st.empty()) {
        auto [u, state] = st.top(); st.pop();
        if (state == 0) {
            in_t[u] = ++timer_;
            st.push({u, 1});
            // children를 역순으로 푸시하면 실제 방문은 원래 순서
            for (int i = (int)children[u].size() - 1; i >= 0; --i) {
                int v = children[u][i];
                st.push({v, 0});
            }
        } else {
            out_t[u] = timer_;
        }
    }
}

/* ------------------ Main ------------------ */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> N >> M)) return 0;
    children.assign(N + 1, {});
    root = 1;

    // 입력: p1 p2 ... pN (p1=-1), i의 부모가 p_i
    for (int i = 1; i <= N; ++i) {
        int p; cin >> p;
        if (p == -1) { root = i; }
        else {
            children[p].push_back(i);
        }
    }

    // 오일러 투어(진입 시각만)로 평탄화
    build_euler(root);

    // 세그먼트 트리: 길이 N (오일러 번호 1..N)
    SegTree seg(N);

    while (M--) {
        int t; cin >> t;
        if (t == 1) {
            int u; long long w; cin >> u >> w;
            seg.range_add(in_t[u], out_t[u], w);     // 서브트리 전체에 +w
        } else {
            int u; cin >> u;
            cout << seg.point_query(in_t[u]) << '\n'; // 노드 u의 최종 값
        }
    }
    return 0;
}