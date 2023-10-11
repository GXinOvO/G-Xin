/*************************************************************************
	> File Name: 34.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 May 2022 10:29:22 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order);
};

bool Solution::isAlienSorted(vector<string>& words, string order) {
    map<char, char> m;
    for(int i = 0; i < order.size(); i++) {
        m[order[i]] = (char)(i + 'a');
    }
    vector<string> a, b;
    for(int i = 0; i < words.size(); i++) {
        string t = "";
        for(int j = 0; j < words[i].size(); j++) {
            t += m[words[i][j]];
        }
        a.push_back(t);
        b.push_back(t);
    }
    sort(a.begin(), a.end());
    for(int i = 0; i < words.size(); i++) {
        if(a[i] != b[i]) return false;
    }
    return true;
}

int main() {
    Solution t1;
    vector<string> words;
    string s;
    string order;
    while(1) {
        cin >> s;
        words.push_back(s);
        if(cin.get() == '\n') break;
    }
    cin >> order;
    if(t1.isAlienSorted(words, order)) cout << "true" << endl;
    else cout << "false" << endl;
    return 0;
}
