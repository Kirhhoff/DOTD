#include"SystemDependency.h"
#include"MouseFSM.h"
#include"Hero.h"
#include"Initialize.h"
#include"APIVariable.h"
#include"Load.h"
#include"GameView.h"
#include"Dameon.h"
#include"ControlVariable.h"

void InitialWindow()
{
	//获取各种句柄
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitle("DOTD");
	hwnd = FindWindow(NULL, "DOTD");
	hdc = GetDC(hwnd);
	hmendc = CreateCompatibleDC(hdc);
	hBlackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//hmutex[camp][number] = CreateMutex(NULL, false, NULL);
	 
	//初始化屏幕信息
	GetConsoleScreenBufferInfo(hOut, &csbi);//获得屏幕信息
	GetConsoleMode(hIn, &OldConsoleInputMode);//获取原始输入模式
	NewConsoleInputMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | OldConsoleInputMode;//在原基础上增添接受鼠标输入
	SetConsoleMode(hIn, NewConsoleInputMode);//设置新的输入模式
	


	SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, NULL);//设置全屏
	GetConsoleCursorInfo(hOut, &cursorInfo);//获得原始光标信息
	cursorInfo.bVisible = false;//仅将光标
	SetConsoleCursorInfo(hOut, &cursorInfo);//设为不可见

	//游戏尚未开始
	Go = false;

}
void InitialGame()
{
	//初始化小量
	isShowingHero = true;
	CurNum[Allies] = 0;
	CurNum[Enemy] = 0;
	money = 5000;
	CurHeroPrice = 0;
	srand(time(NULL));
	
	//初始化信号量 互斥量
	EndFighting = CreateEvent(NULL, true, true, NULL);
	PRINTF_MUTEX = CreateMutex(NULL, false, NULL);
	CHASE_MUTEX = CreateMutex(NULL, false, NULL);

	for (short y = 0; y < BATTLE_HEIGHT; y++)
		FillConsoleOutputAttribute(hOut, DefaultColor, BATTLE_WIDTH, { 0,y }, &num);

	//加载背景音乐
	LoadBackgroundSound();
	//加载装备库
	LoadEquipmentStock();
	//加载消耗品库
	LoadConsumableStock();
	//加载强化书库
	LoadEnhanceBookStock();
	//加载英雄库
	LoadHeroStock();
	//加载分界条
	LoadDivider();
	//加载大本营 商店 也是0号英雄
	LoadCitadel();
	//加载游戏轮数计时器
	LoadTimer();

	//初始化有限状态机
	FMState = new FormalState;
	SMState = new SkillingState;
	TMState = new TransportingState;
	PMState = new ShoppingState;
	CurMOPState = PMState;
	TmpMOPState = PMState;
}
void Operate()
{
	Sleep(500);
	while (ReadConsoleInput(hIn, Inputs, MAX_INPUT_RECORD, &InputOneTime))
	{
		for (int i = 0; i < InputOneTime; i++)
		{
			if (Inputs[i].EventType == MOUSE_EVENT)//鼠标事件
				HandleMouseInput(Inputs[i].Event.MouseEvent);
			else if (Inputs[i].EventType == KEY_EVENT)//键盘事件
				HandleKeyInput(Inputs[i].Event.KeyEvent);
		}
		if (Shop->uAttribute.Blood <= 0)
			exit(0);
		for (short y = BATTLE_HEIGHT / 2 - 1; y <= BATTLE_HEIGHT / 2 + 1; y++)//设置主城处的砖块信息
			FillConsoleOutputAttribute(hOut, CitadelColor, 3, { BATTLE_WIDTH / 2 - 1,y }, &num);//涂抹主城的颜色
	}
}