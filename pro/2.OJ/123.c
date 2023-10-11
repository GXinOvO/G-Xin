/*************************************************************************
	> File Name: 123.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 May 2022 11:22:47 AM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    if((a >= c && b <= d) || (c >= a && d <= b)) printf("YES\n");
    else printf("NO\n");
    return 0;
}
