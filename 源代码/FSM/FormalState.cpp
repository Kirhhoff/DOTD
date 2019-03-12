#include"MouseFSM.h"
#include"Hero.h"
#include<process.h>
#include"ConsoleView.h"
#include"SoundCallback.h"
#include"APIVariable.h"
#include"Dameon.h"
#include"ControlVariable.h"

void FormalState::TriggerFunction(COORD Destination)
{
	GPHero* Tmp;
	if (Tmp = dynamic_cast<GPHero*>(CurSelectedHero))
	{
		if ((Destination.Y == (THING_HEIGHT_CHAR + 1)) || (Destination.X % (THING_WIDTH_CHAR + 1) == 0))//点在分界线上无效
			return;
		int xIndex = Destination.X / (THING_WIDTH_CHAR + 1);//范围是0-8
		int yIndex = Destination.Y / (THING_HEIGHT_CHAR + 1);//范围是0-1
		int Ftype = xIndex / 3;//范围是0-2 分别指技能 消耗品 和装备 //对商店来说分别指强化书 消耗品 和装备
		int RealIndex = yIndex * 3 + xIndex % 3;//索引范围是0-5
		switch (Ftype)
		{
		case 0://技能栏
		{
			if (Tmp->Skills[RealIndex] && (Tmp->uAttribute.Energy > Tmp->Skills[RealIndex]->EnergyConsume))//如果有技能且蓝量足够
			{
				TmpMOPState = SMState;
				CurTriggeredSkill = Tmp->Skills[RealIndex];//设置该技能为当前触发技能
			}
			else
				CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(Invalid)), 0, NULL));
		}
		break;
		case 1://消耗品栏 
			Tmp->UseConsumable(RealIndex);
			break;
		case 2://装备栏无法主动触发
			break;
		default:
			break;
		}
	}
}
void FormalState::SolveMouseReleased(COORD Destination)
{
	if (LeftButtonPressed)//若是按下左键
	{
		if (Destination.Y < BATTLE_AREA&&Active[Destination.X][Destination.Y].Occupied)//如果位于战场区域且选中的位置有单位
		{
			Gotta = dynamic_cast<GPHero*>(CurSelectedHero);
			(CurSelectedHero = Active[Destination.X][Destination.Y].OccupyingUnit)->GetSelected();//那就选中他
		}
		else if (Destination.Y > BATTLE_AREA&&Destination.X > INFO_FUNCTION)//如果不在战场区且位于功能区
			TriggerFunction({ Destination.X - INFO_FUNCTION,Destination.Y - BATTLE_AREA });//触发对应区域的功能
	}
	else//若是按下右键
	{
		GPHero* Tmp;
		if (Tmp = dynamic_cast<GPHero*>(CurSelectedHero))
		{
			if (Destination.Y < BATTLE_AREA)//如果位于战场区
				Tmp->MoveTo(Destination);//英雄行动
			else if (Destination.Y > BATTLE_AREA&&Destination.X > INFO_FUNCTION)//如果位于功能区
				BeginTransportOrUpSkill({ Destination.X - INFO_FUNCTION,Destination.Y - BATTLE_AREA });//那么开始转移或者升级技能
		}
	}
	LeftButtonPressed = false;//重置
}
void FormalState::SolveMouseMoved(COORD MovedLoc)
{
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
void FormalState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
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