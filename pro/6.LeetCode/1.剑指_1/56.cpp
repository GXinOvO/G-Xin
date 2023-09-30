/*************************************************************************
	> File Name: 56.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 01 Aug 2022 01:48:51 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums);
};

vector<int> Solution::singleNumbers(vector<int>& nums) {
    int xorSum = 0;
    for(int i = 0; i < nums.size(); ++i) {
        xorSum ^= nums[i];
    }
    int pos = 0;
    while(xorSum % 2 == 0) {
        xorSum /= 2;
        pos++;
    }
    int ans1 = 0, ans2 = 0;
    for(int i = 0; i < nums.size(); ++i) {
        if(nums[i] & (1 << pos)) {
            ans1 ^= nums[i];
        }else {
            ans2 ^= nums[i];
        }
    } 
    return vector<int> {ans1, ans2};
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
    vector<int> num = t1.singleNumbers(sum);
    cout << "[";
    for(int i = 0; i < 2; ++i) {
        if(i != 0) cout << ",";
        cout << num[i];
    }
    cout << "]" << endl;
    return 0;
}
