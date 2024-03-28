// 문자열 뒤집기
#include <iostream>
#define endl '\n'
using namespace std;

int main(){
    string str;
    cin >> str;

    int cnt0 = 0, cnt1 = 0;
    char prev = str[0];
    prev == '0' ? cnt1++ : cnt0++;

    for(char c : str){
        if(prev == c) continue;

        if(c == '0'){
            cnt1++;
            prev = '0';
        }

        else{
            cnt0++;
            prev = '1';
        }
    }

    cnt0 > cnt1 ? cout << cnt1 : cout << cnt0;
    return 0;
}