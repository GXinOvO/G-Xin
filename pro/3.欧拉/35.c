/*************************************************************************
	> File Name: 35.c
	> Author: 
	> Mail: 
	> Created Time: Sat 07 May 2022 10:31:03 PM CST
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

int get_digits(int n) {
    return floor(log10(n)) + 1;
}


int is_val(int n) {
    int digit = get_digits(n);
    int power = pow(10, digit - 1);
    for(int i = 0, I = digit - 1; i < I; i++) {
        n = n % power * 10 + n / power;
        if(is_prime[n]) return 0;
    }
    return 1;
}

int main() {
    init_prime();
    int cnt = 0;
    for(int i = 1; i <= prime[0]; i++) {
        cnt += is_val(prime[i]);
    }
    printf("%d\n", cnt);
    return 0;
}
