/*************************************************************************
	> File Name: 134.c
	> Author: 
	> Mail: 
	> Created Time: Fri 13 May 2022 08:05:52 PM CST
 ************************************************************************/

#include<stdio.h>

int ans[100];

int main() {
    int a, b;
    int num = 0;
    scanf("%d %d", &a, &b);
    while(a <= b) {
        if(a % 11 == 0) ans[num++] = a;
        a += 1;
    }
    for(int i = 0; i < num; i++) {
        printf("%d", ans[i]);
        if(i != num - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
