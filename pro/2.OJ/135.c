/*************************************************************************
	> File Name: 135.c
	> Author: 
	> Mail: 
	> Created Time: Fri 13 May 2022 08:22:30 PM CST
 ************************************************************************/

#include<stdio.h>

void advance(int *y, int *m, int *d) {
    int days[12] = {
        31, ((*y % 4 == 0 && *y % 100 != 0) || *y % 400 == 0) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    *d += 1;
    if(*d > days[*m - 1]) {
        *d = 1;
        *m += 1;
    }
    if(*m > 12) {
        *m = 1;
        *y += 1;
    }
}

int main() {
    int x;
    int y, m, d;
    scanf("%d %d %d %d", &x, &y, &m, &d);
    for(int i = 0; i < x; i++) {
        advance(&y, &m, &d);
    }
    printf("%d %d %d\n", y, m, d);
    return 0;
}
