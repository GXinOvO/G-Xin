#pragma once
#include "graphics.h"   //easyx图形图库的头文件

// 表示落子位置
struct ChessPos
{
    int row;
    int col;
};

typedef enum 
{
    CHESS_WHITE = -1, // 白棋
    CHESS_BLACK = 1  // 黑棋
} chess_kind;

// 棋盘
class Chess
{
public:
    // 棋盘初始化: 加载棋盘的图片资源，初始化棋盘的相关数据
    void init();
    // 判断在指定坐标(x, y)位置，是否是有效点击
    bool clickBoard(int x, int y, ChessPos *pos);
    
    // 在棋盘的指定位置，落子
    void chessDown(ChessPos *pos, chess_kind kind);
    int getGradeSize(); // 获取棋盘大小

    // 获取指定位置是黑棋还是白棋、空白
    int getChessData(ChessPos *pos);
    int getChessData(int row, int col);

    bool checkOver();   // 检查棋局是否结束

private:
    IMAGE chessBlack;   // 黑棋
    IMAGE chessWhite;   // 白棋

    int gradeSize;  //棋盘大小
    
};