/*************************************************************************
	> File Name: 140.c
	> Author: 
	> Mail: 
	> Created Time: Sat 14 May 2022 05:44:25 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        for(int j = i; j < n; j++) printf(" ");
        for(int x = 1; x < 2 * i; x++) printf("%c", 'A' - 1 + i);
        printf("\n");
    }
    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= i; j++) printf(" ");
        for(int x = 2 * (n - i); x > 1; x--) printf("%c", 'A' + n - i - 1);
        printf("\n");
    }
    return 0;
}
