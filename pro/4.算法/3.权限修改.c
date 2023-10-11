/*************************************************************************
	> File Name: 3.权限修改.c
	> Author: 
	> Mail: 
	> Created Time: Wed 08 Jun 2022 10:06:02 PM CST
 ************************************************************************/

#include<stdio.h>
#include <string.h>

int main() {
    int sum = 0;
    char string[3];
    char modify[2];
    scanf("%s", string);
    for(int i = 0; i < strlen(string); i++) {
        if(string[i] == 'r') sum |= 4;
        if(string[i] == 'w') sum |= 2;
        if(string[i] == 'x') sum |= 1;
    }
    while(scanf("%s", modify) != EOF) {
        if(strcmp(modify, "+r")) sum |= 4;
        if(strcmp(modify, "+w")) sum |= 2;
        if(strcmp(modify, "+x")) sum |= 1;
        if(strcmp(modify, "-r")) sum &= 3;
        if(strcmp(modify, "-w")) sum &= 5;
        if(strcmp(modify, "-x")) sum &= 6;
    }
    printf("%d\n", sum);
    return 0;
}
