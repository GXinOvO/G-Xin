/*************************************************************************
	> File Name: 5_1.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 02 Aug 2022 02:06:47 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProduct(vector<string>& words);
};

int Solution::maxProduct(vector<string>& words) {
    int n = words.size();
    int states[n];
    memset(states, 0, sizeof(states));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < words[i].size(); ++j) {
            states[i] |= (1 << (words[i][j] - 'a'));
        }
    }
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            if((states[i] & states[j]) == 0) {
                int tmp = words[i].size() * words[j].size();
                ans = max(ans, tmp);
            }
        }
    }
    return ans;
}

int main() {
    Solution t1;
    vector<string> words;
    string x;
    while(1) {
        cin >> x;
        words.push_back(x);
        if(cin.get() == '\n') break;
    }
    cout << t1.maxProduct(words) << endl;

    return 0;
}
