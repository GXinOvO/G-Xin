/*************************************************************************
	> File Name: include/Soldier.h
	> Author: 
	> Mail: 
	> Created Time: Mon 02 Oct 2023 02:37:02 PM CST
 ************************************************************************/

#ifndef _SOLDIER_H
#pragma once
#include <string>
#include "Gun.h"

class Soldier
{
public:
	Soldier(std::string name);
	void addBulletToGun(int num);
	void addGun(Gun *ptr_gun);
	bool fire();
	~Soldier();
private:
	std::string _name;
	Gun *_ptr_gun;
};
#define _SOLDIER_H
#endif
