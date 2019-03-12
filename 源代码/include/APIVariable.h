#ifndef APIVARIABLE_H
#define APIVARIABLE_H

#include<Windows.h>
#include"ConsoleView.h"
#include"Element.h"
extern CONSOLE_SCREEN_BUFFER_INFO csbi;//控制台缓冲区信息
extern HWND hwnd;//窗口句柄
extern HDC hdc;//设备环境句柄
extern HDC hmendc;//兼容的设备环境句柄
extern HBRUSH hBlackBrush;//黑色的画刷
extern HANDLE hOut, hIn;//标准输入输出句柄
extern CONSOLE_CURSOR_INFO cursorInfo;//光标信息
extern BRICK_INFO Active[BATTLE_WIDTH][BATTLE_HEIGHT];//记录各个格子的活动信息，取横向为x 纵向为y
extern INPUT_RECORD Inputs[MAX_INPUT_RECORD];//输入事件数组
extern bool LeftButtonPressed;//标记左键是否按下
extern int CurScreen;//当前活动的屏幕号
extern DWORD InputOneTime;//单次读取的输入事件数
extern DWORD OldConsoleInputMode, NewConsoleInputMode;//输入模式
extern COORD LastMousePos;//记录上次鼠标位置
extern DWORD num;//作为一个保留变量 不真正使用 只是为了填充实参

#endif