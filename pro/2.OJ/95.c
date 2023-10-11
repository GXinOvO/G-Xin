/*************************************************************************
	> File Name: 95.c
	> Author: 
	> Mail: 
	> Created Time: Wed 04 May 2022 04:14:28 PM CST
 ************************************************************************/

#include<stdio.h>

int reverse(int n) {
    int temp = 0;
    while(n) {
        temp = temp * 10 + n % 10;
        n /= 10;
    }
    return temp;
}

int main() {
    int n;
    scanf("%d", &n);
    int temp = reverse(n);
    printf("%d\n", temp);
    return 0;
}
