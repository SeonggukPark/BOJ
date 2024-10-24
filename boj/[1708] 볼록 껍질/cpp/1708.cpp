#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define x first
#define y second
#define pii pair<int, int>
#define pll pair<ll, ll>

using namespace std;
vector<pll> vec;
pll min_pos;

ll ccw(pll a, pll b, pll c){
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cmp_pos(pll & a, pll & b){
    if(a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

bool cmp_ccw(const pll &a, const pll &b) {
    ll cross = ccw(min_pos, a, b);
    if (cross == 0) {
        ll dist_a = (a.x - min_pos.x) * (a.x - min_pos.x) + (a.y - min_pos.y) * (a.y - min_pos.y);
        ll dist_b = (b.x - min_pos.x) * (b.x - min_pos.x) + (b.y - min_pos.y) * (b.y - min_pos.y);
        return dist_a < dist_b;
    }
    return cross > 0;
}

void solve() {
    int N; cin >> N;
    vec.resize(N);
    vector<pll> hull;

    for (int i = 0; i < N; ++i) {
        cin >> vec[i].x >> vec[i].y;
    }

    sort(vec.begin(), vec.end(), cmp_pos);
    min_pos = vec[0];

    sort(vec.begin()+1, vec.end(), cmp_ccw);

    hull.push_back(min_pos);
    hull.push_back(vec[1]);

    for(int i = 2; i < N; ++i){
        while(hull.size() >= 2){
            pll p2 = hull.back(); hull.pop_back();
            pll p1 = hull.back();

            if(ccw(p1, p2, vec[i]) > 0){
                hull.push_back(p2);
                break;
            }
        }

        hull.push_back(vec[i]);
    }

    cout << hull.size(); // 컨벡스 헐의 점 개수 출력
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}