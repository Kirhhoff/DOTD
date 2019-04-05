#include"Element.h"
#include"ConsoleView.h"
#include"APIVariable.h"
void Equipment::PrintName(int index)
{
	short xStart = SCREEN_WIDTH - (3 - index % 3)*(THING_WIDTH_CHAR + 1);
	short yStart = SCREEN_HEIGHT + (index / 3 - 2)*(THING_HEIGHT_CHAR + 1) + 1;
	SelectObject(hdc, hBlackBrush);
	Rectangle(hdc, xStart*PIX_PER_WIDTH, yStart*PIX_PER_HEIGHT, (xStart + THING_WIDTH_CHAR )*PIX_PER_WIDTH, (yStart + THING_HEIGHT_CHAR )*PIX_PER_HEIGHT);
	SetConsoleCursorPosition(hOut, { xStart , yStart });
	printf("￥：%d", EquipEffection.BaseAttack->RewardM);
	SetConsoleCursorPosition(hOut, { xStart , yStart +1});
	switch (StockNumber)
	{
	case 0://锋哥的指甲刀
	{
		printf("锋哥的");
		SetConsoleCursorPosition(hOut, { xStart , yStart+2 });
		printf("指甲刀");
	}
	break;
	case 1://锋哥的订书机
	{
		printf("锋哥的");
		SetConsoleCursorPosition(hOut, { xStart , yStart + 2 });
		printf("订书机");
	}
	break;
	case 2://拖鞋
	{
		printf("拖鞋");
	}
	break;
	case 3://加厚的班服
	{
		printf("加厚的");
		SetConsoleCursorPosition(hOut, { xStart , yStart + 2 });
		printf("班服");
	}
	break;
	case 4://吹风机
	{
		printf("吹风机");
	}
	break;
	case 5://锋哥的杠铃
	{
		printf("锋哥的");
		SetConsoleCursorPosition(hOut, { xStart , yStart + 2 });
		printf("杠铃");
	}
	break;
	default:
		break;
	}
}
void Equipment::Set(Injury injury, string EquipName)
{
	EquipEffection = injury;
	name = EquipName;
}