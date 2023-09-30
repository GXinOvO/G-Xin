/*************************************************************************
	> File Name: 3.LOG.c
	> Author: 
	> Mail: 
	> Created Time: Thu 19 May 2022 08:28:55 PM CST
 ************************************************************************/

#include<stdio.h>

#define log(frm, args...) { \
    printf("[%s : %s : %d] ", __FILE__, __func__, __LINE__); \
    printf(frm, ##args); \
    printf("\n"); \
}

int main() {
    int a = 123, b = 345;
    printf("[%s : %s : %d] %d\n", __FILE__, __func__, __LINE__, a);
    log("%d", a);
    printf("hello world\n");
    log("hello world\n");
    return 0;
}
