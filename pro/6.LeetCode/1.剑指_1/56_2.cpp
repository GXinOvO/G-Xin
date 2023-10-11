/*************************************************************************
	> File Name: 56_2.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 01 Aug 2022 02:21:52 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <cstring>
using namespace std;

class Solution {
public:
    int singLeNumber(vector<int>& nums);
};

int Solution::singLeNumber(vector<int>& nums) {
    int bits[32];
    int n = nums.size();
    memset(bits, 0, sizeof(bits));
    for(int i = 0; i < n; ++i) {
        int pos = 0;
        while(nums[i]) {
            bits[pos] += (nums[i] & 1);
            nums[i] >>= 1;
            pos++;
        }
    }
    int ans = 0;
    for(int i = 0; i < 32; ++i) {
        ans += (1 << i) * (bits[i] % 3);
    }
    return ans;
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
    cout << t1.singLeNumber(sum) << endl;

    return 0;
}
