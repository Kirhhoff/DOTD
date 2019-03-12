#include"Navigate.h"
#include"Hero.h"
#include"ConsoleView.h"
#include"APIVariable.h"
#include"GameView.h"
#include"Navigate.h"
#include"Reload.h"
#include"SoundCallback.h"
#include"Dameon.h"
#include"ControlVariable.h"
#include"Empty.h"


void Hero::GetInjuried(Hero* Attacker)
{
	if (Attacker)
	{
		HeroToChase = Attacker;
		int Blood = (Attacker->uAttribute.Pa + uAttribute.Blood*Attacker->special.PhysicalPercent / 100) * 100 / (100 + uAttribute.Pd) + (Attacker->uAttribute.Ma + uAttribute.Blood*Attacker->special.MagicPercent / 100) * 100 / (100 + uAttribute.Md);
		srand(rand()+1);
		int Rand = rand() % 100 + 1;
		if (Rand <= Attacker->uAttribute.CrRate)//暴击
			Blood *= 2;
		int BloodSucked = Blood * Attacker->special.SuckBlood / 100;
		int EnergySucked = Blood * Attacker->special.SuckMagic / 100;
		Attacker->SuckBlood(BloodSucked);
		Attacker->SuckEnergy(EnergySucked);
		uAttribute.Blood -= Blood;
	}
}
void Hero::SuckBlood(int blood)
{
	uAttribute.Blood = (uAttribute.Blood + blood) > uAttribute.MaxBlood ? uAttribute.MaxBlood : uAttribute.Blood + blood;
}
void Hero::SuckEnergy(int energy)
{
	uAttribute.Energy = (uAttribute.Energy + energy) > uAttribute.MaxEnergy ? uAttribute.MaxEnergy : uAttribute.Energy + energy;
}
void Hero::EraseSelf()
{
	FillConsoleOutputAttribute(hOut, DefaultColor, 1, KerLoc, &num);
	Active[KerLoc.X][KerLoc.Y].Occupied = false;
}
void Hero::ShowSelf()
{
	PrintSelf();//打印自己
	Active[KerLoc.X][KerLoc.Y].Occupied = true;
	Active[KerLoc.X][KerLoc.Y].OccupyingUnit = this;
	Active[KerLoc.X][KerLoc.Y].UnitCamp = camp;
}
void Hero::PrintSelf()
{
	FillConsoleOutputAttribute(hOut, Apperance, 1, KerLoc, &num);
}
void Hero::PrintImage()
{
	for (short y = BATTLE_AREA + 1; y < SCREEN_HEIGHT; y++)
		FillConsoleOutputCharacter(hOut, ' ', IMAGE_INFO, { 0,y }, &num);
	for (short y = BATTLE_AREA + 1; y < SCREEN_HEIGHT; y++)
		FillConsoleOutputAttribute(hOut, Apperance, IMAGE_INFO, { 0,y }, &num);//打印头像背景
	//下面这部分是共有的
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance,EyeHeight }, &num);//画左眼
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance,EyeHeight }, &num);//画右眼
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium,NoseHeight }, &num);//画鼻子
	FillConsoleOutputAttribute(hOut, 0, 2 * MouthWidth + 1, { ImageMidium - MouthWidth,MouthHeight }, &num);//画平嘴
	//下面这些是独特的
	if (uAttribute.Blood >= (uAttribute.MaxBlood / 2))
		PrintHappy();
	else if (uAttribute.Blood <= (uAttribute.MaxBlood / 4))
		PrintSad();
	else
		PrintGeneral();
}
void Hero::PrintHappy()
{
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance - 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance + 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance ,EyebrowHeight-1 }, &num);//画左边翘起的眉毛
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance - 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance + 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance ,EyebrowHeight - 1 }, &num);//画右边翘起的眉毛
	
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - MouthWidth,MouthHeight - 1 }, &num);//画左上扬嘴角
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + MouthWidth,MouthHeight - 1 }, &num);//画右上扬嘴角

}
void Hero::PrintSad()
{
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance - 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance + 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance ,EyebrowHeight - 1 }, &num);//画左边翘起的眉毛
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance - 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance + 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance ,EyebrowHeight - 1 }, &num);//画右边翘起的眉毛

	for (short i = 2; i <= 4; i++)//左右各画三滴眼泪
	{
		FillConsoleOutputAttribute(hOut, TearColor, 1, { ImageMidium - EyeDistance,EyeHeight + i }, &num);
		FillConsoleOutputAttribute(hOut, TearColor, 1, { ImageMidium + EyeDistance,EyeHeight + i }, &num);
	}
}
void Hero::PrintGeneral()
{
	FillConsoleOutputAttribute(hOut, 0, 3, { ImageMidium - EyeDistance - 1,EyebrowHeight }, &num);//画左边的平眉毛
	FillConsoleOutputAttribute(hOut, 0, 3, { ImageMidium + EyeDistance - 1,EyebrowHeight }, &num);//画右边的平眉毛
}
void Hero::PrintInformation()
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);
	if (this==Shop)//区分商店和英雄
	{
		SetConsoleTextAttribute(hOut, DefaultColor);
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 1 });
		printf("大本营:%13s               Lv.%d",  name.c_str(),level);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 2 });
		SetConsoleTextAttribute(hOut, MoneyColor);
		printf("金钱:%15d               ", money);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 3 });
		SetConsoleTextAttribute(hOut, BloodColor);
		printf("生命值:%7d/%5d               ", uAttribute.Blood, uAttribute.MaxBlood);
		SetConsoleTextAttribute(hOut, DefaultColor);
		printf("经验:%9d/%5d", CurExperical, ExpercialNeeded);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 4 });
		SetConsoleTextAttribute(hOut, PdColor);
		printf("护甲:%15d               ", uAttribute.Pd);
		SetConsoleTextAttribute(hOut, MdColor);
		printf("魔抗:%15d", uAttribute.Md);
		for (short y = 5; y <= 10; y++)
		{
			SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + y });
			printf("                                                       ");
		}


	}
	else
	{
		SetConsoleTextAttribute(hOut, DefaultColor);
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 1 });
		printf("英雄%d:%14s               Lv.%d", number, name.c_str(),level);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 3 });
		printf("技能点:%13d               经验:%9d/%5d",LeftSkillPoint,CurExperical,ExpercialNeeded);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 9 });
		printf("物理百分比:%8d%%               魔法百分比:%8d%%",special.PhysicalPercent,special.MagicPercent);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 4 });
		SetConsoleTextAttribute(hOut, BloodColor);
		printf("生命值:%7d/%5d               ",uAttribute.Blood,uAttribute.MaxBlood);
		SetConsoleTextAttribute(hOut, EnergyColor);
		printf("法力值:%7d/%5d", uAttribute.Energy, uAttribute.MaxEnergy);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 2 });
		SetConsoleTextAttribute(hOut, MoneyColor);
		printf("金钱:%15d", money);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 5 });
		SetConsoleTextAttribute(hOut, PaColor);
		printf("攻击力:%13d               ",uAttribute.Pa);
		SetConsoleTextAttribute(hOut, MaColor);
		printf("法强:%15d",uAttribute.Ma);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 6 });
		SetConsoleTextAttribute(hOut, PdColor);
		printf("护甲:%15d               ",uAttribute.Pd);
		SetConsoleTextAttribute(hOut, MdColor);
		printf("魔抗:%15d",uAttribute.Md);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 7 });
		SetConsoleTextAttribute(hOut, SpeedColor);
		printf("攻速:%15f               移速:%15f",uAttribute.Frequence,uAttribute.Speed);
		
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 8 });
		SetConsoleTextAttribute(hOut, BloodColor);
		printf("生命偷取:%10d%%               ",special.SuckBlood);
		SetConsoleTextAttribute(hOut, EnergyColor);
		printf("法力汲取:%10d%%",special.SuckMagic);
		
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 10 });
		SetConsoleTextAttribute(hOut, BloodColor);
		printf("暴击率:%12d%%",uAttribute.CrRate);
	}
	ReleaseMutex(PRINTF_MUTEX);
}
bool Hero::GetEquipment(Equipment* NewEquipment)
{
	for(int i=0;i<MAX_THING_NUM;i++)
		if (!Equipments[i])
		{
			WaitForSingleObject(hmutex, INFINITE);
			Equipments[i] = NewEquipment;//增加信息
			GetEquipmentEffection(NewEquipment->GetEffection());//获得装备效果
			ReleaseMutex(hmutex);
			return true;
		}
	return false;
}
void Hero::GetEquipmentEffection(Injury EquipEffection)
{
	uAttribute += *(EquipEffection.BaseAttack);
	special += *(EquipEffection.special);
}
void Hero::GetSlowRecovery(Attribute& ThingEff)
{
	uAttribute.Blood = ((uAttribute.Blood + ThingEff.Blood) > uAttribute.MaxBlood) ? uAttribute.MaxBlood : uAttribute.Blood + ThingEff.Blood;
	uAttribute.Energy = ((uAttribute.Energy + ThingEff.Energy) > uAttribute.MaxEnergy) ? uAttribute.MaxEnergy : uAttribute.Energy + ThingEff.Energy;
}
void Hero::GetSlowInjury(Attribute& ThingEff)
{
	uAttribute.Blood = uAttribute.Blood > ThingEff.Blood ? uAttribute.Blood - ThingEff.Blood : 0;
	uAttribute.Energy = uAttribute.Energy > ThingEff.Energy ? uAttribute.Energy- ThingEff.Energy : 0;
}
void Hero::Jmp(COORD NextKerLoc)
{
	WaitForSingleObject(CHASE_MUTEX, INFINITE);
	//这一部分是抹除之前的
	EraseSelf();
	//更新内核位置
	KerLoc = NextKerLoc;
	//这一部分是更新的
	ShowSelf();
	ReleaseMutex(CHASE_MUTEX);
}
bool Hero::FindPath()
{
	if (KerLoc == Destination)
		return false;
	Astar* Start = new Astar(NULL, KerLoc, Destination);
	Open->insert(Start);//将起始点假如开启列表中
	Astar* Curstar = Open->remove();//获得这个位置
	for (; Curstar->Loc != Destination;)
	{
		if (Active[Destination.X][Destination.Y].Occupied)
		{
			int dx = Curstar->Loc.X-Destination.X;
			int dy= Curstar->Loc.Y - Destination.Y;
			if (dx > 0)
				Destination.X++;
			else if (dx < 0)
				Destination.X--;
			if (dy > 0)
				Destination.Y++;
			else if (dx < 0)
				Destination.Y--;

		}
		if (Curstar->Loc == Destination)
			break;
		Close->Add(Curstar);//关闭列表中添加当前方格
		int y1 = Curstar->Loc.Y ? Curstar->Loc.Y - 1 : 0;
		int y2 = (BATTLE_HEIGHT - Curstar->Loc.Y - 1) ? Curstar->Loc.Y + 1: BATTLE_HEIGHT-1;
		int x1 = Curstar->Loc.X ? Curstar->Loc.X - 1 : 0;
		int x2= (BATTLE_WIDTH - Curstar->Loc.X - 1) ? Curstar->Loc.X + 1 : BATTLE_WIDTH - 1;
		for (short y = y1; y <= y2; y++)
			for (short x = x1; x <= x2; x++)
			{
					if (Active[x][y].Occupied &&Destination != COORD({ x,y }))//有人而且那还不是目的地的话 就设置Flase
						Close->Add(new Astar(NULL, { x,y }, { x,y }));
					if (!Close->find({ x,y }))
					{
						Astar* Son;
						if (Son = Open->find({ x,y }))//如果这块砖在开启列表中
						{
							int NewG = Curstar->G + ((Curstar->Loc.X == x || Curstar->Loc.Y == y) ? 10 : 14);//计算新的G值
							if (NewG < Son->G)//如果新路径更短 那么就更新这块砖的信息
							{
								Son->Father = Curstar;
								Son->G = NewG;
								Son->F = Son->G + Son->H;
								Open->Heapify();//重新维护堆的性质
							}
						}
						else
							Open->insert(new Astar(Curstar, { x,y }, Destination));//如果不在开启列表中 开启列表中增加这一项
					}
			}
		if (!(Curstar = Open->remove()))//开启列表中移除最小优先方格
		{
			Close->Clean();
			return false;//如果此时列表已经空 说明没有路径 失败
		}
	}
	Curstar->Next = Curstar;//设置最后一个的结尾
	Curstar->IsPath = true;
	auto son = Curstar;//设置Next的性质
	for (auto tmp = Curstar->Father; tmp; )
	{
		tmp->IsPath = true;
		tmp->Next = son;
		son = son->Father;
		tmp = tmp->Father;
	}
	for (; PathBegin;)//删除旧的路径
	{
		auto tmp = PathBegin;//暂存这个节点
		PathBegin = PathBegin->Next;//向后推一个节点
		if (tmp == PathBegin)//如果这个节点和它的后续节点相同 说明到了结尾 那么就可以退出了
			break;
		else 
			delete tmp;//删除这个节点
	}
	NextLoc =PathBegin = Start;//设置起点
	Open->Clean();//将除路径外的其他
	Close->Clean();//节点全部删除
	return true;//寻路成功
}
void Hero::LoseEquipment(int index)
{
	EraseThing(EQUIPMENT, index);//擦去图片
	uAttribute -= *(Equipments[index]->GetEffection().BaseAttack);//删除基础效果
	special -= *(Equipments[index]->GetEffection().special);//删除特殊效果
	Equipments[index] = NULL;//清除记录
}
void Hero::GetEffectedByBuff(Buff* BuffEffection)
{
	if (BuffEffection->Effection.LastTime)//如果是持续性效果
	{//以下是准备工作 创建一个buff的副本
		Buff* Tmp = new Buff(*BuffEffection);
		Tmp->Next = Head->Next;
		Tmp->Prev = Head;
		Head->Next = Head->Next->Prev = Tmp;//更新节点信息
		uAttribute += Tmp->Effection;//进行状态加成
		//通知线程 有Buff产生
		SetEvent(BuffMsg);
	}
	else
	{
		uAttribute += BuffEffection->Effection;
		special += BuffEffection->special;
	}
}
void Hero::GetEffectedByDeBuff(Buff* BuffEffection)
{
	if (BuffEffection->Effection.LastTime)//如果是持续性效果
	{//以下是准备工作 创建一个buff的副本
		Buff* Tmp = new Buff(*BuffEffection);
		Tmp->Next = Head->Next;
		Tmp->Prev = Head;
		Head->Next = Head->Next->Prev = Tmp;//更新节点信息
		uAttribute -= Tmp->Effection;//进行状态减益
		special -= Tmp->special;//进行状态减益
		//通知线程 有Buff产生
		SetEvent(DeBuffMsg);
	}
	else
	{
		uAttribute -= BuffEffection->Effection;
		special -= BuffEffection->special;
	}
}
void Hero::GetSkillEffection(Skill* skill)
{
	if (skill->Owner->camp == camp)
	{
		uAttribute += *skill->Effection;
		if (skill->buff)
			GetEffectedByBuff(skill->buff);
	}
	else
	{
		int FinalInjury = (skill->Effection->Pa + skill->ADR*skill->Owner->uAttribute.Pa)*uAttribute.Pd / (100 + uAttribute.Pd) + (skill->Effection->Ma + skill->APR*skill->Owner->uAttribute.Ma)*uAttribute.Md / (100 + uAttribute.Md);
		uAttribute.Blood = uAttribute.Blood>=FinalInjury? uAttribute.Blood - FinalInjury:0;
		uAttribute -= *skill->Effection;
		if (skill->buff)
			GetEffectedByDeBuff(skill->buff);
	}
}
void Hero::LoadBIAttribute(Attribute Base, Attribute Inc)
{
	uAttribute=BaseAttribute = Base;
	IncAttribute = Inc;
}
void Hero::LoadBISpecial(Special Base, Special Inc)
{
	special=BaseSpecial = Base;
	IncSpecial = Inc;
}
void Hero::GetSelected()
{
	for (short y = BATTLE_AREA + 1; y < SCREEN_HEIGHT; y++)
		FillConsoleOutputCharacterA(hOut, ' ', SCREEN_WIDTH - INFO_FUNCTION - 2, { INFO_FUNCTION + 1,y }, &num);
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySelectedSound, (void*)this, 0, NULL));
	PrintImage();//显示头像区
	PrintInformation();//显示信息区
	PrintFunction();//设置功能区
}
void Hero::LoadReuseAttribute()
{
	CurExperical = 0;
	//number=??? number只有在购买时才确定
	dead = false;
	KerLoc = HERO_INITIAL_LOC;
	Destination = HERO_INITIAL_LOC;
	uAttribute = BaseAttribute;
	special = BaseSpecial;
	level = 0;
	LeftSkillPoint = 0;
	Head = new Buff({ 0,EMPTY_ATTRIBUTE,EMPTY_SPECIAL,NULL,NULL });
	Rear = new Buff({ 0,EMPTY_ATTRIBUTE,EMPTY_SPECIAL,NULL,NULL });
	Head->Next = Rear;
	Rear->Prev = Head;
	HeroToChase = NULL;
	for (int i = 0; i < MAX_THING_NUM; i++)
		Equipments[i] = NULL;
}