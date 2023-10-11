/*************************************************************************
	> File Name: 111.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 02:43:34 PM CST
 ************************************************************************/

#include<stdio.h>

double get_money(int);

int main() {
    int journey;
    scanf("%d", &journey);
    printf("%g\n", get_money(journey));
    return 0;
}

double get_money(int journey) {
    double money;
    if(journey <= 3) money = 14;
    else money = 14 + (journey - 3) * 2.3;
    return money;
}
