/*************************************************************************
	> File Name: 121.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 May 2022 10:59:58 AM CST
 ************************************************************************/

#include<stdio.h>

void decide(char, char);

int main() {
    char a, b;
    scanf("%c %c", &a, &b);
    decide(a, b);
    return 0;
}

void decide(char a, char b) {
    if(a == b) printf("TIE\n");
    else if((a == 'O' && b == 'Y') || (a == 'Y' && b == 'H') || (a == 'H' && b == 'O')) printf("MING\n");
    else printf("LI\n");
    return ;
}
