#include"Hero.h"
#include"MouseFSM.h"
#include"ConsoleView.h"
#include"APIVariable.h"
#include<stdio.h>
#include"GameView.h"
#include"SoundCallback.h"
#include"ControlVariable.h"

void ShoppingState::ShowDetail(int FTYPE, int REALINDEX)
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);
	for (short y = BATTLE_AREA + 1; y < SCREEN_HEIGHT; y++)
	{
		FillConsoleOutputCharacterA(hOut, ' ', IMAGE_INFO, { 0,y }, &num);
		FillConsoleOutputAttribute(hOut, 0, IMAGE_INFO, { 0,y }, &num);
		FillConsoleOutputAttribute(hOut, 0, INFO_FUNCTION - IMAGE_INFO - 1, { IMAGE_INFO + 1,y }, &num);
	}
	SetConsoleCursorPosition(hOut, { 0,BATTLE_AREA + 1 });//定位光标
	SetConsoleTextAttribute(hOut, DefaultColor);
	switch (FTYPE)
	{
	case 0://强化书
	{
		switch (Shop->EnhanceBooks[REALINDEX]->StockNumber)
		{
		case 0://大学物理
			printf("永久增加5点攻击力：来尝尝知识的厚重吧！");
			break;
		case 1://精神分析
			printf("永久增加5点法强：\"悲歌可以当泣，远望可以当归\"");
			break;
		case 2://思想品德
			printf("永久增加5点护甲：这样，他就能站在道德的高地上，用思想品\n德武装自己");
			break;
		case 3://修仙法则
			printf("永久增加5点魔抗：我这都快得道成仙了，还怕你这小打小闹？\nNaive!");
			break;
		case 4://智商逻辑
			printf("永久增肌0.2攻击速度：学习逻辑可以提高智商，大抵如此");
			break;
		case 5://保送游泳
			printf("永久增加0.1移动速度：我游着都比你跑着快，你这渣渣");
			break;
		default:
			break;
		}
	}
	break;
	case 1://消耗品
	{
		switch (Shop->Consumables[REALINDEX]->StockNumber)
		{
		case 0://烤奶
			printf("它常时沉默寡言，不愿意展示自己，“销量？我奶君是需要销\n量来证明的吗？”。然而坊间却一直流传着它军训时的光伟，\n有人说只是传说……“我高贵的奶红怎么会和原谅绿为伍！”\n的确，人们都若有所思地点点头，仿佛确信一般。");
			break;
		case 1://肾宝
			printf("不知名的橙色饮料");
			break;
		case 2://好吃的奇异果
			printf("“为什么你叫奇异果呢？”“切！”，面对人们的疑惑，奇异\n果先生不屑地发声，“奇异果怎么了，你们也可以叫我猕猴桃\n啊，再说了”，他使劲挺了挺胸脯，用听起来似乎很坚毅的声\n音表示，“水果之王可不是白叫的，不信你们可以尝一口。”\n然而当人们跃跃欲试的时候，他却迈开大步走掉了，顿时人们\n唏嘘一片……");
			break;
		case 3://维C柠檬茶
			printf("\"维C柠檬茶，爽过吸大麻\"");
			break;
		case 4://咖啡
			printf("茶和咖啡，同样供给刺激，好比购物，是你的绝对尊贵自由");
			break;
		case 5://电脑配件
			printf("“嗯……让我看看这次又找到了什么”，大佬一边举起新发现\n的零件，一边扶了扶眼镜，一旁的Emphasizer等待着大佬的分\n析。“嗯……根据我的综合判断，这是个电脑零件。”，大佬\n严肃地说道。Emphasizer挠了挠头，“那……这到底是哪个部\n位的？”大佬顿时怒不可遏，“能百度的问题就不要问嘛！”\n说着，拂袖而去，只留下Emphasizer一脸懵逼地看着零件……");
			break;
		default:
			break;
		}
	}
		break;
	case 2://装备
	{
		Rectangle(hdc, 0, (BATTLE_AREA + 1)*PIX_PER_HEIGHT, IMAGE_INFO*PIX_PER_WIDTH, SCREEN_HEIGHT*PIX_PER_HEIGHT);
		switch (Shop->Equipments[REALINDEX]->StockNumber)
		{
		case 0://锋哥的指甲刀
			printf("“直到那一天，人们终于想起被锋哥的指甲刀支配的恐惧，以\n及无论如何锋哥都不借给你的耻辱”\n                                             -----阿门\n");
			break;
		case 1://锋哥的订书机
			printf("自从用了锋哥的订书机，大家就可以在每订一次就得打开一次\n订书机摆正钉子的间隔中思考人生，思考克制自己的欲望，\n绝对不能诉诸武力，学会心平气和。看到大家都学会了控制情\n绪，锋哥高兴得想从轮椅上站起来");
			break;
		case 2://拖鞋
			printf("“如果非要有什么推荐给大家的话，那就一定是拖鞋了”");
			break;
		case 3://加厚的班服
			printf("当大家都在纠结加厚的班服是否真的适合广州的天气时，锋哥\n已经默默地把它穿上了。“明明就不热！”大家向他望去，随\n即一哄而散了。锋哥从不理会关于“虚”的一些流言，仍然在\n四十度时紧裹班服。只是据他的舍友追忆，他生前喜欢喝一罐\n不知名的橙色饮料，然后躺下睡觉。");
			break;
		case 4://吹风机
			printf("关于到底吹风机能不能加快攻击速度的问题，Emphasizer已经\n显得不厌其烦了，“够了！”，他大声呵斥道。人们都吓了一\n跳，“起码”，咽了咽口水，他继续说道，“我的头发是干得\n比以前快了。”");
			break;
		case 5://锋哥的杠铃
			printf("实际上，据Emphasizer说，在刚买来时，它还只是一个小哑铃\n。“你们看，它长得多快！”，锋哥像摸着自己的孩子一样抚\n摸着他的杠铃。“嗯……哥，你说的对……”，大家都为他鼓\n掌。可当人们问起来的时候，Emphasizer也只是模糊的回答：\n“没错，我是锋哥的舍友……但我们也不清楚他到底是怎么把\n那玩意搞得越来越大的。”");
			break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}
	ReleaseMutex(PRINTF_MUTEX);

}
void ShoppingState::TriggerFunction(COORD Destination)
{
	if (Gotta)//如果购买者是己方
	{
		if ((Destination.Y == (THING_HEIGHT_CHAR + 1)) || (Destination.X % (THING_WIDTH_CHAR + 1) == 0))//点在分界线上无效
			return;
		int xIndex = Destination.X / (THING_WIDTH_CHAR + 1);//范围是0-8
		int yIndex = Destination.Y / (THING_HEIGHT_CHAR + 1);//范围是0-1
		int Ftype = xIndex / 3;//范围是0-2 分别指技能 消耗品 和装备 //对商店来说分别指强化书 消耗品 和装备
		int RealIndex = yIndex * 3 + xIndex % 3;//索引范围是0-5
		switch (Ftype)
		{
		case 0://买强化书
		{
			if (money >= Shop->EnhanceBooks[RealIndex]->Effect()->Effection.RewardM&&Gotta)
			{
				Gotta->GetEffectedByBuff(Shop->EnhanceBooks[RealIndex]->Effect());//获得强化效果
				money -= Shop->EnhanceBooks[RealIndex]->Effect()->Effection.RewardM;//付钱
				CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlaySystemSound, (void*)(int(TriggerEnhanceBook)), 0, NULL));
			}
			else
				CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayLackSound, (void*)Gotta, 0, NULL));
		}
		break;
		case 1://买消耗品
		{
			if ((money >= Shop->Consumables[RealIndex]->Effect()->Effection.RewardM) && Gotta&&Gotta->GetConsumable(Shop->Consumables[RealIndex]))//钱够而且有空位
				money -= Shop->Consumables[RealIndex]->Effect()->Effection.RewardM;//付钱
			else
				CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayLackSound, (void*)Gotta, 0, NULL));
		}
		break;
		case 2://买装备
		{
			if ((money >= (Shop->Equipments[RealIndex]->GetEffection()).BaseAttack->RewardM) && Gotta&& Gotta->GetEquipment(Shop->Equipments[RealIndex]))//钱够而且有空位
				money -= (Shop->Equipments[RealIndex]->GetEffection().BaseAttack->RewardM);//付钱
			else
				CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayLackSound, (void*)Gotta, 0, NULL));
		}
		break;
		default:
			break;
		}
	}
}
void ShoppingState::SolveMouseReleased(COORD Destination)
{
	if (LeftButtonPressed)//若是按下左键
	{
		if (Destination.Y < BATTLE_AREA&&Active[Destination.X][Destination.Y].Occupied)//如果位于战场区域且选中的位置有单位
			(CurSelectedHero = Active[Destination.X][Destination.Y].OccupyingUnit)->GetSelected();//那就选中他
		else if (Destination.Y > BATTLE_AREA&&Destination.X > INFO_FUNCTION)//如果不在战场区且位于功能区
			TriggerFunction({ Destination.X - INFO_FUNCTION,Destination.Y - BATTLE_AREA });//触发对应区域的功能
	}
	LeftButtonPressed = false;
}
void ShoppingState::SolveMouseMoved(COORD MovedLoc)
{
	if (MovedLoc.X > INFO_FUNCTION&&MovedLoc.Y > BATTLE_AREA)//如果鼠标位于功能区
	{
		RelativeLoc.X = MovedLoc.X - INFO_FUNCTION;
		RelativeLoc.Y = MovedLoc.Y - BATTLE_AREA;

		if ((RelativeLoc.Y == (THING_HEIGHT_CHAR + 1)) || (RelativeLoc.X % (THING_WIDTH_CHAR + 1) == 0))//点在分界线上无效
			return;
		int xIndex = RelativeLoc.X / (THING_WIDTH_CHAR + 1);//范围是0-8
		int yIndex = RelativeLoc.Y / (THING_HEIGHT_CHAR + 1);//范围是0-1
		int Ftype = xIndex / 3;//范围是0-2 分别指技能 消耗品 和装备 //对商店来说分别指强化书 消耗品 和装备
		int RealIndex = yIndex * 3 + xIndex % 3;//索引范围是0-5
		if (LastShownIndex != RealIndex || LastShownType != Ftype)
		{
			isShowingHero = false;//设置没在显示英雄
			ShowDetail(Ftype, RealIndex);//展示其信息
			LastShownIndex = RealIndex;
			LastShownType = Ftype;
		}
	}
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
void ShoppingState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
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
