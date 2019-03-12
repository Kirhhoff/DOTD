#include"ServiceCallback.h"
#include"Hero.h"
#include"SoundCallback.h"
#include"Dameon.h"
#include"ControlVariable.h"
#include"UnitVariable.h"

unsigned WINAPI LoadGPHero(LPVOID lpParameter)//加载一个新英雄的例程
{
	((GPHero*)lpParameter)->Operating();
	return 0;
}
unsigned WINAPI LoadAIHero(LPVOID lpParameter)//加载一个新英雄的例程
{
	((AIHero*)lpParameter)->Operating();
	return 0;
}
unsigned WINAPI Timer(LPVOID lpParameter)
{
	SYSTEMTIME LastSecond;
	SYSTEMTIME CurSecond;
	int MonsterNum;//该轮的辅导员数目
	int EquipmentNum;//辅导员的装备数
	while (1)
	{
		WaitForSingleObject(EndFighting, INFINITE);
		IntervalLastTime = INTERVAL;//重置间隔时间
		GetLocalTime(&LastSecond);
		for (; IntervalLastTime;)
		{
			ShowGameProgress();
			GetLocalTime(&CurSecond);
			while (CurSecond.wSecond == LastSecond.wSecond)
			{
				Sleep(200);
				GetLocalTime(&CurSecond);
			}
			LastSecond = CurSecond;
			IntervalLastTime--;
		}
		Round++;
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayRoundSound, (void*)(int(RoundStart)), 0, NULL));
		EraseGameProgress();

		//设置出现的辅导员个数
		if (Round >= ThirdMonsterTurnUp)
			MonsterNum = 3;
		else if (Round >= SecondMonsterTurnUp)
			MonsterNum = 2;
		else
			MonsterNum = 1;

		SYSTEMTIME Tmp;
		GetLocalTime(&Tmp);
		srand(rand() + Tmp.wMilliseconds);//初始化随机数种子

		//对各个辅导员进行初始化
		for (int i = 1; i <= MonsterNum; i++)
		{
			//初始化辅导员数组
			Monsters[i] = &MonsterStock[i];
			CloseHandle((HANDLE)_beginthreadex(NULL, 0, LoadAIHero, (void*)Monsters[i], 0, NULL));//开启辅导员线程
		}
		ResetEvent(EndFighting);
	}
}