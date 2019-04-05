#include"Element.h"
#include"ConsoleView.h"
#include"APIVariable.h"
void Consumable::PrintName(int index)
{
	short xStart = SCREEN_WIDTH - (6 - index % 3)*(THING_WIDTH_CHAR + 1);
	short yStart = SCREEN_HEIGHT + (index / 3 - 2)*(THING_HEIGHT_CHAR + 1) + 1;
	SetConsoleCursorPosition(hOut, { xStart , yStart });
	printf("￥：%d", ConsumableEffetion->Effection.RewardM);
	SetConsoleCursorPosition(hOut, { xStart , yStart +1});
	switch (StockNumber)
	{
	case 0://烤奶
	{
		printf("烤奶");
	}
	break;
	case 1://肾宝
	{
		printf("肾宝");
	}
	break;
	case 2://好吃的奇异果
	{
		printf("好吃的");
		SetConsoleCursorPosition(hOut, { xStart , yStart + 2 });
		printf("奇异果");
	}
	break;
	case 3://维C柠檬茶
	{
		printf("维C柠檬茶");
	}
	break;
	case 4://咖啡
	{
		printf("咖啡");
	}
	break;
	case 5://电脑配件
	{
		printf("电脑配件");
	}
	break;
	default:
		break;
	}
}
void Consumable::PrintName(int index, int)
{
	short xStart = SCREEN_WIDTH - (9 - index % 3)*(THING_WIDTH_CHAR + 1);
	short yStart = SCREEN_HEIGHT + (index / 3 - 2)*(THING_HEIGHT_CHAR + 1) + 1;
	SetConsoleCursorPosition(hOut, { xStart , yStart });
	printf("￥：%d", ConsumableEffetion->Effection.RewardM);
	SetConsoleCursorPosition(hOut, { xStart , yStart + 1 });
	switch (StockNumber)
	{
	case 0://大学物理
	{
		printf("大学物理");
	}
	break;
	case 1://精神分析
	{
		printf("精神分析");
	}
	break;
	case 2://思想品德
	{
		printf("思想品德");
	}
	break;
	case 3://修仙法则
	{
		printf("修仙法则");
	}
	break;
	case 4://智力逻辑
	{
		printf("智力逻辑");
	}
	break;
	case 5://保送游泳
	{
		printf("保送游泳");
	}
	break;
	default:
		break;
	}
}