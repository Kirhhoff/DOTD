#include"Hero.h"
#include"MouseFSM.h"
#include"APIVariable.h"
#include"ConsoleView.h"
#include"GameView.h"
#include"SoundCallback.h"
#include"Dameon.h"
#include"ControlVariable.h"

void SkillingState::SolveMouseReleased(COORD Destination)
{
	for (short y = LastMousePos.Y-TmpSkillRange; y <= LastMousePos.Y + TmpSkillRange; y++)//清除技能指示
		FillConsoleOutputCharacter(hOut, ' ', TmpSkillRange*2+1, { LastMousePos.X - TmpSkillRange,y }, &num);
	if (LeftButtonPressed) //如果左键按下
	{
		if (Destination.Y < BATTLE_AREA)//如果点在战场区 说明是在施放技能
		{
			for (short y = LastMousePos.Y - TmpSkillRange; y <= LastMousePos.Y + TmpSkillRange; y++)
				for (short x = LastMousePos.X - TmpSkillRange; x <= LastMousePos.X + TmpSkillRange; x++)
					if (Active[x][y].Occupied&&Active[x][y].UnitCamp==CurTriggeredSkill->Effection->Camp)
						Active[x][y].OccupyingUnit->GetSkillEffection(CurTriggeredSkill);
			CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(TriggerSkill)), 0, NULL));
			CurSelectedHero->uAttribute.Energy -= CurTriggeredSkill->EnergyConsume;//耗蓝
			CurTriggeredSkill->LastCD = CurTriggeredSkill->CD;//设置CD
			EraseThing(SKILL, CurTriggeredSkill->index);
			CurSelectedHero->Skills[CurTriggeredSkill->index] = NULL;
			SetEvent(CurSelectedHero->SkillCDMsg);//发送刷新技能的信号
		}
	}
	//非左键点在战场区则不进行响应
	TmpMOPState = FMState;//状态转移
	LeftButtonPressed = false;//重置
}
void SkillingState::SolveMouseMoved(COORD MovedLoc)
{
	if ((MovedLoc.Y<BATTLE_AREA))//这里说明一下 一旦鼠标进入功能区 就不应该再判断是否在放技能了  因为这时不应该显示放技能信息
	{
		for (short y = LastMousePos.Y - TmpSkillRange; y <= LastMousePos.Y + TmpSkillRange; y++)
		{
			FillConsoleOutputAttribute(hOut,DefaultColor, TmpSkillRange * 2 + 1, { LastMousePos.X - TmpSkillRange,y }, &num);
			FillConsoleOutputCharacter(hOut, ' ', TmpSkillRange * 2 + 1, { LastMousePos.X - TmpSkillRange,y }, &num);
		}
		TmpSkillRange = CurTriggeredSkill->Range();//暂存技能范围
		LastMousePos.X = MovedLoc.X > TmpSkillRange ? ((MovedLoc.X+ TmpSkillRange<BATTLE_WIDTH? MovedLoc.X : BATTLE_WIDTH -1- TmpSkillRange)): TmpSkillRange;
		LastMousePos.Y = MovedLoc.Y > TmpSkillRange ? ((MovedLoc.Y + TmpSkillRange<BATTLE_HEIGHT ? MovedLoc.Y : BATTLE_HEIGHT - 1 - TmpSkillRange)) : TmpSkillRange;
		for (short y = LastMousePos.Y - TmpSkillRange; y <= LastMousePos.Y + TmpSkillRange; y++)
			FillConsoleOutputCharacter(hOut, SKILL_CHAR, TmpSkillRange * 2 + 1, { LastMousePos.X - TmpSkillRange,y }, &num);
	}
	else if (MovedLoc.X > INFO_FUNCTION)//如果鼠标位于功能区
		MouseOperateState::SolveMouseMoved(MovedLoc);

	if (!isShowingHero)
	{
		isShowingHero = true;//设置在显示英雄
		CurSelectedHero->PrintImage();//显示当前选定的英雄的头像
	}
}
void SkillingState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
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