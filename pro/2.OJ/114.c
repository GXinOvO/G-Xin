/*************************************************************************
	> File Name: 114.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 03:01:40 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    char x;
    scanf("%c", &x);
    if(x == 'h') printf("He\n");
    else if(x == 'l') printf("Li\n");
    else if(x == 'c') printf("Cao\n");
    else if(x == 'd') printf("Duan\n");
    else if(x == 'w') printf("Wang\n");
    else printf("Not Here\n");
    return 0;
}
