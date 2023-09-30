/*************************************************************************
	> File Name: 2.main.c
	> Author: 
	> Mail: 
	> Created Time: Sun 08 May 2022 04:24:11 PM CST
 ************************************************************************/

#include<stdio.h>

void funcA(int);
void funcB(int);

int main() {
    funcA(5);
    return 0;
}

void funcB(int n) {
    if(n == 0) return ;
    printf("funcB : %d\n", n);
    funcA(n - 1);
    return ;
}


void funcA(int n) {
    printf("funcA : %d\n", n);
    funcB(n - 1);
    return ;
}
