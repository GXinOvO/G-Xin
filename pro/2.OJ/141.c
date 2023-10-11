/*************************************************************************
	> File Name: 141.c
	> Author: 
	> Mail: 
	> Created Time: Sat 14 May 2022 05:59:42 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < i; j++) printf(" ");
        for(int x1 = i; x1 <= n; x1++) printf("%c", 'A' + x1);
        for(int x2 = n - 1; x2 >= i; x2--) printf("%c", 'A' + x2);
        printf("\n");
    }
    for(int i = n - 1; i >= 0; i--) {
        for(int j = i; j > 0; j--) printf(" ");
        for(int x1 = i; x1 <= n; x1++) printf("%c", 'A' + x1);
        for(int x2 = n - 1; x2 >= i; x2--) printf("%c", 'A' + x2);
        printf("\n");
    }
    return 0;
}
