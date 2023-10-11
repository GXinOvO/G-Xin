/**********************************************************************
	> File Name: 9.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 12 Aug 2022 01:57:18 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int numSubarrayProductLessThank(vector<int>& nums, int k);
};

int Solution::numSubarrayProductLessThank(vector<int>& nums, int k) {
    if(k <= 1) return 0;
    int j = 0, ans = 0, sum = 1;
    for(int i = 0; i < nums.size(); ++i) {
        while(j < nums.size() && sum < k) {
            sum *= nums[j];
            ++j;
        }
        if(sum >= k) ans += j - i - 1;
        else ans += j - i;
        sum /= nums[i];
    }
    return ans;
}

int main() {
    vector<int> nums;
    int x, k;
    Solution t1;
    while(x) {
        cin >> x;
        nums.push_back(x);
        if(cin.get() == '\n') break;
    }
    cin >> k;
    cout << t1.numSubarrayProductLessThank(nums, k) << endl;

    return 0;
}

