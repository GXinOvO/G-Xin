/*************************************************************************
	> File Name: 245.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Jul 2022 03:29:43 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v;
    int n;
    int t;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> t;
        v.push_back(t);
    }
    sort(v.begin(), v.end());
    int pos = v[n / 2];
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += abs(v[i] - pos);
    }
    cout << sum << endl;
    return 0;
}
