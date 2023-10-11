/*************************************************************************
	> File Name: 16.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 11 Aug 2022 01:30:22 PM CST
 ************************************************************************/

#include<iostream>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

class Solution{
public:
    int lengthOfLongestSubstring(string s);
};

int Solution::lengthOfLongestSubstring(string s) {
    set<int> st;
    int j = 0, ans = 0;
    int n = s.size();
    for(int i = 0; i < n; ++i) {
        while(j < n && !st.count(s[j])) {
            st.insert(s[j]);
            ++j;
        }
        ans = max(ans, j - i);
        st.erase(s[i]);
    }
    return ans;
}

int main() {
    string s;
    Solution t1;
    cin >> s;
    cout << t1.lengthOfLongestSubstring(s) << endl;

    return 0;
}
