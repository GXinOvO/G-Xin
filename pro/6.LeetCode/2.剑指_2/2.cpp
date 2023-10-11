/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 31 Jul 2022 03:19:20 PM CST
 ************************************************************************/

#include<iostream>
#include <string>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b);
};

string Solution::addBinary(string a, string b) {
    int i = a.size() - 1, j = b.size() - 1;
    int sum = 0;
    int base = 2;
    string ans = "";
    while(i > -1 || j > -1 || sum != 0) {
        if(i > -1) sum += a[i] - '0', i--;
        if(j > -1) sum += b[j] - '0', j--;
        ans = (char)('0' + sum % base) + ans;
        sum /= base;
    }
    return ans;
}

int main() {
    string a, b;
    Solution t1;
    cin >> a >> b;
    cout << t1.addBinary(a, b) << endl;
    return 0;
}
