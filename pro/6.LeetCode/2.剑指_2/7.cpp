/*************************************************************************
	> File Name: 7.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 14 Aug 2022 01:55:54 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums);
};

vector<vector<int>> Solution::threeSum(vector<int>& nums) {
    if(nums.size() < 3) return {};
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    for(int i = 0; i < n - 2; ++i) {
        if(i != 0 && nums[i] == nums[i - 1]) continue;
        int target = -nums[i];
        int left = i + 1, right = n - 1;
        while(left < right) {
            int sum = nums[left] + nums[right];
            if(sum == target) {
                res.push_back({nums[i], nums[left], nums[right]});
                while(left < right && nums[left] == nums[++left]);
                while(left < right && nums[right] == nums[--right]);
            }else if(sum < target) {
                left++;
            }else right--;
        }
    }
    return res;
}

int main() {
    vector<int> nums;
    Solution t1;
    int x;
    while(1) {
        cin >> x;
        nums.push_back(x);
        if(cin.get() == '\n') break;
    }
    vector<vector<int>> res = t1.threeSum(nums);
    int n = res.size();
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 3; ++j) {
            if(j != 0) cout << " ";
            cout << res[i][j];
        }
        cout << endl;
    }
    return 0;
}

