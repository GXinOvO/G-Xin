/*************************************************************************
	> File Name: 142.c
	> Author: 
	> Mail: 
	> Created Time: Mon 16 May 2022 04:38:42 PM CST
 ************************************************************************/

#include<stdio.h>

int nums[100000 + 5];

int reverse(int);
int set_num(int);

int main() {
    int a, b;
    int ans = 0;
    scanf("%d %d", &a, &b);
    while(a <= b) {
        int get_num = reverse(a);
        if(get_num == a) nums[ans++] = a;
        a++;
    }
    for(int i = 0; i < ans; i++) {
        if(set_num(nums[i])) {
            printf("%d", nums[i]);
            if(i != ans - 1) printf(" ");
        }
    }
    printf("\n");
    return 0;
}

int reverse(int a) {
    int get_num = 0;
    while(a) {
        get_num = get_num * 10 + a % 10;
        a /= 10;
    }
    return get_num;
}

int set_num(int a) {
    for(int i = 2; i < a / 2; i++) {
        if(a % i == 0) return 0;
    }
    return 1;
}
