/*************************************************************************
	> File Name: 116.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 03:14:55 PM CST
 ************************************************************************/

#include<stdio.h>
#include <math.h>
void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
    return ;
}
void decide(int, int, int);

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if(b < a) swap(a, b);
    if(c < b) swap(b, c);
    if(a < b) swap(b, a);
    decide(a, b, c);
    return 0;
}

void decide(int a, int b, int c) {
    if((a + b) <= c) printf("illegal triangle\n");
    else {
        if((pow(a, 2) + pow(b, 2)) > pow(c, 2)) printf("acute triangle\n");
        else if((pow(a, 2) + pow(b, 2)) == pow(c, 2)) printf("right triangle\n");
        else if((pow(a, 2) + pow(b, 2)) < pow(c, 2)) printf("obtuse triangle\n");
    }
    return ;
}

