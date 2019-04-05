#include"Navigate.h"
#include"Hero.h"
#include"ActionCallback.h"
#include"APIVariable.h"
#include"GameView.h"
#include"Reload.h"
#include"ControlVariable.h"

unsigned WINAPI SolveMove(LPVOID lpParameter)
{
	GPHero* Object = (GPHero*)lpParameter;
	COORD LastDestination;//记录上一次移动的目的地
	while (!Object->dead)
	{
		WaitForSingleObject(Object->MoveMsg, INFINITE);//等待移动指令
		if (Object->uAttribute.Blood <= 0)
		{
			Object->dead = true;
			break;
		}
		if (!Object->FindPath())
		{
			ResetEvent(Object->MoveMsg);
			continue;
		}
		LastDestination = Object->Destination;
		while (1)
		{
			if (Object->isChasing)
			{
				int dx = (Object->KerLoc.X - Object->Destination.X) > 0 ? Object->KerLoc.X - Object->Destination.X : Object->Destination.X - Object->KerLoc.X;
				int dy = (Object->KerLoc.Y - Object->Destination.Y) > 0 ? Object->KerLoc.Y - Object->Destination.Y : Object->Destination.Y - Object->KerLoc.Y;
				
				if(Object->HeroToChase->camp == Enemy)
					if (dx <= Object->uAttribute.AttackRange&&dy <= Object->uAttribute.AttackRange)
						break;
			}
			else
				if (Object->KerLoc == Object->Destination)
					break;

			Object->NextLoc = Object->NextLoc->Next;//找到下一步的位置
			if (Active[Object->NextLoc->Loc.X][Object->NextLoc->Loc.Y].Occupied || LastDestination != Object->Destination)//若果这个位置被占据了或者目的地变更了
			{
				if (Object->FindPath())//开始找新路径  如果找到了
				{
					Object->NextLoc = Object->NextLoc->Next;
					if (LastDestination != Object->Destination)//如果是因为目的地变更 那么更新上一次的目的地为新的这个目的地
						LastDestination = Object->Destination;
				}
				else
					break;//找不到路径就停止
			}
			Object->Jmp(Object->NextLoc->Loc);//移动到那个位置
			Sleep(500/Object->uAttribute.Speed);
		}
		ResetEvent(Object->MoveMsg);
		SetEvent(Object->AttackMsg);
	}
	return 0;
}
unsigned WINAPI ToChase(LPVOID lpParameter)
{
	GPHero* Object = (GPHero*)lpParameter;
	while (!Object->dead)
	{
		WaitForSingleObject(Object->ChaseMsg, INFINITE);
		if (Object->dead)
			break;
		if (Object->HeroToChase)
		{
			Object->isChasing = true;
			Object->Destination = Object->HeroToChase->KerLoc;//设置追踪目标
			if (Object->Destination == CITADEL_POS)
				ResetEvent(Object->ChaseMsg);
			SetEvent(Object->MoveMsg);//设置移动信号
			ResetEvent(Object->AttackMsg);//取消攻击信号
		}
		Sleep(100);//每过一段时间更新一次跟随目的地
	}
	return 0;
}
unsigned WINAPI CitadelOperate(LPVOID lpParameter)
{
	Shop->number = 0;
	Shop->dead = false;
	Shop->KerLoc = { BATTLE_WIDTH / 2,BATTLE_HEIGHT / 2 };
	Shop->Destination = { BATTLE_WIDTH / 2,BATTLE_HEIGHT / 2 };
	Shop->HeroToChase = NULL;
	Shop->isChasing = false;
	Shop->AttackMsg = CreateEvent(NULL, true, false, NULL);
	Shop->BuffMsg = CreateEvent(NULL, true, false, NULL);//初始无buff
	Shop->DeBuffMsg = CreateEvent(NULL, true, false, NULL);//初始无buff
	Shop->SkillCDMsg = CreateEvent(NULL, true, false, NULL);//初始无技能处于CD
	Shop->MoveMsg = CreateEvent(NULL, true, false, NULL);//初始未移动
	Shop->ChaseMsg = CreateEvent(NULL, true, false, NULL);//初始未追逐
	CurSelectedHero = Shop;
	CurSelectedHero->GetSelected();
	while (Shop->uAttribute.Blood > 0)
		Sleep(100);
	return 0;
}