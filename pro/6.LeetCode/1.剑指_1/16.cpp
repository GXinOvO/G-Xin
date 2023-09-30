/*************************************************************************
	> File Name: 16.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 11 Sep 2022 02:37:36 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class Solution {
public:
    double myPow(double x, int n);
};

double Solution::myPow(double x, int n) {
    unsigned int s = (unsigned int)n;
    if(!n) return 1;
    if(n < 0) x = 1 / x, s = -s;
    double result = 1;
    while(s) {
        if(s & 1) result *= x;
        x *= x, s >>= 1;
    }
    return result;
}

int main() {
    double x;
    int n;
    cin >> x >> n;
    Solution t1;
    cout << t1.myPow(x, n) << endl;
    return 0;
}
