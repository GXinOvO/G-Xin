/*************************************************************************
	> File Name: 139.c
	> Author: 
	> Mail: 
	> Created Time: Sat 14 May 2022 05:02:55 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        for(int j = i; j < n; j++) printf(" ");
        for(int x = 1; x <= 2 * i; x++) printf("%c", 'A');
        printf("\n");
    }
    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= i; j++) printf(" ");
        for(int x = 2 * (n - i); x >= 1; x--) printf("%c", 'A');
        printf("\n");
    }
    return 0;
}
