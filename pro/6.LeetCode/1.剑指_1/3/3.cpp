/*************************************************************************
	> File Name: 3.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 May 2022 11:01:33 AM CST
 ************************************************************************/

#include<iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int findRepeatNumber(vector<int>& nums);
};

int Solution::findRepeatNumber(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    for(int i = 1; i < nums.size(); i++) {
        if(nums[i] == nums[i - 1]) return nums[i];
    }
    return -1;
}

int main() {
    vector<int> nums;
    Solution t1;
    int number;
    while(1) {
        cin >> number;
        nums.push_back(number);
        if(cin.get() == '\n') break;
    }
    cout << t1.findRepeatNumber(nums) << endl;
    return 0;
}
