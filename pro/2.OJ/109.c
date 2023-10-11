/*************************************************************************
	> File Name: 109.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 02:31:32 PM CST
 ************************************************************************/

#include<stdio.h>

void decide(int);

int main() {
    int n;
    scanf("%d", &n);
    decide(n);
    return 0;
}

void decide(int n) {
    int ans;
    while(n) {
        ans = n % 10;
        if(ans % 2 == 0) {
            printf("YES\n");
            return ;
        }
        n /= 10;
    }
    printf("NO\n");
    return ;
}
