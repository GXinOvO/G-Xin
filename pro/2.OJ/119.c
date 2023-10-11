/*************************************************************************
	> File Name: 119.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 04:08:21 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int y, m, d;
    scanf("%d %d %d", &y, &m, &d);
    int y1 = y, m1 = m, d1 = d - 1;
    int y2 = y, m2 = m, d2 = d + 1;
    int days_in_month[12] = {31, ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(d1 == 0) {
        m1--;
    }
    if(m1 == 0) {
        y1--;
        m1 = 12;
    }
    if(d1 == 0) {
        d1 = days_in_month[m1 - 1];
    }
    if(d2 > days_in_month[m2 - 1]) {
        ++m2;
        d2 = 1;
    }
    if(m2 > 12) {
        ++y2;
        m2 = 1;
    }
    printf("%d %d %d\n", y1, m1, d1);
    printf("%d %d %d\n", y2, m2, d2);
    return 0;
}
