/*************************************************************************
	> File Name: src/Gun.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 02 Oct 2023 02:21:47 PM CST
 ************************************************************************/

#include "Gun.h"
#include <iostream>

using namespace std;

void Gun::addBullet(int bullet_num)
{
	this->_bullet_count = bullet_num;
}

bool Gun::shoot()
{
	if (this->_bullet_count <= 0)
	{
		std::cout << "Thers is no bullet" << std::endl;
		return false;
	}
	
	this->_bullet_count -= 1;
	std::cout << "shoot successfully!" << std::endl; 
	return true;
}

