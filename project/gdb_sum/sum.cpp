/*************************************************************************
	> File Name: sum.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 01 Oct 2023 02:47:31 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main()
{
	int N = 100;
	int sum = 0;
	int i = 1;

	while (i <= N)
	{
		sum = sum + i;
		i = i + 1;
	}

	cout << "sum = " << sum << endl;
	cout << "The program is over." << endl;

	return 0;
}
