/*************************************************************************
	> File Name: 61.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 17 May 2022 04:30:48 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isStraight(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int i = 0, cnt = 0;
        while(nums[i] == 0) i++, cnt++;
        i++;
        while(i < nums.size()) {
            if(nums[i] == nums[i - 1]) return false;
            if(nums[i] - nums[i - 1] > 1) {
                cnt -= nums[i] - nums[i - 1] - 1;
                if(cnt < 0) return false;
            }
            i++;
        }
        return true;
    }
};

int main() {
    vector<int> nums;
    Solution t1;
    for(int i = 0; i < 5; i++) {
        int x;
        cin >> x;
        nums.push_back(x);
    }
    for(int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    if(t1.isStraight(nums) == true) cout << "true" << endl;
    else cout << "false" << endl;
    return 0;
}
