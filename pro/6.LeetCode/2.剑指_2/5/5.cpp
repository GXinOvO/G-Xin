/*************************************************************************
	> File Name: 5.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 02 Aug 2022 01:43:46 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    int maxProduct(vector<string>& words);
};

int Solution::maxProduct(vector<string>& words) {
    int n = words.size();
    map<char, int> cnts[n];
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < words[i].size(); ++j) {
            cnts[i][words[i][j]]++;
        }
    }
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            bool hasSame = false;
            for(char c = 'a'; c <= 'z'; ++c) {
                if(cnts[i].count(c) && cnts[j].count(c)) {
                    hasSame = true;
                    break;
                }
            }
            if(!hasSame) {
                int sum = words[i].size() * words[j].size();
                ans = max(ans, sum);
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
