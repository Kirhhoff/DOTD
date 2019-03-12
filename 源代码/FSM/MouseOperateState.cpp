#include"MouseFSM.h"
#include"ConsoleView.h"
#include"APIVariable.h"
#include"Hero.h"
#include"GameView.h"
#include"ControlVariable.h"

bool MouseOperateState::LeftButtonPressed = false;
void MouseOperateState::ShowDetail(int FTYPE, int REALINDEX)
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
	case 0://技能
	{
		if (CurSelectedHero->Skills[REALINDEX])
		{
			switch (CurSelectedHero->Skills[REALINDEX]->StockNumber)
			{
			case 1://
				printf("萌新开始跑步，不小心跑到别人，直接造成物理伤害");
			break;
			case 2://
				printf("萌新想到今晚没课，突然上头，并带带动了大家，增加攻击速\n度");
			break;
			case 3://
				printf("萌新突然觉得很饿，点了一块鸡排，马上精神了很多");
			break;
			case 4:
				printf("萌新怕变成肥宅，于是开始锻炼身体，杀伤力增加了很多");
			break;
			case 5:
				printf("萌新发现今天漫画加更，很高兴，攻速立马变快了");
			break;
			case 6:
				printf("萌新开始帮同学找Bug，这不但对他人造成了伤害，还使他很快\n乐，越来越精神");
			break;
			case 7://
				printf("学会化妆之后，学姐的美貌令敌人受到会心一击");
			break;
			case 8://
				printf("受到学弟学妹们的刺激后，学姐认识到了志我奋斗的重要，决\n定每天爆肝，攻击力激增");
			break;
			case 9://
				printf("学姐决定卖萌，模仿天线宝宝，求抱抱，移速和法强增加了很\n多");
			break;
			case 10:
				printf("经过一年的磨砺之后，学姐收获了很多人生的经验，各方面获\n得增幅");
			break;
			case 11:
				printf("学姐通过工作刷新了自己认知的下限，护甲提升了很多");
			break;
			case 12:
				printf("每每有人问学姐的秘籍，学姐只告诉他们：“无可奉告”，这\n经常使人们受到致命的打击"); 
			break; 
			case 13://
				printf("三年间，腊肉们早已不在乎形象之所在，穿着背心裤衩进出课\n室，身体受到自然神力的沐浴，获得百分比伤害");
			break;
			case 14://
				printf("腊肉们经常聆听一些长者的讲座来获取人生的经验，攻击力激\n增");
			break;
			case 15://
				printf("腊肉们被选举为学生会部长，有了广阔的人脉，各方面获得增\n幅");
			break;
			case 16:
				printf("许多萌新请求腊肉们帮忙完成任务，为了学弟学妹们的进步，\n腊肉们总是会回复一句另请高明 永久降低对方魔抗护甲");
			break;
			case 17:
				printf("腊肉们阅事无数，很有经验，这使他人十分害怕");
			break;
			case 18:
				printf("腊肉们获得理想的实习机会，十分一颗赛艇，很容易上头，大\n幅增加暴击率");
			break; 
			case 19://
				printf("骨灰们通过实习积累人生的经验，各方面获得增幅");
			break;
			case 20://
				printf("骨灰们不再一股脑的努力，而是将个人的努力与历史的进程结\n合，攻击力激增");
			break;
			case 21://
				printf("骨灰们与面试官们谈笑风生，时不时地冒出惊人之语，使得对\n方难以接话，造成心理伤害");
				break;
			case 22:
				printf("骨灰们参加了百场面试，正可谓身经百战，回复自身的血量");
			break;
			case 23:
				printf("骨灰们经常用一句古老的咒语“图样图森破”来形容大一大二\n的学弟学妹，自身移速大幅增加");
			break;
			case 24:
				printf("骨灰们认为大三的同学十分的拿衣服，大三同学十分不解，对\n方收到极大伤害");
			break;
			default:
				break;
			}
		}
	}
	break;
	case 1://消耗品
	{
		GPHero* Tmp;
		if ((Tmp = dynamic_cast<GPHero*>(CurSelectedHero)) && Tmp->Consumables[REALINDEX])//如果这个位置有消耗品
		{
			switch (Tmp->Consumables[REALINDEX]->StockNumber)
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
	}
	break;
	case 2://装备
	{
		if (CurSelectedHero->Equipments[REALINDEX])//如果这个位置有装备
		{
			Rectangle(hdc, 0, (BATTLE_AREA + 1)*PIX_PER_HEIGHT, IMAGE_INFO*PIX_PER_WIDTH, SCREEN_HEIGHT*PIX_PER_HEIGHT);
			switch (CurSelectedHero->Equipments[REALINDEX]->StockNumber)
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
	}
	break;
	default:
		break;
	}
	ReleaseMutex(PRINTF_MUTEX);
}
void MouseOperateState::SolveMouseMoved(COORD MovedLoc)
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