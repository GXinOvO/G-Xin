/*************************************************************************
	> File Name: 149.c
	> Author: 
	> Mail: 
	> Created Time: Tue 17 May 2022 12:36:06 AM CST
 ************************************************************************/

#include<stdio.h>
#include <string.h>

int main() {
    char s[50 + 5];
    scanf("%[^\n]s", s);
    int len = strlen(s);
    int num = 0;
    for(int i = 0; i < len; i++) {
        if(s[i] == ' ') num = i;
    }
    printf("%d\n", len - 1 - num);
    return 0;
}
