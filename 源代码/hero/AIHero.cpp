#include"Navigate.h"
#include"Hero.h"
#include"MouseFSM.h"
#include"AIFSM.h"
#include"ConsoleView.h"
#include"SoundCallback.h"
#include"StatusCallback.h"
#include"Reload.h"
#include"GameView.h"
#include"APIVariable.h"
#include"ControlVariable.h"
#include"UnitVariable.h"

void AIHero::SetRebrithLevel(int NewLevel)
{
	level = NewLevel;
	//以下设定技能等级
	if (level%MAX_MONSTER_SKILL_NUM == 0)
		for (int i = 0; i < MAX_MONSTER_SKILL_NUM; i++)
			Skills[i]->SetLevel(level / MAX_MONSTER_SKILL_NUM);
	else
	{
		for (int i = 0; i < MAX_MONSTER_SKILL_NUM - 1; i++)
			Skills[i]->SetLevel(level / (MAX_MONSTER_SKILL_NUM - 1));
		Skills[MAX_MONSTER_SKILL_NUM - 1]->SetLevel(level % (MAX_MONSTER_SKILL_NUM - 1));
	}
	uAttribute = BaseAttribute;
	special = BaseSpecial;
	for (int i = 1; i <= level; i++)
	{
		uAttribute += IncAttribute;
		special += IncSpecial;
	}
}
void AIHero::Rebrith()
{
	number = ++CurNum[Enemy];
	dead = false;
	SYSTEMTIME Tmp;
	GetLocalTime(&Tmp);
	srand(rand() + Tmp.wMilliseconds);//初始化随机数种子
	srand(rand()+ number * 67);
	//设定重生等级
	SetRebrithLevel(StockNumber == 1 ? Round : (StockNumber == 2 ? Round - SecondMonsterTurnUp : Round - ThirdMonsterTurnUp));
	//随机生成重生位置
	switch (rand()%4)//设定初始降生位置
	{
	case 0://上边
	{
		srand(rand() + number * 67);
		KerLoc = { rand() % (BATTLE_WIDTH - 2) + 1,0 };
	}
	break;
	case 1://下边
	{
		srand(rand() + number * 67);
		KerLoc = { rand() % (BATTLE_WIDTH - 2) + 1,BATTLE_HEIGHT - 2 };
	}
	break;
	case 2://左边
	{
		srand(rand() + number * 67);
		KerLoc = { 0,rand() % (BATTLE_HEIGHT - 2) + 1 };
	}
	break;
	case 3://右边
	{
		srand(rand() + number * 67);
		KerLoc = { BATTLE_WIDTH - 1,rand() % (BATTLE_HEIGHT - 2) + 1 };
	}
	break;
	default:
		break;
	}
	Destination = CITADEL_POS;
	//重新获得技能
	for (int i = 0; i<MAX_MONSTER_SKILL_NUM; i++)
		Skills[i] = &AISkillStock[(StockNumber - 1)*MAX_MONSTER_SKILL_NUM + i + 1];
	//失去现有装备
	for (int i = 0; i < MAX_THING_NUM; i++)
		if (Equipments[i])
			LoseEquipment(i);
	//设置辅导员的装备数
	int EquipmentNum;
	if (Round >= MAX_THING_NUM * RoundsToGetMoreOneEqipment)
		EquipmentNum = 6;
	else
		EquipmentNum = Round / RoundsToGetMoreOneEqipment;
	//重新获得装备
	for (int i = 1; i <= EquipmentNum; i++)
	{
		srand(rand() + 1);
		GetEquipment(&EquipmentStock[rand() % EQUIPMENT_STOCK]);
	}
	HeroToChase = NULL;
	//重新设置状态
	AIStillState* TmpStill = dynamic_cast<AIStillState*>(AIStates[AIStill]);
	TmpStill->JustAttacked = false;

	CurAIState = AIStates[AIStill];
	TmpAIState = AIStates[AIStill];
	ResetEvent(BuffMsg);//重置buff
	ResetEvent(DeBuffMsg);//重置debuff
	ResetEvent(SkillCDMsg);//重置CD信息
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, UpdateAIBuff, (void*)this, 0, NULL));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, UpdateAIDeBuff, (void*)this, 0, NULL));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, FlushAISkill, (void*)this, 0, NULL));
	ShowSelf();
}
void AIHero::Die()
{
	GenerateReward();
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, AIPlayDieSound, (void*)this, 0, NULL));
	SetEvent(BuffMsg);//确保退出线程
	SetEvent(DeBuffMsg);//确保退出线程
	SetEvent(SkillCDMsg);//确保退出线程
	//清除buff
	for (Buff* tmp = Head->Next; tmp != Rear; )
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
	//重置状态参量
	CurAIState = TmpAIState = NULL;

	for (int i = number; i <= CurNum[Enemy] - 1; i++)
		Monsters[i + 1]->number--;
	EraseSelf();
	if (--CurNum[Enemy] == 0)
	{
		SetEvent(EndFighting);
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayRoundSound, (void*)(int(RoundEnd)), 0, NULL));
	}
}
void AIHero::Operating()
{
	Rebrith();
	while(uAttribute.Blood>0&&!dead&&CurAIState)
	{
		CurAIState->Act();
		CurAIState = TmpAIState;
		if (uAttribute.Blood <= 0)
			dead = true;
	}
	Die();
}
void AIHero::GetSelected()
{
	TmpMOPState = FMState;
	Hero::GetSelected();
}
void AIHero::LoadReuseAttribute()
{
	Hero::LoadReuseAttribute();
	camp = Enemy;
	ExpercialNeeded = 0;
	for(int i=0;i<MAX_MONSTER_SKILL_NUM;i++)
		Skills[i]= &AISkillStock[(StockNumber - 1)*MAX_MONSTER_SKILL_NUM + i + 1];
}
void AIHero::GenerateReward()
{
	for (int i = 1; i <= CurNum[Allies]; i++)
		Heros[i]->GetExperical(uAttribute.RewardE);
	money += uAttribute.RewardM;
}
void AIHero::PrintFunction()
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);

	SetConsoleTextAttribute(hOut, SKILL_COLOR);
	for (int i = 0; i < MAX_THING_NUM; i++)
		if (Skills[i])
			Skills[i]->PrintName();

	SetConsoleTextAttribute(hOut, EQUIPMENT_COLOR);
	for (int i = 0; i < MAX_THING_NUM; i++)
		if (Equipments[i])
			Equipments[i]->PrintName(i);

	ReleaseMutex(PRINTF_MUTEX);

}
void AIHero::GetInjuried(Hero* Attacker)//受到伤害
{
	Hero::GetInjuried(Attacker);
	AIStillState* Tmp;
	if(uAttribute.Blood>0)
		if (Tmp = dynamic_cast<AIStillState*>(CurAIState))
			Tmp->JustAttacked = true;
}