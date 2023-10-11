/*************************************************************************
	> File Name: 137.c
	> Author: 
	> Mail: 
	> Created Time: Fri 13 May 2022 08:43:11 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int n;
    char c = 'A';
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            printf("%c", c++);
        }
        printf("\n");
    }
    return 0;
}
