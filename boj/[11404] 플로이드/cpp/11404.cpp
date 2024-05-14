#include <iostream>
#include <vector>
#include <cstring>
#define INF 987654321
using namespace std;
constexpr size_t MAX_N = 101;
int n, m;
int graph[MAX_N][MAX_N];

void traverse(){
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << graph[i][j] << ' ';
        }
        if(i < n) cout << endl;
    }
}

void init(){
    for (int i = 0; i < MAX_N; ++i) {
        for (int j = 0; j < MAX_N; ++j) {
            graph[i][j] = INF;
            if(i == j) graph[i][j] = 0;
        }
    }
}

void input(){
    int a, b, c;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c;
        graph[a][b] = min(graph[a][b], c);
    }
}

void run(){
    // floyd warshall
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n ; ++k) {
                graph[j][k] = min(graph[j][k], graph[j][i] + graph[i][k]);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if(graph[i][j] >= INF) graph[i][j] = 0;
        }
    }

    traverse();

}

int main(){
    init();
    input();
    run();

    return 0;
}