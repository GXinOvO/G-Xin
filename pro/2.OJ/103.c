/*************************************************************************
	> File Name: 103.c
	> Author: 
	> Mail: 
	> Created Time: Tue 10 May 2022 04:11:50 PM CST
 ************************************************************************/

#include<stdio.h>

void decide(int, int);

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    decide(a, b);
    return 0;
}

void decide(int a, int b) {
    if(a % b) {
        printf("NO\n");
        return ;
    }
    printf("YES\n");
    return ;
}


