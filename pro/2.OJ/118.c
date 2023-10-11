/*************************************************************************
	> File Name: 118.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 May 2022 03:47:56 PM CST
 ************************************************************************/

#include<stdio.h>

char* zodiac[] = {"rat", "ox", "tiger", "rabbit", "dragon", "snake", "horse", "sheep", "monkey", "rooster", "dog", "pig"};

int my_abs(int);

int main() {
    int year;
    scanf("%d", &year);
    int final_year = year - 1900;
    if(final_year >= 0) final_year = final_year % 12;
    else final_year = 12 - (my_abs(final_year) % 12);
    printf("%s\n", zodiac[final_year]);
    return 0;
}

int my_abs(int n) {
    int ans;
    if(n >= 0) ans = n;
    else ans = -n;
    return ans;
}
