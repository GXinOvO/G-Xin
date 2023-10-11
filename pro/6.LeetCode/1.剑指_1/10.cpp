/*************************************************************************
	> File Name: 10.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 08 Sep 2022 08:19:18 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class Solution {
public:
    int numWays(int n);
};

int Solution::numWays(int n) {
    if(n == 0) return 1;
    if(n <= 2) return n;
    int a = 1, b = 2, c;
    for(int i = 3; i <= n; ++i) {
        c = (a + b) % 1000000007;
        a = b; 
        b = c;
    }
    return c;
}

int main() {
    int n;
    cin >> n;
    Solution t1;
    cout << t1.numWays(n) << endl;
    return 0;
}
