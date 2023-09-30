/*************************************************************************
	> File Name: 50.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 May 2022 11:04:45 PM CST
 ************************************************************************/

#include<iostream>
#include <map>
using namespace std;

class Solution {
public:
    char firstUniqChar(string s);  
};

char Solution::firstUniqChar(string s) {
    map<char, int> cnt;
    for(int i = 0; i < s.size(); i++) {
        cnt[s[i]] += 1;
    }
    for(int i = 0; i < s.size(); i++) {
        if(cnt[s[i]] == 1) return s[i];
    }
    return ' ';
}

int main() {
    Solution t1;
    string s;
    cin >> s;
    cout << t1.firstUniqChar(s) << endl;
    return 0;
}
