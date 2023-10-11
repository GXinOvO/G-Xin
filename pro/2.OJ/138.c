/*************************************************************************
	> File Name: 138.c
	> Author: 
	> Mail: 
	> Created Time: Fri 13 May 2022 08:55:23 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int ans = 2 * n;
    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= ans; j++) {
            printf("A");
        }
        ans -= 2;
        printf("\n");
    }
    return 0;
}
