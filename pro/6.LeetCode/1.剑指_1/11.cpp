/*************************************************************************
	> File Name: 11.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 08 Sep 2022 09:59:24 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minArray(vector<int>& numbers);
};

int Solution::minArray(vector<int>& numbers) {
    int i = 0, j = numbers.size() - 1;
    while(i < j) {
        int m = (i + j) / 2;
        if(numbers[m] > numbers[j]) i = m + 1;
        else if(numbers[m] < numbers[j]) j = m;
        else {
            int x = i;
            for(int k = i + 1; k < j; ++k) {
                if(numbers[k] < numbers[x]) x = k;
            }
            return numbers[x];
        }
    }
    return numbers[i];
}

int main() {
    int x;
    vector<int> numbers;
    while(1) {
        cin >> x;
        numbers.push_back(x);
        if(cin.get() == '\n') break;
    }
    Solution t1;
    cout << t1.minArray(numbers) << endl;

    return 0;
}
