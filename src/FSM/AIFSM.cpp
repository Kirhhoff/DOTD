#include"Navigate.h"
#include"Hero.h"
#include"AIFSM.h"
#include"APIVariable.h"
#include"GameView.h"
#include"Reload.h"
#include"ControlVariable.h"

void AIStillState::Act()
{
	if (JustAttacked)//如果刚被攻击 则转移到消极追逐状态 此外 这个状态是由外界设置的 同时 攻击者应该设置Object的HeroToChase项
	{
		Object->TmpAIState = Object->AIStates[AINegChase];//切换到消极追逐状态
		JustAttacked = false;
	}
	else//否则继续走向寝室 并检测范围内是否有敌人
	{
		int dx = CITADEL_POS.X - Object->KerLoc.X;
		int dy = CITADEL_POS.Y - Object->KerLoc.Y;
		if (dx < 0)
			dx = -dx;
		if (dy < 0)
			dy = -dy;
		if ((dx < Object->uAttribute.AttackRange + 1) && (dy < Object->uAttribute.AttackRange + 1))
			Object->Destination = Object->KerLoc;
		else
			Object->Destination = CITADEL_POS;//设置寝室为其目标位置
		Object->FindPath();
		Object->NextLoc = Object->NextLoc->Next;//找到下一步的位置
		if (Active[Object->NextLoc->Loc.X][Object->NextLoc->Loc.Y].Occupied || LastDestination != CITADEL_POS)//若果这个位置被占据了或者目的地不是寝室
		{
			if (Object->FindPath())//开始找新路径  如果找到了
			{
				Object->NextLoc = Object->NextLoc->Next;
				if (LastDestination != CITADEL_POS)//如果是因为目的地变更 那么更新上一次的目的地为新的这个目的地
					LastDestination = CITADEL_POS;
			}
			else
				Object->NextLoc->Loc=Object->KerLoc;//找不到路径就停止
		}
		Object->Jmp(Object->NextLoc->Loc);//移动到那个位置
		GetLocalTime(&BeginTest);//取得开始检测的时间
		if (Object->uAttribute.Frequence>Object->uAttribute.Speed)
			Sleep(1000 / Object->uAttribute.Frequence);//等待攻击间隔
		GetLocalTime(&EndTest);//取得结束检测时间
		for (; ;)//也就是说 对于攻速小到一定程度的敌人，追逐状态中无法攻击 即可起到风筝的作用
		{
			if (EndTest.wMinute>BeginTest.wMinute||((EndTest.wSecond - BeginTest.wSecond) * 1000 + EndTest.wMilliseconds - BeginTest.wMilliseconds) >= (TestTime/Object->uAttribute.Speed)||Object->uAttribute.Blood<=0)
				break;
			int y1 = ((Object->KerLoc.Y - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.Y - Object->uAttribute.AttackRange : 0;
			int y2 = ((Object->KerLoc.Y + Object->uAttribute.AttackRange)<BATTLE_HEIGHT) ? Object->KerLoc.Y + Object->uAttribute.AttackRange : BATTLE_HEIGHT - 1;
			short x1 = ((Object->KerLoc.X - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.X - Object->uAttribute.AttackRange : 0;
			int x2 = ((Object->KerLoc.X + Object->uAttribute.AttackRange)<BATTLE_WIDTH) ? Object->KerLoc.X + Object->uAttribute.AttackRange : BATTLE_WIDTH - 1;
			int length = x2 - x1 + 1;
			for (short y = y1; y <= y2; y++)
				for (short x = x1; x <= x2; x++)
					if (Active[x][y].Occupied&&Object->KerLoc != COORD({ x, y }) && Active[x][y].UnitCamp != Object->camp)//如果有人而且不是自己而且那人是对立阵营的
					{
						for (short y = y1; y <= y2; y++)
							FillConsoleOutputCharacterA(hOut, ATTACK_CHAR, length, { x1,y }, &num);
						Sleep(300);
						for (short y = y1; y <= y2; y++)
							FillConsoleOutputCharacterA(hOut, ' ', length, { x1,y }, &num);
						Active[x][y].OccupyingUnit->GetInjuried(Object);//进行一次伤害
						//if (Active[x][y].OccupyingUnit->uAttribute.Blood>0&&(typeid(*Active[x][y].OccupyingUnit)==typeid(GPHero)))
							//CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackedSound, (void*)Active[x][y].OccupyingUnit, 0, NULL));
						WaitForSingleObject(CHASE_MUTEX, INFINITE);
						Object->HeroToChase = Active[x][y].OccupyingUnit;//设置为追踪目标	
						ReleaseMutex(CHASE_MUTEX);
						Object->TmpAIState= Object->AIStates[AIPosChase];//转换到积极追逐状态
						goto BREAK;
					}
			GetLocalTime(&EndTest);//取得当前时间
		}
		BREAK:{}
	}
}
void AIPChaseState::Act()
{
	Object->Destination = Object->HeroToChase->KerLoc;
	int dx = (Object->KerLoc.X - Object->Destination.X) > 0 ? Object->KerLoc.X - Object->Destination.X : Object->Destination.X - Object->KerLoc.X;
	int dy = (Object->KerLoc.Y - Object->Destination.Y) > 0 ? Object->KerLoc.Y - Object->Destination.Y : Object->Destination.Y - Object->KerLoc.Y;
	while((dx<=Object->uAttribute.AttackRange+2)&&(dy <= Object->uAttribute.AttackRange + 2))//当没有超出攻击范围2的时候
	{
		if (!Object->FindPath())//不知道怎么追就不追了
			break;
		Object->NextLoc = Object->NextLoc->Next;
		Object->Jmp(Object->NextLoc->Loc);
		GetLocalTime(&BeginTest);//取得开始检测的时间
		if(Object->uAttribute.Frequence>Object->uAttribute.Speed)
			Sleep(1000 / Object->uAttribute.Frequence);//等待攻击间隔
		GetLocalTime(&EndTest);//取得结束检测时间
		for (; ;)
		{
			dx = (Object->KerLoc.X - Object->Destination.X) > 0 ? Object->KerLoc.X - Object->Destination.X : Object->Destination.X - Object->KerLoc.X;
			dy = (Object->KerLoc.Y - Object->Destination.Y) > 0 ? Object->KerLoc.Y - Object->Destination.Y : Object->Destination.Y - Object->KerLoc.Y;
			if (dx > Object->uAttribute.AttackRange || dy > Object->uAttribute.AttackRange)
				break;
			else
			{
				if (EndTest.wMinute > BeginTest.wMinute || ((EndTest.wSecond - BeginTest.wSecond) * 1000 + EndTest.wMilliseconds - BeginTest.wMilliseconds) >= (TestTime / Object->uAttribute.Speed) || Object->uAttribute.Blood <= 0)
					break;
				int y1 = ((Object->KerLoc.Y - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.Y - Object->uAttribute.AttackRange : 0;
				int y2 = ((Object->KerLoc.Y + Object->uAttribute.AttackRange) < BATTLE_HEIGHT) ? Object->KerLoc.Y + Object->uAttribute.AttackRange : BATTLE_HEIGHT - 1;
				short x1 = ((Object->KerLoc.X - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.X - Object->uAttribute.AttackRange : 0;
				int x2 = ((Object->KerLoc.X + Object->uAttribute.AttackRange) < BATTLE_WIDTH) ? Object->KerLoc.X + Object->uAttribute.AttackRange : BATTLE_WIDTH - 1;
				int length = x2 - x1 + 1;
				for (short y = y1; y <= y2; y++)
					FillConsoleOutputCharacterA(hOut, ATTACK_CHAR, length, { x1,y }, &num);
				Sleep(300);
				for (short y = y1; y <= y2; y++)
					FillConsoleOutputCharacterA(hOut, ' ', length, { x1,y }, &num);
				Object->HeroToChase->GetInjuried(Object);//受到伤害
				//if (Object->HeroToChase->uAttribute.Blood > 0 && (typeid(*Object->HeroToChase) == typeid(GPHero)))
					//CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackedSound, (void*)Object->HeroToChase, 0, NULL));

				/*for (short y = y1; y <= y2; y++)
					for (short x = x1; x <= x2; x++)
						if (Active[x][y].Occupied&&Object->KerLoc != COORD({ x, y }) && Active[x][y].UnitCamp != Object->camp)//如果有人而且不是自己而且那人是对立阵营的
						{
							for (short y = y1; y <= y2; y++)
								FillConsoleOutputCharacterA(hOut, ATTACK_CHAR, length, { x1,y }, &num);
							Sleep(300);
							for (short y = y1; y <= y2; y++)
								FillConsoleOutputCharacterA(hOut, ' ', length, { x1,y }, &num);
							Active[x][y].OccupyingUnit->GetInjuried(Object);//进行一次伤害
							CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackedSound, (void*)Active[x][y].OccupyingUnit, 0, NULL));
						}*/
				Sleep(1000 / Object->uAttribute.Frequence);//等待攻击间隔
				GetLocalTime(&EndTest);//取得当前时间
			}
			if (Object->uAttribute.Blood <= 0)
				break;
		}
		Object->Destination = Object->HeroToChase->KerLoc;//更新目标位置
		dx = (Object->KerLoc.X - Object->Destination.X) > 0 ? Object->KerLoc.X - Object->Destination.X : Object->Destination.X - Object->KerLoc.X;//计算X距离
		dy = (Object->KerLoc.Y - Object->Destination.Y) > 0 ? Object->KerLoc.Y - Object->Destination.Y : Object->Destination.Y - Object->KerLoc.Y;//计算Y距离
		if (Object->uAttribute.Blood <= 0)
			break;
	}
	Object->TmpAIState = Object->AIStates[AIStill];//追逐完毕后进入静止状态
}
void AINChaseState::Act()
{
	int dx, dy;
	for(;;)
	{
		GetLocalTime(&BeginTest);//获取开始检测时间
		Object->Destination = Object->HeroToChase->KerLoc;
		if (!Object->FindPath())//不知道怎么追就不追了
			break;
		Object->NextLoc = Object->NextLoc->Next;
		Object->Jmp(Object->NextLoc->Loc);
		if (Object->uAttribute.Frequence>Object->uAttribute.Speed)
			Sleep(1000 / Object->uAttribute.Frequence);//等待攻击间隔
		GetLocalTime(&EndTest);//获取停止检测时间
		dx = (Object->KerLoc.X - Object->Destination.X) > 0 ? Object->KerLoc.X - Object->Destination.X : Object->Destination.X - Object->KerLoc.X;//计算X相对距离
		dy = (Object->KerLoc.Y - Object->Destination.Y) > 0 ? Object->KerLoc.Y - Object->Destination.Y : Object->Destination.Y - Object->KerLoc.Y;//计算Y相对距离
		if (dx > Object->uAttribute.AttackRange || dy > Object->uAttribute.AttackRange)//没到攻击范围 继续追
		{
			while(1)//等待足够的时间
			{
				if (EndTest.wMinute>BeginTest.wMinute||(EndTest.wSecond - BeginTest.wSecond) * 1000 + EndTest.wMilliseconds - BeginTest.wMilliseconds >= (TestTime / Object->uAttribute.Speed) || Object->uAttribute.Blood <= 0)
					break;
				GetLocalTime(&EndTest);
			}
			if (Object->uAttribute.Blood <= 0)
				break;
			continue;
		}
		else
		{
			int y1 = ((Object->KerLoc.Y - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.Y - Object->uAttribute.AttackRange : 0;
			int y2 = ((Object->KerLoc.Y + Object->uAttribute.AttackRange)<BATTLE_HEIGHT) ? Object->KerLoc.Y + Object->uAttribute.AttackRange : BATTLE_HEIGHT - 1;
			short x1 = ((Object->KerLoc.X - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.X - Object->uAttribute.AttackRange : 0;
			int x2 = ((Object->KerLoc.X + Object->uAttribute.AttackRange)<BATTLE_WIDTH) ? Object->KerLoc.X + Object->uAttribute.AttackRange : BATTLE_WIDTH - 1;
			int length = x2 - x1 + 1;
			for (short y = y1; y <= y2; y++)
				FillConsoleOutputCharacterA(hOut, ATTACK_CHAR, length, { x1,y }, &num);
			Sleep(300);
			for (short y = y1; y <= y2; y++)
				FillConsoleOutputCharacterA(hOut, ' ', length, { x1,y }, &num);
			Object->HeroToChase->GetInjuried(Object);//受到伤害
			//if(Object->HeroToChase->uAttribute.Blood>0 && (typeid(*Object->HeroToChase) == typeid(GPHero)))
				//CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackedSound, (void*)Object->HeroToChase, 0, NULL));
			Object->TmpAIState = Object->AIStates[AIPosChase];//切换到积极追逐状态
			break;
		}
	}
}