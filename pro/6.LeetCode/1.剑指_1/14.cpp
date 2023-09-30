/*************************************************************************
	> File Name: 14.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 10 Sep 2022 09:53:49 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int cuttingRope(int n);
};

int Solution::cuttingRope(int n) {
    vector<int> dp(n + 1);
    for(int i = 2; i <= n; ++i) {
        int curMax = 0;
        for(int j = 1; j < i; ++j) {
            curMax = max(curMax, max(j * (i - j), j * dp[i - j]));
        }
        dp[i] = curMax;
    }
    return dp[n];
}

int main() {
    int n;
    cin >> n;
    Solution t1;
    cout << t1.cuttingRope(n) << endl;
    return 0;
}

