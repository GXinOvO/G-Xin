/*************************************************************************
	> File Name: swap.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 01 Oct 2023 11:30:35 AM CST
 ************************************************************************/

#include "swap.h"

void swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}
