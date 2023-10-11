/*************************************************************************
	> File Name: 33.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 29 Jul 2022 03:51:46 PM CST
 ************************************************************************/

#include<iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Solution{
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs);
};

vector<vector<string>> Solution::groupAnagrams(vector<string>& strs) {
    map<string, int> index;
    vector<vector<string>> ans;
    int n = strs.size();
    for(int i = 0; i < n; ++i) {
        string tmp = strs[i];
        sort(tmp.begin(), tmp.end());
        if(index.count(tmp) == 0) {
            ans.push_back(vector<string>{strs[i]});
            index[tmp] = ans.size() - 1;
        }else {
            ans[index[tmp]].push_back(strs[i]);
        }
    }
    return ans;
}

int main() {
    vector<string> strs;
    Solution t1;
    string str;
    while(1) {
        cin >> str;
        strs.push_back(str);
        if(cin.get() == '\n') break;
    }
    vector<vector<string>> type_strs = t1.groupAnagrams(strs);
    int n = type_strs.size();
    for(int i = 0; i < n; ++i) {
        int m = type_strs[i].size();
        for(int j = 0; j < m; ++j) {
            cout << type_strs[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
