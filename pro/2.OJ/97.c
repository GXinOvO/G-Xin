/*************************************************************************
	> File Name: 97.c
	> Author: 
	> Mail: 
	> Created Time: Tue 10 May 2022 03:00:21 PM CST
 ************************************************************************/

#include<stdio.h>

long long get_sum(long long);

int main() {
    long long n;
    scanf("%lld", &n);
    printf("%lld\n", get_sum(n));
    return 0;
}

long long get_sum(long long n) {
    return n * (1 + n) / 2;
}

