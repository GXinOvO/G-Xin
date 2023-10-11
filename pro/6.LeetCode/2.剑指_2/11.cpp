/*************************************************************************
	> File Name: 11.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 30 Jul 2022 04:49:45 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums);
};

int Solution::findMaxLength(vector<int>& nums) {
    int p[2][nums.size() + 1];
    p[0][0] = p[0][1] = 0;
    for(int i = 0; i < nums.size(); ++i) {
        if(nums[i] == 0) {
            p[0][i + 1] = p[0][i] + 1;
            p[1][i + 1] = p[1][i];
        }else {
            p[0][i + 1] = p[0][i];
            p[1][i + 1] = p[1][i] + 1;
        }
    }
    int ans = 0;
    map<int, int> cnt;
    for(int i = 0; i <= nums.size(); ++i) {
        int t = p[0][i] - p[1][i];
        if(cnt.count(t)) {
            ans = max(ans, i - cnt[t]);
        }else {
            cnt[t] = i;
        }
    } 
    return ans;
}

int main() {
    int x;
    vector<int> sum;
    while(1) {
        cin >> x;
        sum.push_back(x);
        if(cin.get() == '\n') break;
    }
    Solution t1;
    cout << t1.findMaxLength(sum) << endl;
    return 0;
}
