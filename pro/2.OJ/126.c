/*************************************************************************
	> File Name: 126.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 May 2022 12:07:30 PM CST
 ************************************************************************/

#include<stdio.h>
#define PI 3.14

double acreage(double, double);

int main() {
    double r1, r2;
    scanf("%lf %lf", &r1, &r2);
    printf("%.2f\n", acreage(r1, r2));
    return 0;
}

double acreage(double r1, double r2) {
    return PI * r1 * r1 - PI * r2 * r2;
}
