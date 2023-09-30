/*************************************************************************
	> File Name: 102.c
	> Author: 
	> Mail: 
	> Created Time: Tue 10 May 2022 03:57:14 PM CST
 ************************************************************************/

#include<stdio.h>

double get_number(double, double, double, double);

int main() {
    double a, b, c, t;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &t);
    printf("%.2f\n", get_number(a, b, c, t));
    return 0;
}

double get_number(double a, double b, double c, double t) {
    double sum = (1 - (t / a + t / b)) / (1 / a + 1 / b - 1 / c) + t;
    return sum;
}
