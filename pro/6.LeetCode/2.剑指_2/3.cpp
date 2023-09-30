/*************************************************************************
	> File Name: 3.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 01 Aug 2022 03:32:38 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> countBits(int n);
};

vector<int> Solution::countBits(int n) {
    vector<int> f;
    f.push_back(0);
    for(int i = 1; i <= n; ++i) {
        if(i & 1) f.push_back(f[i - 1] + 1);
        else f.push_back(f[i / 2]);//这里是因为相当于我们把这个值给 << 2，把偶数后面的0给去了，这样也好理解为什么他的1的个数和他缩小2倍的1的个数是一样的。
    }
    return f;
}

int main() {
    Solution t1;
    int x;
    cin >> x;
    vector<int> sum = t1.countBits(x);
    cout << "[";
    for(int i = 0; i < sum.size(); ++i) {
        if(i != 0) cout << ",";
        cout << sum[i];
    }
    cout << "]" << endl;
    return 0;
}
