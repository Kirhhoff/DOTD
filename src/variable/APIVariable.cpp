
#include"APIVariable.h"
#include"ConsoleView.h"
CONSOLE_SCREEN_BUFFER_INFO csbi;//控制台缓冲区信息
HWND hwnd;//窗口句柄
HDC hdc;//设备环境句柄
HDC hmendc;//兼容的设备环境句柄
HBRUSH hBlackBrush;//黑色的画刷
HANDLE hOut, hIn;//标准输入输出句柄
CONSOLE_CURSOR_INFO cursorInfo;//光标信息
BRICK_INFO Active[BATTLE_WIDTH][BATTLE_HEIGHT];//记录各个格子的活动信息，取横向为x 纵向为y
INPUT_RECORD Inputs[MAX_INPUT_RECORD];//输入事件数组
bool LeftButtonPressed;//标记左键是否按下
int CurScreen;//当前活动的屏幕号
DWORD InputOneTime;//单次读取的输入事件数
DWORD OldConsoleInputMode, NewConsoleInputMode;//输入模式
COORD LastMousePos;//记录上次鼠标位置
DWORD num;//作为一个保留变量 不真正使用 只是为了填充实参
