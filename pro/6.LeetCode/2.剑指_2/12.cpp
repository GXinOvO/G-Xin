/*************************************************************************
	> File Name: 12.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 31 Jul 2022 01:50:33 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums);
};

int Solution::pivotIndex(vector<int>& nums) {
    int n = nums.size();
    int pre[n + 1];
    pre[0] = 0;
    for(int i = 0; i < n; ++i) {
        pre[i + 1] = pre[i] + nums[i];
    }
    for(int i = 0; i < n; ++i) {
        int sum1 = pre[i];
        int sum2 = pre[n] - nums[i] - pre[i];
        if(sum1 == sum2) return i;
    }
    return -1;
}

int main() {
    Solution t1;
    vector<int> sum;
    int x;
    while(1) {
        cin >> x;
        sum.push_back(x);
        if(cin.get() == '\n') break;
    }
    cout << t1.pivotIndex(sum) << endl;
    return 0;
}
