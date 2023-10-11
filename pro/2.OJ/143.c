/*************************************************************************
	> File Name: 143.c
	> Author: 
	> Mail: 
	> Created Time: Mon 16 May 2022 04:59:32 PM CST
 ************************************************************************/

#include<stdio.h>

int is_prime(int);
int is_square(int);

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    int ans[10000] = {0};
    int cnt = 0;
    for(int i = a; i <= b; i++) {
        int l2 = i / 100;
        int r2 = i % 100;
        if(is_prime(l2) && is_square(r2) && i % 6 == 0) {
            ans[cnt++] = i;
        }
    }
    for(int i = 0; i < cnt; i++) {
        printf("%d", ans[i]);
        if(i != cnt - 1) printf(" ");
        else printf("\n");
    }
    printf("%d\n", cnt);
    return 0;
}

int is_prime(int x) {
    for(int i = 2; i < x; i++) {
        if(x % i == 0) return 0;
    }
    return 1;
}

int is_square(int x) {
    if(x == 1 || x == 4 || x == 9 || x == 16 || x == 25 || x == 36 || x == 49 || x == 64 || x == 81) return 1;
    return 0;
}
