/*************************************************************************
	> File Name: 73.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 02 Aug 2022 02:53:22 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int eatAll(vector<int>& piles, int k);
    int minEatingSpeed(vector<int>& piles, int h);
};

int Solution::eatAll(vector<int>& piles, int k) {
    int cnt = 0;
    for(int i = 0; i < piles.size(); ++i) {
        cnt += (piles[i] - 1) / k + 1;
    }
    return cnt;
}

int Solution::minEatingSpeed(vector<int>& piles, int h) {
    int l = 1, r = 1e9;
    while(l + 1 < r) {
        int mid = (l + r) / 2;
        if(eatAll(piles, mid) <= h) {
            r = mid;
        }else {
            l = mid;
        }
    }
    if(eatAll(piles, l) <= h) {
        return l;
    }
    return r;
}

int main() {
    Solution t1;
    vector<int> piles;
    int x, h;
    while(1) {
        cin >> x;
        piles.push_back(x);
        if(cin.get() == '\n') break;
    }
    cin >> h;
    cout << t1.minEatingSpeed(piles, h) << endl;
    return 0;
}
