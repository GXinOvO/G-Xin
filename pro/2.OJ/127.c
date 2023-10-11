/*************************************************************************
	> File Name: 127.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 May 2022 12:14:39 PM CST
 ************************************************************************/

#include<stdio.h>
#include <math.h>

int main() {
    double x, n;
    scanf("%lf %lf", &x, &n);
    while(n) {
        x *= 1.06;
        n--;
    }
    printf("%g\n", floor(x));
    return 0;
}
