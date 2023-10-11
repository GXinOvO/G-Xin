/*************************************************************************
	> File Name: 136.c
	> Author: 
	> Mail: 
	> Created Time: Fri 13 May 2022 08:36:46 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int n;
    int ans = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        if(i % 7 == 0) {
            printf("%d\n", i);
            ans += 1;
        }
    }
    return 0;
}
