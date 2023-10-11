/*************************************************************************
	> File Name: 128.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 May 2022 02:59:38 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int n;
    double ans = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        ans += x;
    }
    printf("%.2f\n", ans / n);
    return 0;
}
