/*************************************************************************
	> File Name: 110.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 02:34:17 PM CST
 ************************************************************************/

#include<stdio.h>

double get_money(double);

int main() {
    double weight;
    scanf("%lf", &weight);
    printf("%.2f\n", get_money(weight));
    return 0;
}

double get_money(double weight) {
    double money;
    if(weight <= 15) money = weight * 6;
    else money = 90 + (weight - 15) * 9;
    return money;
}
