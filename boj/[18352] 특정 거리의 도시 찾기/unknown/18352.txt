#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
constexpr size_t MAX_CITY = 300001;
int N, M, K, X;
vector<int> v[MAX_CITY];
bool visited[MAX_CITY];

void init(){
    for(auto i : v){
        i.clear();
    }

    memset(visited, false, sizeof(visited));
}

void input(){
    int a, b;
    cin >> N >> M >> K >> X;

    for(int i = 0; i < M; i++){
        cin >> a >> b;
        v[a].push_back(b);
    }
}

void run(){
    queue<pair<int, int>> q;
    priority_queue<int, vector<int>, greater<>> rst;
    
    visited[X] = true;
    q.emplace(X, 0);

    while(!q.empty()){
        auto top = q.front();
        q.pop();

        if(top.second == K){
            rst.push(top.first);
            continue;
        }

        // 방문 안한 노드 추가
        for(auto i : v[top.first]){
            if(!visited[i]){
                visited[i] = true;
                q.emplace(i, top.second + 1);
            }
        }
    }

    if(rst.empty()){
        cout << -1;
        return;
    }

    while(!rst.empty()){
        cout << rst.top() << endl;
        rst.pop();
    }
}

int main() {
    init();
    input();
    run();
    return 0;
}