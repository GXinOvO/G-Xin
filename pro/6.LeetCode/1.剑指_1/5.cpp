/*************************************************************************
	> File Name: 5.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 17 Aug 2022 01:06:04 PM CST
 ************************************************************************/

#include<iostream>
#include <string>
using namespace std;

class Solution {
public:
    string replaceSpace(string s);
};

string Solution::replaceSpace(string s) {
    string res;
    for(char c : s) {
        if(c == ' ') {
            res.push_back('%');
            res.push_back('2');
            res.push_back('0');
            continue;
        }
        res.push_back(c);
    }
    return res;
}

int main() {
    string s;
    getline(cin, s);
    Solution t1;
    cout << t1.replaceSpace(s) << endl;
    return 0;
}
