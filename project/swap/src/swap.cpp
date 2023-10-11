#include "swap.h"

void swap::run()
{
    int temp;
    temp = this->_a;
    _a = _b;
    _b = temp;
}

void swap::printInfo()
{
    std::cout << "a = " << this->_a << std::endl;
    std::cout << "b = " << this->_b << std::endl;
}