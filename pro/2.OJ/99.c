/*************************************************************************
	> File Name: 99.c
	> Author: 
	> Mail: 
	> Created Time: Tue 10 May 2022 03:17:19 PM CST
 ************************************************************************/

#include<stdio.h>

double get_long(double, double);

int main() {
    double a, v;
    scanf("%lf %lf", &v, &a);
    printf("%.2f\n", get_long(a, v));
    return 0;
}

double get_long(double a, double v) {
    return (v * v) / (2 * a);
}
