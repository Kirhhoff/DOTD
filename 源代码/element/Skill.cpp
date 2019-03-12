#include"Element.h"
#include"ConsoleView.h"
#include"APIVariable.h"
#include"Reload.h"
void Skill::LevelUp()
{
	*Effection += IncValue;
	if(buff)
		*buff += IncBValue;
	level++;
	PrintName();
}
void Skill::SetLevel(int DirectLevel)
{
	*Effection = BaseValue;
	for (int i = 1; i <= DirectLevel; i++)
		*Effection += IncValue;
	if (buff)
	{
		*buff = BaseBValue;
		for (int i = 1; i <= DirectLevel; i++)
			*buff += IncBValue;
	}
	level = DirectLevel;
}
void Skill::PrintName()
{
	short xStart = SCREEN_WIDTH - (9 - index % 3)*(THING_WIDTH_CHAR + 1);
	short yStart = SCREEN_HEIGHT + (index / 3-2)*(THING_HEIGHT_CHAR+1)+1;
	
	SetConsoleCursorPosition(hOut, {xStart , yStart});
	printf("等级%d", level);
	SetConsoleCursorPosition(hOut, { xStart , yStart+1 });
	printf("%s", name.c_str());
	SetConsoleCursorPosition(hOut, { xStart , yStart+2 });
	printf("消耗：%d", EnergyConsume);
	SetConsoleCursorPosition(hOut, { xStart , yStart+3 });
	printf("CD:%d", CD);
}
void Skill::SetSkill(Attribute basevalue, Attribute incvalue, Buff baseBvalue, Buff incBvalue)
{
	BaseValue = basevalue;
	IncValue = incvalue;
	if (baseBvalue.TimeLeft&&incBvalue.TimeLeft)
		buff = NULL;
	else
	{
		BaseBValue = baseBvalue;
		IncBValue = incBvalue;
	}
	SetLevel(0);
}