/*************************************************************************
	> File Name: 106.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 11:38:50 AM CST
 ************************************************************************/

#include<stdio.h>

double decide(double);

int main() {
    double n;
    scanf("%lf", &n);
    printf("%g\n", decide(n));
    return 0;
}

double decide(double n) {
    double ans;
    if(n < 0) ans = -n;
    else ans = n;
    return ans;
}
