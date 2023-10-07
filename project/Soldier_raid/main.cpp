/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 02 Oct 2023 03:06:40 PM CST
 ************************************************************************/

#include "Gun.h"
#include "Soldier.h"

void test()
{
	Soldier sanduo("xusanduo");
	sanduo.addGun(new Gun("AK47"));
	sanduo.addBulletToGun(20); 
	sanduo.fire();
}

int main()
{
	test();
	return 0;
}