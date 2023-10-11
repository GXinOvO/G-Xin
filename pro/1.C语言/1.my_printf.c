/*************************************************************************
	> File Name: 1.my_printf.c
	> Author: 
	> Mail: 
	> Created Time: Fri 06 May 2022 04:09:24 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int my_printf(const char *frm, ...) {
    int cnt = 0;
    va_list arg;
    va_start(arg, frm);
    #define PUTC(a) putchar(a), ++cnt
    for(int i =0; frm[i]; i++) {
        switch (frm[i]) {
            case '%': {
                switch (frm[++i]) {
                    case '%': PUTC(frm[i]); break;
                    case 'd': {
                        int x = va_arg(arg, int);
                        if(x < 0) x = -x, PUTC('-');
                        int temp = 0, digit = 0;
                        do {
                            temp = temp * 10 + x % 10;
                            x /= 10;
                            digit += 1;
                        } while (x);
                        while (digit--) {
                            PUTC(temp % 10 + '0');
                            temp /= 10;
                        } 
                    } break;
                }

            } break;
            default: PUTC(frm[i]);
        }
    }
    return cnt;
}

int main() {
    printf("hello kaikeba!\n");
    int num = my_printf("hello kaikeba!\n");
    printf("%d\n", num);
    int a = 123;
    printf("int (a) = %d\n", a);
    my_printf("int (a) = %d\n", a);
    printf("int (b) = %d\n", 0);
    my_printf("int (b) = %d\n", 0);
    return 0;
}
