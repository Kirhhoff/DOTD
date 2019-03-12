#include"StatusCallback.h"
#include"Hero.h"
#include"Reload.h"
#include"APIVariable.h"
#include"GameView.h"
#include"ControlVariable.h"

unsigned WINAPI UpdateGPBuff(LPVOID lpParameter)
{
	GPHero* Object = (GPHero*)lpParameter;
	int curbuff = 0;//记录本次更新的buff数 以便发现没有buff时及时阻塞该线程
	while (!Object->dead)
	{
		WaitForSingleObject(Object->BuffMsg, INFINITE);//等待有buff
		if (Object->dead)
			break;
		WaitForSingleObject(Object->hmutex, INFINITE);//加锁
		curbuff = 0;
		for (Buff* tmp = Object->Head->Next; tmp != Object->Rear; )
		{
			curbuff++;
			if (tmp->TimeLeft <= 0)
			{
				Object->special -= tmp->special;//减去它提供的那部分特殊效果
				Object->uAttribute -= tmp->Effection;//减去暂时的护甲 等等加成
				Buff* ttmp = tmp->Next;
				tmp->Prev->Next = tmp->Next;//更新节点
				tmp->Next->Prev = tmp->Prev;//以删去当前节点
				delete tmp;
				tmp = ttmp;
			}
			else 
			{
				tmp->TimeLeft--;//剩余时间-1
				Object->GetSlowRecovery(tmp->Effection);//更新缓慢的回血回蓝
				tmp = tmp->Next;
			}
		}
		if (!curbuff)//如果遍历完这次发现没有buff了  那么设置事件阻塞函数
			ResetEvent(Object->BuffMsg);
		ReleaseMutex(Object->hmutex);//解锁
		Sleep(1000);
	}
	return 0;
}
unsigned WINAPI UpdateGPDeBuff(LPVOID lpParameter)
{
	GPHero* Object = (GPHero*)lpParameter;
	int curbuff = 0;//记录本次更新的buff数 以便发现没有buff时及时阻塞该线程
	while (!Object->dead)
	{
		WaitForSingleObject(Object->DeBuffMsg, INFINITE);//等待有buff
		if (Object->dead)
			break;
		WaitForSingleObject(Object->hmutex, INFINITE);//加锁
		curbuff = 0;
		for (Buff* tmp = Object->Head->Next; tmp != Object->Rear; )
		{
			curbuff++;
			if (tmp->TimeLeft <= 0)
			{
				Object->special += tmp->special;//恢复它损失的那部分特殊效果
				Object->uAttribute += tmp->Effection;//恢复暂时的护甲 等等加成
				tmp->Prev->Next = tmp->Next;//更新节点
				tmp->Next->Prev = tmp->Prev;//以删去当前节点
				Buff* ttmp = tmp->Next;
				delete tmp;
				tmp = ttmp;
			}
			else
			{
				tmp->TimeLeft--;//剩余时间-1
				Object->GetSlowInjury(tmp->Effection);//更新缓慢的回血回蓝
				tmp = tmp->Next;
			}
		}
		if (!curbuff)//如果遍历完这次发现没有buff了  那么设置事件阻塞函数
			ResetEvent(Object->DeBuffMsg);
		ReleaseMutex(Object->hmutex);//解锁
		Sleep(1000);
	}
	return 0;
}
unsigned WINAPI UpdateAIBuff(LPVOID lpParameter)
{
	AIHero* Object = (AIHero*)lpParameter;
	int curbuff = 0;//记录本次更新的buff数 以便发现没有buff时及时阻塞该线程
	while (!Object->dead)
	{
		WaitForSingleObject(Object->BuffMsg, INFINITE);//等待有buff
		if (Object->dead)
			break;
		WaitForSingleObject(Object->hmutex, INFINITE);//加锁
		curbuff = 0;
		for (Buff* tmp = Object->Head->Next; tmp != Object->Rear; )
		{
			curbuff++;
			if (tmp->TimeLeft <= 0)
			{
				Object->special -= tmp->special;//减去它提供的那部分特殊效果
				Object->uAttribute -= tmp->Effection;//减去暂时的护甲 等等加成
				tmp->Prev->Next = tmp->Next;//更新节点
				tmp->Next->Prev = tmp->Prev;//以删去当前节点
				Buff* ttmp = tmp->Next;
				delete tmp;
				tmp = ttmp;
			}
			else
			{
				tmp->TimeLeft--;//剩余时间-1
				Object->GetSlowRecovery(tmp->Effection);//更新缓慢的回血回蓝
				tmp = tmp->Next;
			}
		}
		if (!curbuff)//如果遍历完这次发现没有buff了  那么设置事件阻塞函数
			ResetEvent(Object->BuffMsg);
		ReleaseMutex(Object->hmutex);//解锁
		Sleep(1000);
	}
	return 0;
}
unsigned WINAPI UpdateAIDeBuff(LPVOID lpParameter)
{
	AIHero* Object = (AIHero*)lpParameter;
	int curbuff = 0;//记录本次更新的buff数 以便发现没有buff时及时阻塞该线程
	while (!Object->dead)
	{
		WaitForSingleObject(Object->DeBuffMsg, INFINITE);//等待有buff
		if (Object->dead)
			break;
		WaitForSingleObject(Object->hmutex, INFINITE);//加锁
		curbuff = 0;
		for (Buff* tmp = Object->Head->Next; tmp != Object->Rear; )
		{
			curbuff++;
			if (tmp->TimeLeft <= 0)
			{
				Object->special += tmp->special;//恢复它损失的那部分特殊效果
				Object->uAttribute += tmp->Effection;//恢复暂时的护甲 等等加成
				tmp->Prev->Next = tmp->Next;//更新节点
				tmp->Next->Prev = tmp->Prev;//以删去当前节点
				Buff* ttmp = tmp->Next;
				delete tmp;
				tmp = ttmp;
			}
			else
			{
				tmp->TimeLeft--;//剩余时间-1
				Object->GetSlowInjury(tmp->Effection);//更新缓慢的回血回蓝
				tmp = tmp->Next;
			}
		}
		if (!curbuff)//如果遍历完这次发现没有buff了  那么设置事件阻塞函数
			ResetEvent(Object->DeBuffMsg);
		ReleaseMutex(Object->hmutex);//解锁
		Sleep(1000);
	}
	return 0;
}

