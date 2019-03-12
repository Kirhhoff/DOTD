#include"Hero.h"
#include"MouseFSM.h"
#include"Dameon.h"
#include"APIVariable.h"
#include"GameView.h"
#include"SoundCallback.h"
#include"ServiceCallback.h"
#include"Reload.h"
#include"ControlVariable.h"
#include"UnitVariable.h"

void ShowGameProgress()
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);
	SetConsoleCursorPosition(hOut, { 0,0 });
	SetConsoleTextAttribute(hOut, GAME_INFO);
	printf("寝室完好：%d轮\n距离辅导员（们）下次来查寝：%2ds", Round, IntervalLastTime);
	ReleaseMutex(PRINTF_MUTEX);
}
void EraseGameProgress()
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);
	SetConsoleCursorPosition(hOut, { 0,0 });
	printf("               \n                               ");
	ReleaseMutex(PRINTF_MUTEX);
}
void BuyHero(int HeroNumber)
{
	if (money >=CurHeroPrice)//如果有足够的钱
	{
		for (int i = 1; i <= CurNum[Allies]; i++)
			if (Heros[i]->StockNumber == HeroNumber)
				return;//已经有这个英雄了 就不能再买了
		money -= CurHeroPrice;//花钱
		CurHeroPrice += INC_HERO_PRICE;//更新价格
		//新英雄加入
		Heros[CurNum[Allies]+1] = &HeroStock[HeroNumber];
		//播放音效
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayBoughtSound, (void*)(&HeroStock[HeroNumber]), 0, NULL));//为英雄创建线程 投入使用
		//投入使用
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, LoadGPHero, (void*)(&HeroStock[HeroNumber]), 0, NULL));//为英雄创建线程 投入使用
	}
}
void EraseThing(TYPE T, int index)//T可以是SKILL CONSUMBALE EQUIPMENT index范围0-5
{
	int left = (SCREEN_WIDTH - (3 * (3 - T) - index % 3)*(1 + THING_WIDTH_CHAR))*PIX_PER_WIDTH;//算出左边起点
	int top = (SCREEN_HEIGHT - (2 - index / 3)*(1 + THING_HEIGHT_CHAR) + 1)*PIX_PER_HEIGHT;//算出上边起点
	SelectObject(hdc, hBlackBrush);
	Rectangle(hdc, left, top, left + THING_WIDTH_PIX, top + THING_HEIGHT_PIX);//抹黑
}
void BeginTransportOrUpSkill(COORD Destination)
{
	GPHero* Tmp;
	if (Tmp=dynamic_cast<GPHero*>(CurSelectedHero))
	{
		if ((Destination.X % (THING_WIDTH_CHAR + 1) == 0) || (Destination.Y % (THING_HEIGHT_CHAR + 1) == 0))//点在分界线上无效
			return;
		int xIndex = Destination.X / (THING_WIDTH_CHAR + 1);//范围是0-8
		int yIndex = Destination.Y / (THING_HEIGHT_CHAR + 1);//范围是0-1
		int Ftype = xIndex / 3;//范围是0-2 分别指技能 消耗品 和装备 //对商店来说分别指强化书 消耗品 和装备
		int RealIndex = yIndex * 3 + xIndex % 3;//索引范围是0-5
		switch (Ftype)
		{
		case 0://技能栏则升级技能
		{
			if (Tmp->LeftSkillPoint > 0)//如果有技能点
			{
				Tmp->LeftSkillPoint--;//技能点-1
				Tmp->Skills[RealIndex]->LevelUp();//技能升级
				CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(Click)), 0, NULL));
			}
			else
				CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(Invalid)), 0, NULL));
		}
			return;
		break;
		case 1://消耗品栏
		{
			if (Tmp->Consumables[RealIndex])//如果有消耗品 开始转移
			{
				TransportedType = CONSUMABLE;
				CurTransportedThingIndex = RealIndex;
				TmpMOPState = TMState;
				CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(Click)), 0, NULL));
			}
			else
				CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(Invalid)), 0, NULL));
		}
			break;
		case 2://装备栏
		{
			if (Tmp->Equipments[RealIndex])//如果有装备
			{
				TransportedType = EQUIPMENT;
				CurTransportedThingIndex = RealIndex;
				TmpMOPState = TMState;
				CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(Click)), 0, NULL));
			}
			else
				CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(Invalid)), 0, NULL));
		}
			break;
		default:
			break;
		}

	}
}
void GameOver()
{

}


void HandleMenuInput(MOUSE_EVENT_RECORD NewEvent)
{
	CurMenuState->SolveMouseInput(NewEvent);
	CurMenuState = TmpMenuState;
}
void HandleKeyInput(KEY_EVENT_RECORD NewEvent) 
{
	GPHero* Tmp;
	if (NewEvent.bKeyDown)
	{
		int HeroNumber = NewEvent.wVirtualKeyCode - 48;
		if (NewEvent.dwControlKeyState&LEFT_CTRL_PRESSED&&HeroNumber > 0 && HeroNumber <= GP_STOCK)//如果控制键按下 说明是要买英雄
			BuyHero(HeroNumber);
		else if (HeroNumber >= 0 && HeroNumber <= CurNum[Allies])//如果是合法的英雄选定
		{
			if(dynamic_cast<TransportingState*>(CurMOPState))//如果在转移
			{
				if (!(Tmp = dynamic_cast<GPHero*>(CurSelectedHero)))
					system("pause");
				if (HeroNumber == 0)//选0说明要卖装备
				{
					EraseThing(TransportedType, CurTransportedThingIndex);//擦去物品图片
					money += ((TransportedType == EQUIPMENT) ? Tmp->Equipments[CurTransportedThingIndex]->GetEffection().BaseAttack->RewardM : Tmp->Consumables[CurTransportedThingIndex]->Effect()->Effection.RewardM)*SELL_RATE / 10;//拿钱
					if (TransportedType == EQUIPMENT)
						Tmp->LoseEquipment(CurTransportedThingIndex); //卖掉物品
					else
						Tmp->LoseConsumable(CurTransportedThingIndex);//卖掉物品
				}
				else//说明要转移东西
				{
					if (TransportedType == CONSUMABLE && Heros[HeroNumber]->GetConsumable(Tmp->Consumables[CurTransportedThingIndex]))//如果是传输的消耗品 而且有空位
					{
						Tmp->LoseConsumable(CurTransportedThingIndex);//失去装备
						EraseThing(CONSUMABLE, CurTransportedThingIndex);//抹去图片
					}
					else if (TransportedType == EQUIPMENT && Heros[HeroNumber]->GetEquipment(Tmp->Equipments[CurTransportedThingIndex]))//如果是传输的装备 而且有空位
					{
						Tmp->LoseEquipment(CurTransportedThingIndex);//失去装备
						EraseThing(EQUIPMENT, CurTransportedThingIndex);//抹去图片
					}
				}
				CurMOPState = FMState;//重置状态
			}
			else if(!dynamic_cast<SkillingState*>(CurMOPState))//如果不是转移就切换英雄 或者购买英雄
			{
				Gotta = dynamic_cast<GPHero*>(CurSelectedHero );
				(CurSelectedHero = Heros[HeroNumber])->GetSelected();//登记信息 通知英雄他被选定了 指示他做出动作
			}
		}
		CurMOPState = FMState;//重置状态
	}
}
void HandleMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	CurMOPState->SolveMouseInput(NewEvent);
	CurMOPState = TmpMOPState;
}
