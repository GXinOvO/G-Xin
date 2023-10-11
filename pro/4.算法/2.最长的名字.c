/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: Wed 08 Jun 2022 09:16:52 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
int main() {
    int n, sum;
    char string[100];
    scanf("%d\n", &n);
    for(int i = 0; i < n; i++) {
        char num[100];
        int j = 0;
        char character;
        while(scanf("%c", &character) != EOF) {
            if(character != '\n') num[j++] = character;
            else {
                if(strlen(num) > strlen(string)) {
                    j = 0;
                    strcpy(string, num);
                }
                break;
            }
        }
    }
    printf("%s\n", string);
    return 0;
}
