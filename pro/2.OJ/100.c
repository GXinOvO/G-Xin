/*************************************************************************
	> File Name: 100.c
	> Author: 
	> Mail: 
	> Created Time: Tue 10 May 2022 03:27:17 PM CST
 ************************************************************************/

#include<stdio.h>

double get_money(int);

int main() {
    int n;
    scanf("%d", &n);
    printf("$%.2f\n", get_money(n));
    return 0;
}

double get_money(int n) {
    double number = 0;
    for(int i = 0; i < 6; i++) {
        number = (n + number) * (1 + 0.00417);
    }
    return number;
}
