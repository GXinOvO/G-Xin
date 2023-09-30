/*************************************************************************
	> File Name: 98.c
	> Author: 
	> Mail: 
	> Created Time: Tue 10 May 2022 03:11:26 PM CST
 ************************************************************************/

#include<stdio.h>
#define PI 3.14

double floor_space(double);
double volume(double, double);


int main() {
    double r, h;
    scanf("%lf %lf", &r, &h);
    printf("%.2f\n%.2f\n", floor_space(r), volume(r, h));
    return 0;
}

double floor_space(double r) {
    return r * r * PI;
}

double volume(double r, double h) {
    return floor_space(r) * h;
}
