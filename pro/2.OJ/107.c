/*************************************************************************
	> File Name: 107.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 02:19:02 PM CST
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
    if(n % 7 == 0) {
        if(n % 2 != 0) {
            printf("YES\n");
            return ;
        }
    }
    printf("NO\n");
    return ;
    
}
