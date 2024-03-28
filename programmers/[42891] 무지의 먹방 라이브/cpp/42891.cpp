#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define pii pair<int, int>

priority_queue<pii, vector<pii>, greater<>> pq;

bool cmp(const pii & a, const pii & b){
    return a.second < b.second;
}

int solution(vector<int> food_times, long long k) {
    long long total = 0;    
    // 전체 먹는 시간보다 k가 크거나 같다면 -1 return
    for(int i = 0; i < food_times.size(); i++){
        total += food_times[i];
    }
    if(total <= k) return -1;
    
    for(int i = 0; i < food_times.size(); i++){
        pq.push({food_times[i], i + 1});
    }
    
    total = 0;
    long long prev = 0;
    long long length = food_times.size();
    
    while(total + (length * (pq.top().first - prev)) <= k){
        int now = pq.top().first;
        pq.pop();
        total += (now - prev) * length;
        length -= 1;
        prev = now;
    }
    
    vector<pair<int, int>> rst;
    while(!pq.empty()){
        int food_time = pq.top().first;
        int num = pq.top().second;
        pq.pop();
        rst.push_back({food_time, num});
    }
    
    sort(rst.begin(), rst.end(), cmp);
    
    
    return rst[(k - total) % length].second;
}