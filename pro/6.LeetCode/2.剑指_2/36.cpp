/*************************************************************************
	> File Name: 36.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 May 2022 08:26:36 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens);
    bool isNumber(string s);
    int calc(int a, int b, char c);
    int toInt(string str);
};

int Solution::evalRPN(vector<string>& tokens) {
    stack<int> s;
    int n = tokens.size();
    for(int i = 0; i < n; i++) {
        if(isNumber(tokens[i])) {
            s.push(toInt(tokens[i]));
        }else {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            s.push(calc(a, b, tokens[i][0]));
        }
    }
    return s.top();
}

bool Solution::isNumber(string s) {
    if(s.size() > 1) return true;
    return (s[0] >= '0' && s[0] <= '9');
}

int Solution::toInt(string str) {
    int ans = 0;
    for(int i = 0;i < str.size(); i++) {
        if(str[i] == '-') continue;
        ans = ans * 10 + (int)(str[i] - '0');
    }
    return str[0] == '-' ? -ans : ans;
}

int Solution::calc(int a, int b, char c) {
    if(c == '+') return a + b;
    if(c == '-') return a - b;
    if(c == '*') return a * b;
    return a / b;
}

int main() {
    Solution t1;
    vector<string> tokens;
    string s;
    while(1) {
        cin >> s;
        tokens.push_back(s);
        if(cin.get() == '\n') break;
    }
    cout << t1.evalRPN(tokens) << endl;
    return 0;
}
