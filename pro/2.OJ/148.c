/*************************************************************************
	> File Name: 148.c
	> Author: 
	> Mail: 
	> Created Time: Tue 17 May 2022 12:27:45 AM CST
 ************************************************************************/

#include<stdio.h>
#include <string.h>

int main() {
    char x[50 + 5];
    scanf("%s", x);
    int len = strlen(x);
    for(int i = 0; i < len; i++) {
        printf("%c", x[len - 1- i]);
    }
    printf("\n");
    return 0;
}
