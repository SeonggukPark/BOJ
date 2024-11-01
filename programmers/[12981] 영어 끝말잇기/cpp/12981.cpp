#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer = {0, 0};
    unordered_set<string> us;

    string prev = words[0];
    us.insert(words[0]);
    
    for(int i = 1; i < (int)words.size(); ++i){
        if(us.find(words[i]) != us.end() || prev[prev.size() - 1] != words[i][0]){
            // cout << prev[prev.size() - 1] << ' ' << words[i][0] << endl;
            // cout << i << endl;
            return {i % n + 1, i / n + 1};
        }
        
        us.insert(words[i]);
        prev = words[i];
    }
    
    
    return answer;
}