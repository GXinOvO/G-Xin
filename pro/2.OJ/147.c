/*************************************************************************
	> File Name: 147.c
	> Author: 
	> Mail: 
	> Created Time: Tue 17 May 2022 12:15:05 AM CST
 ************************************************************************/

#include<stdio.h>
#include <string.h>

void get_printf(char*);

int main() {
    char data[10005] = {0};
    scanf("%s", data);
    get_printf(data);
    return 0;
}

void get_printf(char *s) {
    if((s[strlen(s) - 1] - '0') % 2 == 0) printf("YES\n");
    else printf("NO\n");
}
