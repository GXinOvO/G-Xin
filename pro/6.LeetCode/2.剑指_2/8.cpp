/*************************************************************************
	> File Name: 8.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 10 Aug 2022 01:30:23 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums);
};

int Solution::minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size();
    int j = 0, sum = 0, ans = n + 1;
    for(int i = 0; i < n; ++i) {
        while(j < n && sum < target) {
            sum += nums[j];
            ++j;
        }
        if(sum >= target) ans = min(ans, j - i);
        sum -= nums[i];
    }
    return ans == n + 1 ? 0 : ans;
}

int main() {
    vector<int> nums;
    Solution t1;
    int x, target;
    cin >> target;
    while(1) {
        cin >> x;
        nums.push_back(x);
        if(cin.get() == '\n') break;
    }
    cout << t1.minSubArrayLen(target, nums) << endl;
    return 0;
}
