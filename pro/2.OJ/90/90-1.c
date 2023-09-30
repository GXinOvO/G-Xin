/*************************************************************************
	> File Name: 90-1.c
	> Author: 
	> Mail: 
	> Created Time: Wed 04 May 2022 11:49:41 AM CST
 ************************************************************************/

#include<stdio.h>

int reverse_num(int n) {
    int temp = 0;
    while(n) {
        temp = temp * 10 + n % 10;
        n /= 10;
    }
    return temp;
}

int get_digits(int n) {
    int cnt = 0;
    do {
        n /= 10;
        cnt += 1;
    } while(n);
    return cnt;
}

int main() {
    int n;
    scanf("%d", &n);
    int num = reverse_num(n);
    int digits = get_digits(n);
    while(digits--) {
        printf("%d\n", num % 10);
        num /= 10;
    }
    return 0;
}
