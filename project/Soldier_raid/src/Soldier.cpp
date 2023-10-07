/*************************************************************************
	> File Name: src/Soldier.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 02 Oct 2023 02:37:10 PM CST
 ************************************************************************/

#include<iostream>
#include "Soldier.h"
using namespace std;

Soldier::Soldier(std::string name)
{
	this->_name = name;
	this->_ptr_gun = nullptr;
}

void Soldier::addGun(Gun *ptr_gun)
{
	this->_ptr_gun = ptr_gun;
}

void Soldier::addBulletToGun(int num)
{
	this->_ptr_gun->addBullet(num);
}

bool Soldier::fire()
{
	return this->_ptr_gun->shoot();
}

Soldier::~Soldier()
{
	if (!this->_ptr_gun)
	{  
		delete this->_ptr_gun;
	}
}
