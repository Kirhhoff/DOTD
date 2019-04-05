#include"Navigate.h"
#include"Hero.h"
#include"MouseFSM.h"
#include"APIVariable.h"
#include"ConsoleView.h"
#include"StatusCallback.h"
#include"SoundCallback.h"
#include"ActionCallback.h"
#include"Reload.h"
#include"GameView.h"
#include"Dameon.h"
#include"ControlVariable.h"
#include"UnitVariable.h"

void GPHero::Operating()
{
	Rebrith();
	while (!dead)
	{
		WaitForSingleObject(AttackMsg, INFINITE);//等待攻击指令
		int y1 = ((KerLoc.Y - uAttribute.AttackRange) >= 0) ? KerLoc.Y - uAttribute.AttackRange : 0;
		int y2 = ((KerLoc.Y + uAttribute.AttackRange)<BATTLE_HEIGHT) ? KerLoc.Y + uAttribute.AttackRange : BATTLE_HEIGHT - 1;
		short x1 = ((KerLoc.X - uAttribute.AttackRange) >= 0) ? KerLoc.X - uAttribute.AttackRange : 0;
		int x2 = ((KerLoc.X + uAttribute.AttackRange)<BATTLE_WIDTH) ? KerLoc.X + uAttribute.AttackRange : BATTLE_WIDTH - 1;
		int length = x2 - x1 + 1;
		for (short y = y1; y <= y2; y++)
			for (short x = x1; x <= x2; x++)
			{
				if (Active[x][y].Occupied&&KerLoc != COORD({x, y})&&Active[x][y].UnitCamp!=camp)//如果有人而且不是自己而且那人是对立阵营的
				{
					for (short y = y1; y <= y2; y++)
						FillConsoleOutputCharacterA(hOut, ATTACK_CHAR, length, { x1,y }, &num);
					Sleep(300);
					for (short y = y1; y <= y2; y++)
						FillConsoleOutputCharacterA(hOut, ' ', length, { x1,y }, &num);
					CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackSound, (void*)this, 0, NULL));
					Active[x][y].OccupyingUnit->GetInjuried(this);//进行一次伤害后退出
					WaitForSingleObject(CHASE_MUTEX, INFINITE);
					HeroToChase = Active[x][y].OccupyingUnit;//设置为追踪目标
					ReleaseMutex(CHASE_MUTEX);
					SetEvent(ChaseMsg);//发送追踪信号 模拟仇恨机制
					isChasing = true;
					break;
				}
			}
		if (uAttribute.Blood <= 0)
			dead = true;
		Sleep((double)1000/uAttribute.Frequence);
	}
	Die();
}
void GPHero::GetExperical(int experical)
{
	if (experical + CurExperical >= ExpercialNeeded)
	{
		experical = experical + CurExperical - ExpercialNeeded;
		LevelUp();
	}
	else
		CurExperical += experical;
}
void GPHero::LevelUp()
{
	level++;
	LeftSkillPoint++;
	uAttribute += IncAttribute;
	ExpercialNeeded += INC_HERO_EXPERICAL;
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(HeroLevelUp)), 0, NULL));
}
void GPHero::GetSelected()
{
	if (!number)
	{
		//商店随机生成商品
		for (int i = 0; i < MAX_THING_NUM; i++)
		{
			srand(rand() + 1);
			Consumables[i] = &ConsumableStock[rand() % CONSUMABLE_STOCK];
			srand(rand() + 1);
			Equipments[i] = &EquipmentStock[rand() % EQUIPMENT_STOCK];
			srand(rand() + 1);
			EnhanceBooks[i] = &EnhanceBookStock[rand() % ENHANCEBOOK_STOCK];
		}
		TmpMOPState = PMState;//切换到购物状态
	}
	else
		TmpMOPState = FMState;//否则切换到普通状态
	Hero::GetSelected();
}
void GPHero::PrintFunction()
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);
	SetConsoleTextAttribute(hOut, SKILL_COLOR);
	if (this == Shop)
	{
		for (int i = 0; i < MAX_THING_NUM; i++)
			EnhanceBooks[i]->PrintName(i, 0);
	}
	else
	{
		for (int i = 0; i < MAX_THING_NUM; i++)
			if (Skills[i])
				Skills[i]->PrintName();
	}
	SetConsoleTextAttribute(hOut, EQUIPMENT_COLOR);
	for (int i = 0; i < MAX_THING_NUM; i++)
		if (Equipments[i])
			Equipments[i]->PrintName(i);

	SetConsoleTextAttribute(hOut, CONSUMABLE_COLOR);
	for (int i = 0; i < MAX_THING_NUM; i++)
		if (Consumables[i])
			Consumables[i]->PrintName(i);
	ReleaseMutex(PRINTF_MUTEX);
}
void GPHero::GetInjuried(Hero* Attacker)
{
	Hero::GetInjuried(Attacker);
	if (this == Shop)
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(CitadelAttacked)), 0, NULL));
	if(Attacker)
		SetEvent(ChaseMsg);
}
void GPHero::UseConsumable(int index)//index范围是0-5
{
	if (Consumables[index])//如果这个格子里有消耗品
	{
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(TriggerConsumable)), 0, NULL));
		if (Consumables[index]->Range)
		{
			if (Consumables[index]->EffectionCamp() == Allies)
				for (int i = 1; i <= CurNum[Allies]; i++)
					Heros[i]->GetEffectedByBuff(Consumables[index]->Effect());//获得效果
			else
				for (int i = 1; i <= CurNum[Enemy]; i++)
					Monsters[i]->GetEffectedByBuff(Consumables[index]->Effect());//获得效果
		}
		else
			GetEffectedByBuff(Consumables[index]->Effect());//获得效果
		EraseThing(CONSUMABLE, index);//擦去图片
		LoseConsumable(index);//在成员中设置NULL
	}
}
void GPHero::MoveTo(COORD destination)
{
	if (number)
	{
		WaitForSingleObject(hmutex, INFINITE);
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMoveSound, (void*)this, 0, NULL));
		ResetEvent(AttackMsg);//设置取消取消攻击
		if (Active[destination.X][destination.Y].Occupied)
		{
			WaitForSingleObject(CHASE_MUTEX, INFINITE);
			HeroToChase = Active[destination.X][destination.Y].OccupyingUnit;
			ReleaseMutex(CHASE_MUTEX);
			SetEvent(ChaseMsg);//设置追逐信号
			isChasing = true;
		}
		else
		{
			ResetEvent(ChaseMsg);//设置不追逐的信号
			isChasing = false;
			Destination = destination;//设置目的地
		}
		SetEvent(MoveMsg);//设置移动信号
		ReleaseMutex(hmutex);
	}
}
void GPHero::TransportEquipTo(int HeroIndex)
{
	if (Heros[HeroIndex]->GetEquipment(Equipments[CurTransportedEquipIndex]))
		LoseEquipment(CurTransportedEquipIndex);
}
void GPHero::TransportConsumableTo(int HeroIndex)
{
	if (Heros[HeroIndex]->GetConsumable(Consumables[CurTransportedThingIndex]))
		LoseConsumable(CurTransportedThingIndex);
}
void GPHero::LoseConsumable(int index) { Consumables[index] = NULL; }
bool GPHero::GetConsumable(Consumable* NewConsumable)
{
	for (int i = 0; i<MAX_THING_NUM; i++)
		if (!Consumables[i])
		{
			Consumables[i] = NewConsumable;
			return true;
		}
	return false;
}
void GPHero::LoadReuseAttribute()
{
	Hero::LoadReuseAttribute();
	ExpercialNeeded = INC_HERO_EXPERICAL;
	camp = Allies;
	for (int i = 0; i < MAX_THING_NUM; i++)
	{
		Consumables[i] = NULL;
		EnhanceBooks[i] = NULL;
		Skills[i] = &GPSkillStock[(StockNumber-1)*MAX_HERO_SKILL_NUM+i + 1];
	}
	isChasing = false;
}
void GPHero::Rebrith()
{
	number = ++CurNum[Allies];
	dead = false;
	KerLoc = HERO_INITIAL_LOC;
	Destination = HERO_INITIAL_LOC;
	for (int i = 0; i < MAX_HERO_SKILL_NUM; i++)
		Skills[i] = &GPSkillStock[(StockNumber - 1)*MAX_HERO_SKILL_NUM + i + 1];
	uAttribute.Blood = uAttribute.MaxBlood;
	uAttribute.Energy = uAttribute.MaxEnergy;
	HeroToChase = NULL;
	isChasing = false;
	//重新创建资源量并设置状态
	ResetEvent(AttackMsg);//重置攻击状态
	ResetEvent(BuffMsg);//重置buff
	ResetEvent(DeBuffMsg);//重置debuff
	ResetEvent(SkillCDMsg);//重置CD信息
	ResetEvent(MoveMsg);//重置移动状态
	ResetEvent(ChaseMsg);//重置追逐状态
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, UpdateGPBuff, (void*)this, 0, NULL));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, UpdateGPDeBuff, (void*)this, 0, NULL));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, FlushGPSkill, (void*)this, 0, NULL));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, SolveMove, (void*)this, 0, NULL));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, ToChase, (void*)this, 0, NULL));
	CurSelectedHero = this;
	ShowSelf();
	GetSelected();
}
void GPHero::Die()
{
	if (!number)
		GameOver();
	else
	{
		GenerateReward();
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, GPPlayDieSound, (void*)this, 0, NULL));
		SetEvent(BuffMsg);//确保退出线程
		SetEvent(DeBuffMsg);//确保退出线程
		SetEvent(SkillCDMsg);//确保退出线程
		SetEvent(MoveMsg);//确保退出线程
		SetEvent(ChaseMsg);//确保退出线程
		//清除buff
		for (Buff* tmp = Head->Next; tmp != Rear;)
		{
			tmp->Prev->Next = tmp->Next;
			tmp->Next->Prev = tmp->Prev;
			Buff* ttmp = tmp->Next;
			delete tmp;
			tmp = ttmp;
		}
		//删除旧的路径
		Open->Clean();
		Close->Clean();
		for (; PathBegin;)
		{
			auto tmp = PathBegin;//暂存这个节点
			PathBegin = PathBegin->Next;//向后推一个节点
			if (tmp == PathBegin)//如果这个节点和它的后续节点相同 说明到了结尾 那么就可以退出了
				break;
			else 
				delete tmp;//删除这个节点
		}
		for (int i = number; i <= CurNum[Allies] - 1; i++)
		{
			Heros[i] = Heros[i + 1];
			Heros[i + 1]->number--;
		}
		EraseSelf();
		CurNum[Allies]--;
	}
}
void GPHero::GenerateReward()
{
	for(int i=1;i<=number-1;i++)
		Heros[i]->GetExperical(uAttribute.RewardE);
	for (int i = number + 1; i <= CurNum[Allies]; i++)
		Heros[i]->GetExperical(uAttribute.RewardE);
	money += uAttribute.RewardM;
}