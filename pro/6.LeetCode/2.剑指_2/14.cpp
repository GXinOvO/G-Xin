/*************************************************************************
	> File Name: 14.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Aug 2022 01:07:52 PM CST
 ************************************************************************/

#include<iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2);
};

bool Solution::checkInclusion(string s1, string s2) {
    int n = s1.length(), m = s2.length();
    if(s1 > s2) return false;
    vector<int> cnt1(26), cnt2(26);
    for(int i = 0; i < n; ++i) {
        ++cnt1[s1[i] - 'a'];
        ++cnt2[s2[i] - 'a'];
    }
    if(cnt1 == cnt2) return true;
    for(int i = n; i < m; ++i) {
        ++cnt2[s2[i] - 'a'];
        --cnt2[s2[i - n] - 'a'];
        if(cnt2 == cnt1) return true;
    }
    return false;
}

int main() {
    string s1, s2;
    Solution t1;
    cin >> s1 >> s2;
    if(t1.checkInclusion(s1, s2)) cout << "True" << endl;
    else cout << "False" << endl;
    return 0;
}
