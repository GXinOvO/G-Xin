/*************************************************************************
	> File Name: 117.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 03:43:00 PM CST
 ************************************************************************/

#include<stdio.h>

void decide(int);
int reverse(int);

int main() {
    int a;
    scanf("%d", &a);
    decide(a);
    return 0;
}

int reverse(int a) {
    int ans = 0;
    while(a) {
        ans = ans * 10 + a % 10;
        a /= 10;
    }
    return ans;
}

void decide(int a) {
    int ans = reverse(a);
    if(ans == a) printf("YES\n");
    else printf("NO\n");
    return ;
}
