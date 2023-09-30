/*************************************************************************
	> File Name: 146.c
	> Author: 
	> Mail: 
	> Created Time: Mon 16 May 2022 11:09:57 PM CST
 ************************************************************************/

#include<stdio.h>
#include <string.h>

int main() {
    char data[55];
    scanf("%s", data);
    int len = strlen(data);
    for(int i = 0; i < len; i++) {
        if((data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' && data[i] <= 'Z')) {
            data[i]++;
            if(data[i] == 'z' + 1) data[i] = 'a';
            else if(data[i] == 'Z' + 1) data[i] = 'A';
        }
    }
    printf("%s\n", data);
    return 0;
}
