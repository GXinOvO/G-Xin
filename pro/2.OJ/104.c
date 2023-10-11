/*************************************************************************
	> File Name: 104.c
	> Author: 
	> Mail: 
	> Created Time: Tue 10 May 2022 04:18:58 PM CST
 ************************************************************************/

#include<stdio.h>

void dicide(int);

int main() {
    int a;
    scanf("%d", &a);
    dicide(a);
    return 0;
}

void dicide(int a) {
    int ans;
    while(a) {
        ans = a % 10;
        a /= 10;
        if(ans == 9) {
            printf("YES\n");
            return ;
        }
    }
    printf("NO\n");
    return ;
}
