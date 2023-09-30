/*************************************************************************
	> File Name: 122.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 May 2022 11:05:04 AM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int t, h, m, s;
    scanf("%d", &t);
    h = t / 3600;
    m = t % 3600 / 60;
    s = t % 3600 % 60;
    if(h == 12) {
        printf("%02d:%02d:%02d midnoon\n", h, m, s);
    }else if(h < 12) {
        printf("%02d:%02d:%02d am\n", h, m, s);
    }else printf("%02d:%02d:%02d pm\n", h - 12, m, s);
    return 0;
}
