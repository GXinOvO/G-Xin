/*************************************************************************
	> File Name: 120.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 May 2022 10:47:20 AM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int y, m, d;
    scanf("%d %d %d", &y, &m, &d);
    if(m == 1 || m == 3 || m ==5 || m == 7 || m == 8 || m == 10 || m == 12) {
        if(d >= 1 && d <= 31) printf("YES\n");
        else printf("NO\n");
    }else if(m == 4 || m == 6 || m == 9 || m == 11) {
        if(d >= 1 && d <= 30) printf("YES\n");
        else printf("NO\n");
    }else if(m == 2) {
        if(y % 100 == 0) {
            if(y % 400 == 0) {
                if(d >= 1 && d <= 29) printf("YES\n");
                else printf("NO\n");
            }else {
                if(d >= 1 && d <= 28) printf("YES\n");
                else printf("NO\n");
            }
        }else if(y % 4 == 0) {
            if (d >= 1 && d <= 29) printf("YES\n");
            else printf("NO\n");
        }else {
            if(d >= 1 && d <= 28) printf("YES\n");
            else printf("NO\n");
        }
    }else printf("NO\n");
    return 0;
}
