/*************************************************************************
	> File Name: 45.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 May 2022 05:39:09 PM CST
 ************************************************************************/

#include<iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    string toStr(int a) {
        string ans = "";
        while(a) {
            ans = (char)(a % 10 + '0') + ans;
            a /= 10;
        }
        return ans == "" ? "0" : ans;
    }

    static int cmp(string a, string b) {
        return a + b < b + a;
    }

    string minNumber(vector<int>& nums) {
        vector<string> strs;
        for(int i = 0; i < nums.size(); i++) {
            strs.push_back(toStr(nums[i]));
        }
        sort(strs.begin(), strs.end(), cmp);
        string ans = "";
        for(int i = 0; i < nums.size(); i++) {
            ans += strs[i];
        }
        return ans;
    }
};


int main() {
    Solution t1;
    vector<int> nums;
    int number;
    while(1) {
        cin >> number;
        nums.push_back(number);
        if(cin.get() == '\n') break;
    }
    cout << t1.minNumber(nums) << endl;
    return 0;
}
