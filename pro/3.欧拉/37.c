/*************************************************************************
	> File Name: 37.c
	> Author: 
	> Mail: 
	> Created Time: Sat 07 May 2022 11:48:29 PM CST
 ************************************************************************/

#include<stdio.h>
#include <math.h>
#define MAX_N 1000000

int prime[MAX_N + 5] = {0};
int is_prime[MAX_N + 5] = {0};
void init_prime() {
    for(int i = 2; i <= MAX_N; i++) {
        if(!is_prime[i]) prime[++prime[0]] = i;
        for(int j = 1; j <= prime[0]; j++) {
            if(prime[j] * i > MAX_N) break;
            is_prime[prime[j] * i] = 1;
            if(i % prime[j] == 0) break;
        }
    }
    return ;
}

int is_val(int n) {
    int x = n, y = n;
    int digit = floor(log10(n)) + 1;
    int power = pow(10, digit - 1);
    for(int i = 0, I = digit - 1; i < I; i++) {
        x %= power;
        power /= 10;
        y /= 10;
        if(is_prime[x] || x == 1 || is_prime[y] || y == 1) return 0;
    }
    return 1;
}

int main() {
    init_prime();
    int flag = 11, sum = 0;
    for(int i = 5; flag && i <= prime[0]; i++) {
        if(!is_val(prime[i])) continue;
        sum += prime[i];
        flag--;
        printf("%d\n", prime[i]);
    }
    printf("flag : %d, sum = %d\n", flag, sum);
    return 0;
}
