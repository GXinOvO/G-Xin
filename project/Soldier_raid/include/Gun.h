/*************************************************************************
	> File Name: include/Gun.h
	> Author: 
	> Mail: 
	> Created Time: Mon 02 Oct 2023 02:21:37 PM CST
 ************************************************************************/

#ifndef _GUN_H
#pragma once
#include <string>
class Gun
{
public:
	Gun(std::string type) 
	{
		this->_type = type;
		this->_bullet_count = 0;
	}

	void addBullet(int bullet_num);
	bool shoot();
	~Gun(){}

private:
	int _bullet_count;
	std::string _type;
};
#define _GUN_H
#endif
