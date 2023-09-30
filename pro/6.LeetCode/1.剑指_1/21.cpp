/*************************************************************************
	> File Name: 21_1.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 15 Aug 2022 01:07:53 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> exchange(vector<int>& nums);
};

vector<int> Solution::exchange(vector<int> &nums) {
    int i = 0, j = nums.size() - 1;
    while(i < j) {
        if((nums[i] & 1) == 1) {
            i++;
            continue;
        }
        if((nums[j] & 1) != 1) {
            j--;
            continue;
        }
        swap(nums[i++], nums[j--]);
    }
    return nums;
}

int main() {
    Solution t1;
    int x;
    vector<int> nums;
    while(1) {
        cin >> x;
        nums.push_back(x);
        if(cin.get() == '\n') break;
    }
    t1.exchange(nums);
    cout << "[";
    int n = nums.size();
    for(int i = 0; i < n; ++i) {
        if(i != 0) cout << " ";
        cout << nums[i];
    }
    cout << "]" << endl;
    return 0;
}