unsigned WINAPI FlushGPSkill(LPVOID lpParameter)
{
	GPHero* Object = (GPHero*)lpParameter;
	Skill* SkillRecords[MAX_HERO_SKILL_NUM];
	for (int i = 0; i < MAX_HERO_SKILL_NUM; i++)
	{
		SkillRecords[i] = Object->Skills[i];//保留技能的副本
		SkillRecords[i]->JustFlushed = false;
	}
	int curskill = 0;//记录本次更新的技能数 以便发现没有技能需要刷新时及时阻塞该线程
	while (!Object->dead)
	{
		WaitForSingleObject(Object->SkillCDMsg,INFINITE);
		if (Object->dead)
			break;
		WaitForSingleObject(Object->hmutex, INFINITE);
		curskill = 0;
		for (int i = 0; i < MAX_HERO_SKILL_NUM; i++)
		{
			if (SkillRecords[i]->LastCD > 0)
			{
				curskill++;
				if(--SkillRecords[i]->LastCD==0)
					SkillRecords[i]->JustFlushed = true;
			}
			if(SkillRecords[i]->JustFlushed)
			{
				Object->Skills[i] = SkillRecords[i];
				if (Object==CurSelectedHero)
				{
					SkillRecords[i]->JustFlushed = false;
					WaitForSingleObject(PRINTF_MUTEX, INFINITE);
					SetConsoleTextAttribute(hOut, SKILL_COLOR);
					SkillRecords[i]->PrintName();
					ReleaseMutex(PRINTF_MUTEX);
				}
			}
		}
		if (!curskill)
			ResetEvent(Object->SkillCDMsg);
		ReleaseMutex(Object->hmutex);
		Sleep(1000);
	}
	return 0;
}
unsigned WINAPI FlushAISkill(LPVOID lpParameter)
{
	AIHero* Object = (AIHero*)lpParameter;
	Skill* SkillRecords[MAX_MONSTER_SKILL_NUM];
	for (int i = 0; i < MAX_MONSTER_SKILL_NUM; i++)
	{
		SkillRecords[i] = Object->Skills[i];//保留技能的副本
		SkillRecords[i]->JustFlushed = false;
	}
	int curskill = 0;//记录本次更新的技能数 以便发现没有技能需要刷新时及时阻塞该线程
	while (!Object->dead)
	{
		WaitForSingleObject(Object->SkillCDMsg, INFINITE);
		if (Object->dead)
			break;
		WaitForSingleObject(Object->hmutex, INFINITE);
		curskill = 0;
		for (int i = 0; i < MAX_MONSTER_SKILL_NUM; i++)
		{
			if (SkillRecords[i]->LastCD > 0)
			{
				curskill++;
				if (--SkillRecords[i]->LastCD == 0)
					SkillRecords[i]->JustFlushed = true;
			}
			if (SkillRecords[i]->JustFlushed)
			{
				Object->Skills[i] = SkillRecords[i];
				if (Object == CurSelectedHero)
				{
					SkillRecords[i]->JustFlushed = false;
					WaitForSingleObject(PRINTF_MUTEX, INFINITE);
					SetConsoleTextAttribute(hOut, SKILL_COLOR);
					SkillRecords[i]->PrintName();
					ReleaseMutex(PRINTF_MUTEX);
				}
			}
		}
		if (!curskill)
			ResetEvent(Object->SkillCDMsg);
		ReleaseMutex(Object->hmutex);
		Sleep(1000);
	}
	return 0;
}