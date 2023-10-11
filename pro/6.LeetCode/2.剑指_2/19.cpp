/*************************************************************************
	> File Name: 19.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 15 Aug 2022 08:58:46 PM CST
 ************************************************************************/

#include<iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool checkPalindrome(string& s, int low, int high);
    bool validPalindrome(string& s);
};

bool Solution::checkPalindrome(string& s, int low, int high) {
    for(int i = low, j = high; i < j; ++i, --j) {
        if(s[i] != s[j]) return false;
    }
    return true;
}

bool Solution::validPalindrome(string& s) {
    int low = 0, high = s.size() - 1;
    while(low < high) {
        int c1 = s[low], c2 = s[high];
        if(c1 == c2) {
            ++low;
            --high;
        }else {
            return checkPalindrome(s, low, high - 1) || checkPalindrome(s, low + 1, high);
        }
    }
    return true;
}

int main() {
    string s;
    Solution t1;
    cin >> s;
    if(t1.validPalindrome(s)) cout << "true" << endl;
    else cout << "false" << endl;
    return 0;
}
