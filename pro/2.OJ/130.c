/*************************************************************************
	> File Name: 130.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 May 2022 03:10:28 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    double m, n;
    double ans = 0;
    scanf("%lf %lf", &m, &n);
    while(n) {
        ans = (m + ans) * 1.00417;
        n--;
    }
    printf("$%.2f\n", ans);
    return 0;
}
