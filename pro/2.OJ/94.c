/*************************************************************************
	> File Name: 94.c
	> Author: 
	> Mail: 
	> Created Time: Wed 04 May 2022 04:09:49 PM CST
 ************************************************************************/

#include<stdio.h>

double BMI(double w, double h) {
    return w / (h * h);
}

int main() {
    double w, h;
    scanf("%lf %lf", &w, &h);
    printf("%.2f\n", BMI(w, h));
    return 0;
}
