/*************************************************************************
	> File Name: 35.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 May 2022 12:13:41 AM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution{
public:
    int toMinutes(string s);
    int findMinDifference(vector<string>& timePoints);
};

int Solution::toMinutes(string s) {
    int h = 10 * (s[0] - '0') + (s[1] - '0');
    int m = 10 * (s[3] - '0') + (s[4] - '0');
    return h * 60 + m;
}

int Solution::findMinDifference(vector<string>& timePoints) {
    vector<int> times;
    for(int i = 0; i < timePoints.size(); i++) {
        times.push_back(toMinutes(timePoints[i]));
    }
    sort(times.begin(), times.end());
    int n = times.size();
    int ans = times[0] + 1440 - times[n - 1];
    for(int i = 1; i < n; i++) {
        ans = min(ans, times[i] - times[i - 1]);
    }
    return ans;
}

int main() {
    Solution t1;
    vector<string> timePoints;
    for(int i = 0; i < 3; i++) {
        string s;
        cin >> s;
        timePoints.push_back(s);
    }
    cout << t1.findMinDifference(timePoints) << endl;
    return 0;
}
