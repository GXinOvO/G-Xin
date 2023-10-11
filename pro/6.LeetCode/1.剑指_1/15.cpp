/*************************************************************************
	> File Name: 15.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 10 Sep 2022 10:09:03 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class Solution {
public:
    int hammingWeight(uint32_t n);
};

int Solution::hammingWeight(uint32_t n) {
    int res = 0;
    for(int i = 0; i < 32; ++i) {
        if(n & (1 << i)) res++;
    }
    return res;
}

int main() {
    uint32_t n;
    cin >> n;
    Solution t1;
    cout << t1.hammingWeight(n) << endl;
    return 0;
}
