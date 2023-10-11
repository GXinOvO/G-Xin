/*************************************************************************
	> File Name: 129.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 May 2022 03:03:33 PM CST
 ************************************************************************/

#include<stdio.h>

int min(int, int);

int main() {
    int n, x;
    int ans;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
        ans = min(ans, x);
    }
    printf("%d\n", ans);
    return 0;
}

int min(int a, int b) {
    if(a > b) return b;
    return a;
}
