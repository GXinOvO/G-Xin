/*************************************************************************
	> File Name: 108.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 02:25:05 PM CST
 ************************************************************************/

#include<stdio.h>

double triangle(double, double);
double oblong(double, double);

int main() {
    char size;
    double m, n;
    scanf("%c %lf %lf", &size, &m, &n);
    if(size == 't') printf("%.2f\n", triangle(m, n));
    else printf("%.2f\n", oblong(m, n));
    return 0;
}

double triangle(double m, double n) {
    return m * n / 2.0;
}

double oblong(double m, double n) {
    return m * n;
}
