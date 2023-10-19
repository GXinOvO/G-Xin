/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 02 Oct 2023 11:15:18 PM CST
 ************************************************************************/

#include<iostream>
#include "ChessGame.h"
using namespace std;

int main()
{
	Man man;
	Chess chess;
	AI ai;
	
	ChessGame game(&man, &ai, &chess);

	game.play();

	return 0;

}

