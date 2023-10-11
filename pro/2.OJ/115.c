/*************************************************************************
	> File Name: 115.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 03:07:57 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int x, y;
    scanf("%d %d", &x, &y);
    int x1 = x % 10, x2 = x / 10;
    int y1 = y % 10, y2 = y / 10;
    if(x == y) printf("100\n");
    else if(x1 == y2 && x2 == y1 ) printf("20\n");
    else if(x1 == y1 || x1 == y2 || x2 == y1 || x2 == y2) printf("2\n");
    else printf("0\n");
    return 0;
}
