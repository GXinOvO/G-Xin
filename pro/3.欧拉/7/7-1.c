/*************************************************************************
	> File Name: 7-1.c
	> Author: 
	> Mail: 
	> Created Time: Thu 05 May 2022 05:32:29 PM CST
 ************************************************************************/

#include<stdio.h>
#define MAX_N 100000

int prime[MAX_N + 5] = {0};
void init_prime() {
    for(int i = 2; i <= MAX_N; i++) {
        if(prime[i]) continue;
        prime[++prime[0]] = i;
        for(int j = i, I = MAX_N / i; j <= I; j++) {
            prime[j * i] = 1;
        }
    }
    return ;
}

int main() {
    init_prime();
    printf("cnt = %d\n", prime[0]);
    return 0;
}
