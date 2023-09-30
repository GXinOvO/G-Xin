/*************************************************************************
	> File Name: 132.c
	> Author: 
	> Mail: 
	> Created Time: Fri 13 May 2022 07:54:37 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int n, x;
    long long ans = 1;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
        ans *= x;
    }
    printf("%lld\n", ans);
    return 0;
}
