/*************************************************************************
	> File Name: 131.c
	> Author: 
	> Mail: 
	> Created Time: Fri 13 May 2022 07:39:38 PM CST
 ************************************************************************/

#include<stdio.h>

int x[100 + 5];

int main() {
    int n, max = 0, min = 10000;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
        if(max < x[i]) max = x[i];
        if(min > x[i]) min = x[i];
    }
    printf("%d\n", max - min);
    return 0;
}
