#include"Hero.h"
#include"MouseFSM.h"
#include"APIVariable.h"
#include"Dameon.h"
#include"SoundCallback.h"
#include"ControlVariable.h"

void TransportingState::SolveMouseReleased(COORD Destination)
{
	GPHero* Tmp;
	if (!(Tmp = dynamic_cast<GPHero*>(CurSelectedHero)))
		system("pause");
	if (LeftButtonPressed) //如果左键按下 进行转移
	{
		if (Active[Destination.X][Destination.Y].Occupied&&(Gotta=dynamic_cast<GPHero*>(Active[Destination.X][Destination.Y].OccupyingUnit)))
		{
			if (Active[Destination.X][Destination.Y].OccupyingUnit->number)//不是0说明要转移
			{
				if (TransportedType == CONSUMABLE && Gotta->GetConsumable(Tmp->Consumables[CurTransportedThingIndex]))//如果是传输的消耗品 而且有空位
				{
					Tmp->LoseConsumable(CurTransportedThingIndex);//失去装备
					EraseThing(CONSUMABLE, CurTransportedThingIndex);//抹去图片
				}
				else if (TransportedType == EQUIPMENT && Active[Destination.X][Destination.Y].OccupyingUnit->GetEquipment(Tmp->Equipments[CurTransportedThingIndex]))//如果是传输的装备 而且有空位
				{
					Tmp->LoseEquipment(CurTransportedThingIndex);//失去装备
					EraseThing(EQUIPMENT, CurTransportedThingIndex);//抹去图片
				}
			}
			else//是0说明要卖
			{
				EraseThing(TransportedType, CurTransportedThingIndex);//擦去物品图片
				money += ((TransportedType == EQUIPMENT) ? Tmp->Equipments[CurTransportedThingIndex]->GetEffection().BaseAttack->RewardM : Tmp->Consumables[CurTransportedThingIndex]->Effect()->Effection.RewardM)*SELL_RATE / 10;//拿钱
				if (TransportedType == EQUIPMENT)
					Tmp->LoseEquipment(CurTransportedThingIndex);//卖掉物品
				else
					Tmp->LoseConsumable(CurTransportedThingIndex);//卖掉物品
			}
		}
		TmpMOPState = FMState;//转换为普通状态
	}
	else//如果按下右键
	{
		if (Destination.Y < BATTLE_AREA)//如果位于战场区
		{
			Tmp->MoveTo(Destination);//英雄行动
			TmpMOPState = FMState;//转换为普通状态
		}
	}
	LeftButtonPressed = false;//重置
	
}
void TransportingState::SolveMouseMoved(COORD MovedLoc)
{
	COORD RelativeLoc;//相对坐标
	if (MovedLoc.X > INFO_FUNCTION&&MovedLoc.Y > BATTLE_AREA)//如果鼠标位于功能区
		MouseOperateState::SolveMouseMoved(MovedLoc);
	else if (MovedLoc.X <= INFO_FUNCTION || MovedLoc.Y <= BATTLE_AREA)//鼠标不位于功能区
	{
		if (!isShowingHero)
		{
			isShowingHero = true;//设置在显示英雄
			CurSelectedHero->PrintImage();//显示当前选定的英雄的头像
		}
		CurSelectedHero->PrintInformation();//显示当前选定的英雄的信息
											//Sleep(500);
	}
}
void TransportingState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	switch (NewEvent.dwEventFlags)
	{
	case 0:
	{
		if (NewEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//左键按下
		{
			LeftButtonPressed = true;
			CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(Click)), 0, NULL));
		}
		else if (NewEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//右键按下
			;
		else//按键释放
			SolveMouseReleased(NewEvent.dwMousePosition);//对其进行处理
	}
	break;
	case MOUSE_MOVED://鼠标移动
		SolveMouseMoved(NewEvent.dwMousePosition);//对其处理
		break;
	default:
		break;
	}
}