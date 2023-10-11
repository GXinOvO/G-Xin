/*************************************************************************
	> File Name: 74.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 31 Jul 2022 02:54:20 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    struct Node {
        int val, type;
    };
    static int cmp(Node a, Node b) {
        if(a.val == b.val) {
            return a.type > b.type;
        }
        return a.val < b.val;
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals);
};

vector<vector<int>> Solution::merge(vector<vector<int>>& intervals) {
    vector<Node> a;
    for(int i = 0; i< intervals.size(); ++i) {
        a.push_back(Node{intervals[i][0], 1});
        a.push_back(Node{intervals[i][1], -1});
    }
    sort(a.begin(), a.end(), cmp);
    int pre = 0, l, r;
    vector<vector<int>> ans;
    for(int i = 0; i < a.size(); ++i) {
        if(a[i].type == 1) {
            pre++;
            if(pre == 1) l = a[i].val;
        }else {
            pre--;
            if(pre == 0) {
                r = a[i].val;
                ans.push_back(vector<int>{l, r});
            }
        }
    }
    return ans;
}

int main() {
    return 0;
}
