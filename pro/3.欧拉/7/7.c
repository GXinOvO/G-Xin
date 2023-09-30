/*************************************************************************
	> File Name: 7.c
	> Author: 
	> Mail: 
	> Created Time: Thu 05 May 2022 12:00:25 AM CST
 ************************************************************************/

#include<stdio.h>

int is_prime(int n) {
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int i = 1, cnt = 0, num;
    scanf("%d", &num);
    while(cnt < num) {
        i++;
        if(!is_prime(i)) continue;
        cnt += 1;
    }
    printf("%d\n", i);
    return 0;
}
