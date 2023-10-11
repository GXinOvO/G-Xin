/*************************************************************************
	> File Name: 10.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 30 Jul 2022 03:34:26 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k);
};

int Solution::subarraySum(vector<int>& nums, int k) {
    int pre[nums.size() + 1];
    pre[0] = 0;
    for(int i = 0; i < nums.size(); ++i) {
        pre[i + 1] = pre[i] + nums[i];
    } 
    map<int, int> cnt;
    int ans = 0;
    for(int i = 0; i <= nums.size(); ++i) {
        if(cnt.count(pre[i] - k)) {
            ans += cnt[pre[i] - k];
        }
        cnt[pre[i]]++;
    }
    return ans;
}

int main() {
    vector<int> sum;
    int x, k;
    while(1) {
        cin >> x;
        sum.push_back(x);
        if(cin.get() == '\n') break;
    }
    cin >> k;
    Solution t1;
    cout << t1.subarraySum(sum, k) << endl;
    return 0;
}
