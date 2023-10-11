/*************************************************************************
	> File Name: 124.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 May 2022 11:29:12 AM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    if((a >= 1 || b <= 50) && (c <= 25 || d >= 5)) printf("ok\n");
    else printf("pass\n");
    return 0;
}
