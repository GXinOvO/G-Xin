/*************************************************************************
	> File Name: 101.c
	> Author: 
	> Mail: 
	> Created Time: Tue 10 May 2022 03:53:08 PM CST
 ************************************************************************/

#include<stdio.h>

int get_sum(int);

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", get_sum(n));
    return 0;
}

int get_sum(int n) {
    int ans = 0;
    while(n) {
        ans += n % 10;
        n /= 10;
    }
    return ans;
}
