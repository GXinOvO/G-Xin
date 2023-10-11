/*************************************************************************
	> File Name: 3_1.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 May 2022 11:27:46 AM CST
 ************************************************************************/

#include<iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findRepeatNumber(vector<int>& a);
};

int Solution::findRepeatNumber(vector<int>& a) {
    for(int i = 0; i < a.size(); i++) {
        while(a[i] != i) {
            if(a[i] == a[a[i]]) return a[i];
            swap(a[i], a[a[i]]);
        }
    }
    return 0;
}


int main() {
    Solution t1;
    vector<int> nums;
    int number;
    while(1) {
        cin >> number;
        nums.push_back(number);
        if(cin.get() == '\n') break;
    }
    cout << t1.findRepeatNumber(nums) << endl;
    return 0;
}
