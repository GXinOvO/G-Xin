/*************************************************************************
	> File Name: 145.c
	> Author: 
	> Mail: 
	> Created Time: Mon 16 May 2022 11:04:44 PM CST
 ************************************************************************/

#include<stdio.h>
#include <string.h>

int main() {
    int N;
    scanf("%d", &N);
    char a[25][105];
    int maxL = 0, maxIndex = 0;
    for(int i = 0; i < N; i++) {
        scanf("%s", a[i]);
        if(strlen(a[i]) > maxL) {
            maxL = strlen(a[i]);
            maxIndex = i;
        }
    }
    printf("%s\n", a[maxIndex]);
    return 0;
}
