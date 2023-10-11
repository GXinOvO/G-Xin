/*************************************************************************
	> File Name: 125.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 May 2022 11:50:10 AM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int h, m, s, t;
    scanf("%d %d %d %d", &h, &m, &s, &t);
    double x = t / 86400.0 * 100;
    h += (t / 3600);
    m += (t % 3600 / 60);
    s += (t % 3600 % 60);
    if(s >= 60) {
        s -= 60;
        m += 1;
    }
    if(m >= 60) {
        m -= 60;
        h += 1;
    }
    if(h >= 24) h -=24;
    if(h > 12) printf("%d:%d:%dpm\n", h - 12, m, s);
    else if(h == 0) printf("12:%d:%dam\n", m , s);
    else if(h == 12) printf("12:%d:%dpm\n", m, s);
    else printf("%d:%d:%dam\n", h, m, s);
    printf("%.2f%%\n", x);
    return 0;
}
