/*************************************************************************
	> File Name: 1.NewTow.c
	> Author: 
	> Mail: 
	> Created Time: Sun 08 May 2022 09:18:33 PM CST
 ************************************************************************/

#include <stdio.h>
#include <math.h>
#include <inttypes.h>

double my_sqrt(double n) {
    #define EPSL 1e-7
    double x = n + 1;
    while(x * x - n > EPSL) {
        x -= (x / 2 - n / x * (1.0 / 2.0));
    }
    #undef EPSL
    return x;
}

int main() {
    double n;
    printf("%ld\n", INT64_MAX);
    while(~scanf("%lf", &n)) {
        printf("sqrt(%g) = %g\n", n, sqrt(n));
        printf("my_sqrt(%g) = %g\n", n, my_sqrt(n));
    }
    return 0;
}
