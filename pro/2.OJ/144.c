/*************************************************************************
	> File Name: 144.c
	> Author: 
	> Mail: 
	> Created Time: Mon 16 May 2022 08:41:18 PM CST
 ************************************************************************/

#include<stdio.h>
#include <string.h>

int main() {
    char s[100 + 5];
    int ans = 0;
    scanf("%s", s);
    int len = strlen(s);
    for(int i = 0; i < len; i++) {
        if(s[i] == 'A') ans++;
    }
    printf("%d\n", ans);
    return 0;
}
