/*************************************************************************
	> File Name: 105.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 11:36:13 AM CST
 ************************************************************************/

#include<stdio.h>

void decide(double);

int main() {
    double num;
    scanf("%lf", &num);
    decide(num);
    return 0;
}

void decide(double num) {
    if(num > 55.4) {
        printf("YES\n");
        return ;
    }
    printf("NO\n");
    return ;
}

