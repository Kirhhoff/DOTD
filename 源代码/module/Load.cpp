#include"Load.h"
#include"GameView.h"
#include"Element.h"
#include"SoundCallback.h"
#include"Navigate.h"
#include"AIFSM.h"
#include"ConsoleView.h"
#include"APIVariable.h"
#include"ServiceCallback.h"
#include"ActionCallback.h"
#include"UnitVariable.h"
#include"Empty.h"
#include"ControlVariable.h"

//**********************************************************************************************
//*****************************************以下是装载函数***************************************
//**********************************************************************************************
void LoadHeroApperance()
{
	HeroStock[0].Apperance = CitadelColor;
	HeroStock[1].Apperance = Cairne_Bloodhoof;
	HeroStock[2].Apperance = Tyrande_Whisperwind;
	HeroStock[3].Apperance = Illidan_Stormrage;
	HeroStock[4].Apperance = Uther;

	MonsterStock[1].Apperance = CitadelColor;
	MonsterStock[2].Apperance = CitadelColor;
	MonsterStock[3].Apperance = CitadelColor;
}
void LoadHeroSound()
{
	HeroStock[0].SelectedSound[0] = "open 造访商店.wav alias aa";
	HeroStock[0].SelectedSound[1] = "open 造访商店.wav alias aa";
	HeroStock[0].SelectedSound[2] = "open 造访商店.wav alias aa";
	HeroStock[0].SelectedSound[3] = "open 造访商店.wav alias aa";

	HeroStock[1].MoveSounds[0] = "open 大一移动1.wav alias aa";
	HeroStock[1].MoveSounds[1] = "open 大一移动2.wav alias aa";
	HeroStock[1].MoveSounds[2] = "open 大一移动3.wav alias aa";
	HeroStock[1].MoveSounds[3] = "open 大一移动4.wav alias aa";
	HeroStock[1].AttackSounds[0] = "open 大一攻击1.wav alias aa";
	HeroStock[1].AttackSounds[1] = "open 大一攻击2.wav alias aa";
	HeroStock[1].AttackSounds[2] = "open 大一攻击3.wav alias aa";
	HeroStock[1].SelectedSound[0] = "open 大一选定1.wav alias aa";
	HeroStock[1].SelectedSound[1] = "open 大一选定2.wav alias aa";
	HeroStock[1].SelectedSound[2] = "open 大一选定3.wav alias aa";
	HeroStock[1].SelectedSound[3] = "open 大一选定4.wav alias aa";
	HeroStock[1].BoughtSound = "open 大一购买.wav alias aa";
	HeroStock[1].DieSound = "open 大一死亡.wav alias aa";
	HeroStock[1].LackSound= "open 大一缺钱.wav alias aa";
	HeroStock[1].AttackedSound = "open 大一被打.wav alias aa";
	HeroStock[1].DeathAnnounce = "open 大一死亡通知.wav alias aa";

	HeroStock[2].MoveSounds[0] = "open 大二移动1.wav alias aa";
	HeroStock[2].MoveSounds[1] = "open 大二移动2.wav alias aa";
	HeroStock[2].MoveSounds[2] = "open 大二移动3.wav alias aa";
	HeroStock[2].MoveSounds[3] = "open 大二移动4.wav alias aa";
	HeroStock[2].AttackSounds[0] = "open 大二攻击1.wav alias aa";
	HeroStock[2].AttackSounds[1] = "open 大二攻击2.wav alias aa";
	HeroStock[2].AttackSounds[2] = "open 大二攻击3.wav alias aa";
	HeroStock[2].SelectedSound[0] = "open 大二选定1.wav alias aa";
	HeroStock[2].SelectedSound[1] = "open 大二选定2.wav alias aa";
	HeroStock[2].SelectedSound[2] = "open 大二选定3.wav alias aa";
	HeroStock[2].SelectedSound[3] = "open 大二选定4.wav alias aa";
	HeroStock[2].BoughtSound = "open 大二购买.wav alias aa";
	HeroStock[2].DieSound = "open 大二死亡.wav alias aa";
	HeroStock[2].LackSound = "open 大二缺钱.wav alias aa";
	HeroStock[2].AttackedSound = "open 大二被打.wav alias aa";
	HeroStock[2].DeathAnnounce = "open 大二死亡通知.wav alias aa";

	HeroStock[3].MoveSounds[0] = "open 大三移动1.wav alias aa";
	HeroStock[3].MoveSounds[1] = "open 大三移动2.wav alias aa";
	HeroStock[3].MoveSounds[2] = "open 大三移动3.wav alias aa";
	HeroStock[3].MoveSounds[3] = "open 大三移动4.wav alias aa";
	HeroStock[3].AttackSounds[0] = "open 大三攻击1.wav alias aa";
	HeroStock[3].AttackSounds[1] = "open 大三攻击2.wav alias aa";
	HeroStock[3].AttackSounds[2] = "open 大三攻击3.wav alias aa";
	HeroStock[3].SelectedSound[0] = "open 大三选定1.wav alias aa";
	HeroStock[3].SelectedSound[1] = "open 大三选定2.wav alias aa";
	HeroStock[3].SelectedSound[2] = "open 大三选定3.wav alias aa";
	HeroStock[3].SelectedSound[3] = "open 大三选定4.wav alias aa";
	HeroStock[3].BoughtSound = "open 大三购买.wav alias aa";
	HeroStock[3].DieSound = "open 大三死亡.wav alias aa";
	HeroStock[3].LackSound = "open 大三缺钱.wav alias aa";
	HeroStock[3].AttackedSound = "open 大三被打.wav alias aa";
	HeroStock[3].DeathAnnounce = "open 大三死亡通知.wav alias aa";

	HeroStock[4].MoveSounds[0] = "open 大四移动1.wav alias aa";
	HeroStock[4].MoveSounds[1] = "open 大四移动2.wav alias aa";
	HeroStock[4].MoveSounds[2] = "open 大四移动3.wav alias aa";
	HeroStock[4].MoveSounds[3] = "open 大四移动4.wav alias aa";
	HeroStock[4].AttackSounds[0] = "open 大四攻击1.wav alias aa";
	HeroStock[4].AttackSounds[1] = "open 大四攻击2.wav alias aa";
	HeroStock[4].AttackSounds[2] = "open 大四攻击3.wav alias aa";
	HeroStock[4].SelectedSound[0] = "open 大四选定1.wav alias aa";
	HeroStock[4].SelectedSound[1] = "open 大四选定2.wav alias aa";
	HeroStock[4].SelectedSound[2] = "open 大四选定3.wav alias aa";
	HeroStock[4].SelectedSound[3] = "open 大四选定4.wav alias aa";
	HeroStock[4].BoughtSound = "open 大四购买.wav alias aa";
	HeroStock[4].DieSound = "open 大四死亡.wav alias aa";
	HeroStock[4].LackSound = "open 大四缺钱.wav alias aa";
	HeroStock[4].AttackedSound = "open 大四被打.wav alias aa";
	HeroStock[4].DeathAnnounce = "open 大四死亡通知.wav alias aa";

	MonsterStock[1].DieSound = "open 辅导员1死亡.wav alias aa";
	MonsterStock[1].SelectedSound[0] = "open 辅导员1选定1.wav alias aa";
	MonsterStock[1].SelectedSound[1] = "open 辅导员1选定2.wav alias aa";
	MonsterStock[1].SelectedSound[2] = "open 辅导员1选定3.wav alias aa";
	MonsterStock[1].SelectedSound[3] = "open 辅导员1选定4.wav alias aa";

	MonsterStock[2].DieSound = "open 辅导员2死亡.wav alias aa";
	MonsterStock[2].SelectedSound[0] = "open 辅导员2选定1.wav alias aa";
	MonsterStock[2].SelectedSound[1] = "open 辅导员2选定2.wav alias aa";
	MonsterStock[2].SelectedSound[2] = "open 辅导员2选定3.wav alias aa";
	MonsterStock[2].SelectedSound[3] = "open 辅导员2选定4.wav alias aa";

	MonsterStock[3].DieSound = "open 辅导员3死亡.wav alias aa";
	MonsterStock[3].SelectedSound[0] = "open 辅导员3选定1.wav alias aa";
	MonsterStock[3].SelectedSound[1] = "open 辅导员3选定2.wav alias aa";
	MonsterStock[3].SelectedSound[2] = "open 辅导员3选定3.wav alias aa";
	MonsterStock[3].SelectedSound[3] = "open 辅导员3选定4.wav alias aa";

	CitadelAttackedSounds[0] = "open 拆家1.wav alias aa";
	CitadelAttackedSounds[1] = "open 拆家2.wav alias aa";
	CitadelAttackedSounds[2] = "open 拆家3.wav alias aa";
	CitadelAttackedSounds[3] = "open 拆家4.wav alias aa";
	CitadelAttackedSounds[4] = "open 拆家5.wav alias aa";
	CitadelAttackedSounds[5] = "open 拆家6.wav alias aa";
}
void LoadHeroName()
{
	HeroStock[0].name = "寝室";
	HeroStock[1].name = "大一萌新";
	HeroStock[2].name = "大二学姐";
	HeroStock[3].name = "大三腊肉";
	HeroStock[4].name = "大四骨灰";

	AINameStock[1] = "18级辅导员";
	AINameStock[2] = "19级辅导员";
	AINameStock[3] = "20级辅导员";
}
void LoadHeroBaseAtttibuteStock()
{

	//{阵营，(自己阵营内的编号),魔抗，护甲，血量上限，法力上限，当前血量，当前法力，移速，物攻，魔攻，暴击，攻速，赏金，赏经验，(持续时间)，攻击范围}
	//寝室
	GPBAttributeStock[0] = { Allies,0,0,0,5000,0,5000,0,0,0,0,0,0,0,0,0,0 };
	//大一萌新
	GPBAttributeStock[1] = { Allies,0,10,10,625,200,625,200,1,45,0,0,0.5,100,50,0,1 };
	//大二学姐
	GPBAttributeStock[2] = { Allies,0,0,0,400,200,400,200,1,70,25,0,1,60,50,0,4 };
	//大三腊肉
	GPBAttributeStock[3] = { Allies,0,5,5,525,200,525,200,1,65,20,10,0.5,100,50,0,2 };
	//大四骨灰
	GPBAttributeStock[4] = { Allies,0,0,0,425,400,425,400,1,35,20,0,0.5,100,50,0,2 };
	// 以下为第一个辅导员基础属性      Attribute的第二个成员 成员编号应为辅导员阵营的编号？
	AIBAttributeStock[1] = { Enemy,1,3,3,500,200,500,200,2,55,20,10,8,100,60,0,1 };

	// 以下为第二个辅导员的基础属性
	AIBAttributeStock[2] = { Enemy,2,5,5,700,300,700,300,3,75,40,20,8,200,100,0,2 };

	//以下为第三个辅导员的基础属性
	AIBAttributeStock[3] = { Enemy,3,10,10,1000,500,1000,500,1,100,50,35,8,500,200,0,3 };

}
void LoadHeroIncAtttibuteStock()
{
	//{阵营，(自己阵营内的编号)，魔抗，护甲，血量上限，法力上限，当前血量，当前法力，移速，物攻，魔攻，暴击，攻速，赏金，赏经验，(持续时间)，攻击范围}
	//寝室
	GPIAtrributeStock[0] = { Allies,0,100,100,1000,0,1000,0,0,0,0,0,0,0,0,0,0 };
	//大一萌新
	GPIAtrributeStock[1] = { Allies,0,4,4,60,20,60,20,0,0,1,1,0,0,0,0,0 };
	//大二学姐
	GPIAtrributeStock[2] = { Allies,0,1,1,40,20,40,20,0,3,2,0,0.04,0,0,0,0 };
	//大三腊肉
	GPIAtrributeStock[3] = { Allies,0,3,2,50,20,50,20,0,2,2,0,0.03,0,0,0,0 };
	//大四骨灰
	GPIAtrributeStock[4] = { Allies,0,1,1,40,50,40,50,0,1,5,0,0,0,0,0,0 };

	//以下为第一个辅导员的增长属性
	AIIAttributeStock[1] = { Enemy,1,1,1,40,50,40,50,0,10,10,0,0,0,0,0,0 };

	//以下为第二个辅导员的增长属性
	AIIAttributeStock[2] = { Enemy,2,2,2,60,30,60,30,0,15,10,0,0,0,0,0,0 };

	//以下为第三个辅导员的增长属性
	AIIAttributeStock[3] = { Enemy,3,3,3,100,50,100,50,0,25,15,5,0,0,0,0,0 };
} 
void LoadHeroBaseSpecialStock()
{
	//{吸血率，吸蓝率，物理百分比率，魔法百分比率}
	GPBSpecialStock[0] = EMPTY_SPECIAL;
}
void LoadHeroIncSpecialStock()
{
	//{吸血率，吸蓝率，物理百分比率，魔法百分比率}
	GPISpecialStock[0] = EMPTY_SPECIAL;

}

void LoadSkillBaseStock()
{
	//这部分全都是永久效果 要小心
	//对敌军时
	//{Enemy，削减魔抗，削减护甲，削减血量上限，削减法力上限，削减当前血量，削减当前法力，削减移速，削减物攻，削减魔攻，削减暴击，削减攻速，(赏金)，(赏经验)，(持续时间)，削减攻击范围}
	//对友军时
	//{Allies，增加魔抗，增加护甲，增加血量上限，增加法力上限，增加当前血量，增加当前法力，增加移速，增加物攻，增加魔攻，增加暴击，增加攻速，(赏金)，(赏经验)，(持续时间)，增加攻击范围}
	GPSkillAttributeBStock[1] = { Enemy,0,0,0,0,0,0,0,0,100,0,0,0,0,0,0,2 };
	GPSkillAttributeBStock[2] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[3] = { Allies,0,0,0,0,0,75,0,0,0,0,0,0,0,0,0,0 };
	GPSkillAttributeBStock[4] = { Allies,0,0,0,0,0,0,0,0,50,0,0,0,0,0,0,0 };
	GPSkillAttributeBStock[5] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[6] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[7] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 110, 0, 0, 0, 0, 0, 0, 2 };
	GPSkillAttributeBStock[8] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[9] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[10] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[11] = { Allies,0,0,0,0,0,85,0,0,0,0,0,0,0,0,0,0 };// 回复血量
	GPSkillAttributeBStock[12] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 110, 0, 0, 0, 0, 0, 0, 2 }; //敌人收到致命的打击
	GPSkillAttributeBStock[13] = { Allies,0,0,0,0,0,90,0,0,0,0,0,0,0,0,0,0 };// 回复血量
	GPSkillAttributeBStock[14] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[15] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[16] = { Enemy, 0, 2, 2, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 }; // 降低魔抗护甲
	GPSkillAttributeBStock[17] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[18] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[19] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[20] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[21] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 120, 0, 0, 0, 0, 0, 0, 2 };
	GPSkillAttributeBStock[22] = { Allies,0,0,0,0,0,100,0,0,0,0,0,0,0,0,0,0 };
	GPSkillAttributeBStock[23] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[24] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 160, 0, 0, 0, 0, 0, 0, 2 };
}
void LoadSkillIncStock()
{
	//这部分全都是永久效果 要小心
	//对敌军时
	//{Enemy，削减魔抗，削减护甲，削减血量上限，削减法力上限，削减当前血量，削减当前法力，削减移速，削减物攻，削减魔攻，削减暴击，削减攻速，(赏金)，(赏经验)，(持续时间)，削减攻击范围}
	//对友军时
	//{Allies，增加魔抗，增加护甲，增加血量上限，增加法力上限，增加当前血量，增加当前法力，增加移速，增加物攻，增加魔攻，增加暴击，增加攻速，(赏金)，(赏经验)，(持续时间)，增加攻击范围}
	GPSkillAttributeIStock[1] = { Enemy,0,0,0,0,0,0,0,0,50,0,0,0,0,0,0,0 };
	GPSkillAttributeIStock[2] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[3] = { Allies,0,0,0,0,0,25,0,0,0,0,0,0,0,0,0,0 };
	GPSkillAttributeIStock[4] = { Allies,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0 };
	GPSkillAttributeIStock[5] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[6] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[7] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0 };
	GPSkillAttributeIStock[8] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[9] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[10] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[11] = { Allies,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0 };
	GPSkillAttributeIStock[12] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0 };
	GPSkillAttributeIStock[13] = { Allies,0,0,0,0,0,35,0,0,0,0,0,0,0,0,0,0 };
	GPSkillAttributeIStock[14] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[15] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[16] = { Enemy, 0, 1, 1, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 };
	GPSkillAttributeIStock[17] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[18] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[19] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[20] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[21] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0 };
	GPSkillAttributeIStock[22] = { Allies,0,0,0,0,0,40,0,0,0,0,0,0,0,0,0,0 };
	GPSkillAttributeIStock[23] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[24] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0 };
}
void LoadSkillBuffBaseStock()
{
	//这部分全都是暂时的 但是数值也不要太高～

	//buff里的Attribute
	//对敌军时
	//{Enemy，削减魔抗，削减护甲，削减血量上限，削减法力上限，削减当前血量，削减当前法力，削减移速，削减物攻，削减魔攻，削减暴击，削减攻速，(赏金)，(赏经验)，持续时间，削减攻击范围}
	//对友军时
	//{Allies，增加魔抗，增加护甲，增加血量上限，增加法力上限，增加当前血量，增加当前法力，增加移速，增加物攻，增加魔攻，增加暴击，增加攻速，(赏金)，(赏经验)，持续时间，增加攻击范围}

	//buff里的special
	//对敌军时(一般不会有这个效果)
	//{降低吸血率，降低吸蓝率，降低物理百分比率，降低魔法百分比率}
	//对友军时(这个可以有)
	//{增加吸血率，增加吸蓝率，增加物理百分比率，降低魔法百分比率}

	//总的来说   { (剩余持续时间),Attribute,Special,NULL,NULL}
	GPSkillBuffBStock[1] = EMPTY_BUFF;
	GPSkillBuffBStock[2] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,3,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffBStock[3] = EMPTY_BUFF;
	GPSkillBuffBStock[4] = EMPTY_BUFF;
	GPSkillBuffBStock[5] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,4,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffBStock[6] = { 0,EMPTY_ATTRIBUTE,{ 50,0,0,0 },NULL,NULL };
	GPSkillBuffBStock[7] = EMPTY_BUFF;
	GPSkillBuffBStock[8] = { 0,{ Allies,0,0,0,0,0,0,0,0,55,0,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL }; // 攻击
	GPSkillBuffBStock[9] = { 0,{ Allies,0,0,0,0,0,0,0,1,0,0,0,0,0,0,4,0 },EMPTY_SPECIAL,NULL,NULL }; //移速
	GPSkillBuffBStock[10] = { 0,{ Allies,0,1,1,0,0,0,0,0,10,5,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL }; //全方面
	GPSkillBuffBStock[11] = EMPTY_BUFF;
	GPSkillBuffBStock[12] = EMPTY_BUFF;
	GPSkillBuffBStock[13] = EMPTY_BUFF;
	GPSkillBuffBStock[14] = { 0,{ Allies,0,0,0,0,0,0,0,0,60,0,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL }; // 攻击力
	GPSkillBuffBStock[15] = { 0,{ Allies,0,2,2,0,0,0,0,0,15,10,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL };//各方面
	GPSkillBuffBStock[16] = EMPTY_BUFF;
	GPSkillBuffBStock[17] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,6,0 },EMPTY_SPECIAL,NULL,NULL };//攻速
	GPSkillBuffBStock[18] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,30,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL };//暴击率
	GPSkillBuffBStock[19] = { 0,{ Allies,0,3,3,0,0,0,0,0,20,15,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL };//各方面
	GPSkillBuffBStock[20] = { 0,{ Allies,0,0,0,0,0,0,0,0,70,0,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL };//攻击力
	GPSkillBuffBStock[21] = EMPTY_BUFF;
	GPSkillBuffBStock[22] = EMPTY_BUFF;
	GPSkillBuffBStock[23] = { 0, { Allies,0,0,0,0,0,0,0,1,0,0,0,0,0,0,6,0 }, EMPTY_SPECIAL, NULL, NULL };//移速
	GPSkillBuffBStock[24] = EMPTY_BUFF;
}
void LoadSkillBuffIncStock()
{
	//这部分全都是暂时的 但是数值也不要太高～

	//buff里的Attribute
	//对敌军时
	//{Enemy，削减魔抗，削减护甲，削减血量上限，削减法力上限，削减当前血量，削减当前法力，削减移速，削减物攻，削减魔攻，削减暴击，削减攻速，(赏金)，(赏经验)，持续时间，削减攻击范围}
	//对友军时
	//{Allies，增加魔抗，增加护甲，增加血量上限，增加法力上限，增加当前血量，增加当前法力，增加移速，增加物攻，增加魔攻，增加暴击，增加攻速，(赏金)，(赏经验)，持续时间，增加攻击范围}

	//buff里的special
	//对敌军时(一般不会有这个效果)
	//{降低吸血率，降低吸蓝率，降低物理百分比率，降低魔法百分比率}
	//对友军时(这个可以有)
	//{增加吸血率，增加吸蓝率，增加物理百分比率，降低魔法百分比率}

	//总的来说   { (剩余持续时间),Attribute,Special,NULL,NULL}	
	GPSkillBuffIStock[1] = EMPTY_BUFF;
	GPSkillBuffIStock[2] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[3] = EMPTY_BUFF;
	GPSkillBuffIStock[4] = EMPTY_BUFF;
	GPSkillBuffIStock[5] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[6] = { 0,EMPTY_ATTRIBUTE,EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[7] = EMPTY_BUFF;
	GPSkillBuffIStock[8] = { 0,{ Allies,0,0,0,0,0,0,0,0,10,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[9] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[10] = { 0,{ Allies,0,1,1,0,0,0,0,0,10,5,0,0,0,0,0,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[11] = EMPTY_BUFF;
	GPSkillBuffIStock[12] = EMPTY_BUFF;
	GPSkillBuffIStock[13] = EMPTY_BUFF;
	GPSkillBuffIStock[14] = { 0,{ Allies,0,0,0,0,0,0,0,0,15,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[15] = { 0,{ Allies,0,2,2,0,0,0,0,0,15,10,0,0,0,0,0,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[16] = EMPTY_BUFF;
	GPSkillBuffIStock[17] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[18] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,10,0,0,0,1,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[19] = { 0,{ Allies,0,3,3,0,0,0,0,0,20,15,0,0,0,0,0,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[20] = { 0,{ Allies,0,0,0,0,0,0,0,0,25,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[21] = EMPTY_BUFF;
	GPSkillBuffIStock[22] = EMPTY_BUFF;
	GPSkillBuffIStock[23] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[24] = EMPTY_BUFF;
}
void LoadSkillStock()
{
	LoadSkillBaseStock();
	LoadSkillIncStock();
	LoadSkillBuffBaseStock();
	LoadSkillBuffIncStock();
	for (int i = 1; i <= GP_STOCK * MAX_HERO_SKILL_NUM; i++)
	{
		GPSkillStock[i].StockNumber = i;
		GPSkillStock[i].index = (i - 1) % MAX_HERO_SKILL_NUM;
		GPSkillStock[i].SetSkill(GPSkillAttributeBStock[i], GPSkillAttributeIStock[i], GPSkillBuffBStock[i], GPSkillBuffIStock[i]);
		GPSkillStock[i].Owner = &HeroStock[(i - 1) / MAX_HERO_SKILL_NUM + 1];
		GPSkillStock[i].JustFlushed = false;
		GPSkillStock[i].LastCD = 0;
	}
	for (int i = 1; i <= AI_STOCK * MAX_MONSTER_SKILL_NUM; i++)
	{
		AISkillStock[i].StockNumber = i;
		AISkillStock[i].index = (i - 1) % MAX_MONSTER_SKILL_NUM;
		AISkillStock[i].SetSkill(AISkillAttributeBStock[i], AISkillAttributeIStock[i], AISkillBuffBStock[i], AISkillBuffIStock[i]);
		AISkillStock[i].Owner = &MonsterStock[(i - 1) / MAX_MONSTER_SKILL_NUM + 1];
		AISkillStock[i].JustFlushed = false;
		AISkillStock[i].LastCD = 0;
	}

	GPSkillStock[1].name = "跑步";
	GPSkillStock[1].CD = 10;
	GPSkillStock[1].EnergyConsume = 20;

	GPSkillStock[2].name = "突然上头";
	GPSkillStock[2].CD = 15;
	GPSkillStock[2].EnergyConsume = 20;

	GPSkillStock[3].name = "吃鸡排";
	GPSkillStock[3].CD = 35;
	GPSkillStock[3].EnergyConsume = 5;

	GPSkillStock[4].name = "锻炼身体";
	GPSkillStock[4].CD = 15;
	GPSkillStock[4].EnergyConsume = 20;

	GPSkillStock[5].name = "自嗨";
	GPSkillStock[5].CD = 25;
	GPSkillStock[5].EnergyConsume = 30;

	GPSkillStock[6].name = "帮找Bug";
	GPSkillStock[6].CD = 20;
	GPSkillStock[6].EnergyConsume = 30;
	
	GPSkillStock[7].name = "化妆";
	GPSkillStock[7].CD = 10;
	GPSkillStock[7].EnergyConsume = 20;

	GPSkillStock[8].name = "志我奋斗";
	GPSkillStock[8].CD = 15;
	GPSkillStock[8].EnergyConsume = 25;

	GPSkillStock[9].name = "拖鞋加成";
	GPSkillStock[9].CD = 15;
	GPSkillStock[9].EnergyConsume = 25;

	GPSkillStock[10].name = "人生经验";
	GPSkillStock[10].CD = 20;
	GPSkillStock[10].EnergyConsume = 25;

	GPSkillStock[11].name = "刷新下限";
	GPSkillStock[11].CD = 20;
	GPSkillStock[11].EnergyConsume = 20;

	GPSkillStock[12].name = "无可奉告";
	GPSkillStock[12].CD = 25;
	GPSkillStock[12].EnergyConsume = 30;

	GPSkillStock[13].name = "背心猛虎";
	GPSkillStock[13].CD = 20;
	GPSkillStock[13].EnergyConsume = 20;

	GPSkillStock[14].name = "长者教诲";
	GPSkillStock[14].CD = 20;
	GPSkillStock[14].EnergyConsume = 30;

	GPSkillStock[15].name = "历史钦定";
	GPSkillStock[15].CD = 20;
	GPSkillStock[15].EnergyConsume = 30;

	GPSkillStock[16].name = "另请高明";
	GPSkillStock[16].CD = 20;
	GPSkillStock[16].EnergyConsume = 25;

	GPSkillStock[17].name = "阅事无数";
	GPSkillStock[17].CD = 20;
	GPSkillStock[17].EnergyConsume = 25;

	GPSkillStock[18].name = "一颗赛艇";
	GPSkillStock[18].CD = 20;
	GPSkillStock[18].EnergyConsume = 25;

	GPSkillStock[19].name = "实习";
	GPSkillStock[19].CD = 15;
	GPSkillStock[19].EnergyConsume = 25;

	GPSkillStock[20].name = "历史进程";
	GPSkillStock[20].CD = 20;
	GPSkillStock[20].EnergyConsume = 25;

	GPSkillStock[21].name = "谈笑风生";
	GPSkillStock[21].CD = 20;
	GPSkillStock[21].EnergyConsume = 20;

	GPSkillStock[22].name = "身经百战";
	GPSkillStock[22].CD = 20;
	GPSkillStock[22].EnergyConsume = 30;

	GPSkillStock[23].name = "图样森破";
	GPSkillStock[23].CD = 20;
	GPSkillStock[23].EnergyConsume = 30;

	GPSkillStock[24].name = "拿衣服";
	GPSkillStock[24].CD = 30;
	GPSkillStock[24].EnergyConsume = 30;

}

void LoadHeroStock()
{
	LoadHeroApperance();//加载英雄颜色
	LoadHeroName();//加载英雄名字
	LoadHeroSound();//加载英雄音效
	LoadSkillStock();//加载英雄技能
					 //加载各个库
	LoadHeroBaseAtttibuteStock();
	LoadHeroIncAtttibuteStock();
	LoadHeroBaseSpecialStock();
	LoadHeroIncSpecialStock();

	//英雄设置
	HeroStock[0].StockNumber = 0;
	HeroStock[0].LoadReuseAttribute();//设置通用属性
	HeroStock[0].LoadBIAttribute(GPBAttributeStock[0], GPIAtrributeStock[0]);//设置基础属性和增长值
	HeroStock[0].LoadBISpecial(GPBSpecialStock[0], GPISpecialStock[0]);//设置基础和增长special
	for (int i = 1; i <= GP_STOCK; i++)//GP设置
	{
		HeroStock[i].StockNumber = i;//设置库编号
		HeroStock[i].LoadReuseAttribute();//设置通用属性
		HeroStock[i].LoadBIAttribute(GPBAttributeStock[i], GPIAtrributeStock[i]);//设置基础属性和增长值
		HeroStock[i].LoadBISpecial(GPBSpecialStock[i], GPISpecialStock[i]);//设置基础和增长special
		HeroStock[i].Open = new MinHeap;
		HeroStock[i].Close = new Aector;
		HeroStock[i].BuffMsg = CreateEvent(NULL, true, false, NULL);
		HeroStock[i].DeBuffMsg = CreateEvent(NULL, true, false, NULL);
		HeroStock[i].SkillCDMsg = CreateEvent(NULL, true, false, NULL);
		HeroStock[i].AttackMsg = CreateEvent(NULL, true, true, NULL);
		HeroStock[i].MoveMsg = CreateEvent(NULL, true, false, NULL);
		HeroStock[i].ChaseMsg = CreateEvent(NULL, true, false, NULL);
		HeroStock[i].hmutex = CreateMutex(NULL, false, NULL);
		for (int j = 0; j < MAX_HERO_SKILL_NUM; j++)//获得技能
			HeroStock[i].Skills[j] = &GPSkillStock[(i - 1)*MAX_HERO_SKILL_NUM + j + 1];
	}
	for (int i = 1; i <= AI_STOCK; i++)//AI设置
	{
		MonsterStock[i].StockNumber = i;//设置库编号
		MonsterStock[i].LoadReuseAttribute();//设置通用属性
		MonsterStock[i].LoadBIAttribute(AIBAttributeStock[i], AIIAttributeStock[i]);//设置基础属性和增长值
		MonsterStock[i].LoadBISpecial(AIBSpecialStock[i], AIISpecialStock[i]);//设置基础和增长special
		MonsterStock[i].Open = new MinHeap;
		MonsterStock[i].Close = new Aector;
		MonsterStock[i].BuffMsg = CreateEvent(NULL, true, false, NULL);
		MonsterStock[i].DeBuffMsg = CreateEvent(NULL, true, false, NULL);
		MonsterStock[i].SkillCDMsg = CreateEvent(NULL, true, false, NULL);
		MonsterStock[i].hmutex = CreateMutex(NULL, false, NULL);
		MonsterStock[i].AIStates[AIStill] = new AIStillState;
		MonsterStock[i].AIStates[AIPosChase] = new AIPChaseState;
		MonsterStock[i].AIStates[AINegChase] = new AINChaseState;
		for (int j = 0; j < AI_STATE_NUM; j++)
			MonsterStock[i].AIStates[j]->Object = &MonsterStock[i];
		for (int j = 0; j < MAX_MONSTER_SKILL_NUM; j++)//获得技能
			MonsterStock->Skills[j] = &GPSkillStock[(i - 1)*MAX_MONSTER_SKILL_NUM + j + 1];
	}
}
void LoadBackgroundSound()
{
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayBackgroundSound, NULL, 0, NULL));
}
void LoadTimer()
{
	HANDLE TmpHandle = (HANDLE)_beginthreadex(NULL, 0, Timer, NULL, 0, NULL);
	SetThreadPriority(TmpHandle, THREAD_PRIORITY_ABOVE_NORMAL);
	CloseHandle(TmpHandle);
}
void LoadEquipmentStock()
{
	//以下为六个装备的属性
	/*
	1、峰哥的指甲刀  （增加50点攻击力  100 块）
	2、峰哥的订书机   （降低0.5攻速 不要钱）
	3、Eul的神圣法杖 （增加移动速度 1  100块）
	4、Guinsoo的邪恶镰刀 （增加自身最大血量200 最大能量100  100块 ）
	5、斯嘉蒂之眼 （增加攻击速度0.5 120块）
	6、梅塞斯密特的掠夺 （增加暴击30 60块 ）
	*/
	//{(阵营)，(阵营编号)，增加魔抗，增加护甲，增加血量上限，增加法力上限，增加当前血量，增加当前法力，增加移速，增加物攻，增加魔攻，增加暴击，增加攻速，价格，(赏经验)，(持续时间)，增加攻击范围}

	EquipmentStock[0].Set({ new Attribute({ Allies,0,0,0,150,0,150,0,0,30,0,30,0,100,0,0,0 }),new Special({ 10,0,0,0 }) }, "锋哥的指甲刀");
	EquipmentStock[0].StockNumber = 0;
	EquipmentStock[1].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,0,50,0,0,-0.5,200,0,0,0 }),new Special({ 0,10,0,0 }) }, "锋哥的订书机");
	EquipmentStock[1].StockNumber = 1;
	EquipmentStock[2].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,1,0,0,0,0,300,0,0,0 }),new Special({ 0,0,0,0 }) }, "拖鞋");
	EquipmentStock[2].StockNumber = 2;
	EquipmentStock[3].Set({ new Attribute({ Allies,0,20,30,300,200,300,200,0,0,0,0,0,100,0,0,0 }),new Special({ 0,0,0,0 }) }, "加厚的班服");
	EquipmentStock[3].StockNumber = 3;
	EquipmentStock[4].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,0,0,0,0,1,300,0,0,0 }),new Special({ 0,0,2,2 }) }, "吹风机");
	EquipmentStock[4].StockNumber = 4;
	EquipmentStock[5].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,0,50,0,20,0,500,0,0,0 }),new Special({ 0,0,5,0 }) }, "锋哥的杠铃");
	EquipmentStock[5].StockNumber = 5;

}
void LoadConsumableStock()
{
	// 以下为六个消耗品的属性
	/*
	1、烤奶 所有友军每秒回复血量20点 持续5s（20块）
	2、肾宝 每秒恢复能量20点 持续5s（30块）
	3、好吃的奇异果 瞬间恢复能量80点 （30块）
	4、维C柠檬茶 瞬间恢复血量80点 能量60点（40块）
	5、咖啡 增加自身攻击速度0.5 持续10s （50块）
	6、电脑配件 增加自身攻击力50点 持续10s （40块）
	*/
	ConsumableStock[0].SetConsumable(true, new Buff({ 5,{ Allies,0,0,0,0,0,20,0,0,0,0,0,0,20,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "烤奶");
	ConsumableStock[0].StockNumber = 0;
	ConsumableStock[1].SetConsumable(true, new Buff({ 5,{ Allies,0,0,0,0,0,0,20,0,0,0,0,0,30,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "肾宝");
	ConsumableStock[1].StockNumber = 1;
	ConsumableStock[2].SetConsumable(false, new Buff({ 0,{ Allies,0,0,0,0,0,0,80,0,0,0,0,0,30,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "好吃的奇异果");
	ConsumableStock[2].StockNumber = 2;
	ConsumableStock[3].SetConsumable(false, new Buff({ 0,{ Allies,0,0,0,0,0,80,60,0,0,0,0,0,40,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "维C柠檬茶");
	ConsumableStock[3].StockNumber = 3;
	ConsumableStock[4].SetConsumable(false, new Buff({ 10,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,50,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "咖啡");
	ConsumableStock[4].StockNumber = 4;
	ConsumableStock[5].SetConsumable(false, new Buff({ 10,{ Allies,0,0,0,0,0,0,0,0,50,0,0,0,40,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "电脑配件");
	ConsumableStock[5].StockNumber = 5;
}
void LoadEnhanceBookStock()
{
	// 以下为6个强化书的属性
	/*
	1、数学分析 增加攻击5点 100元
	2、姿势水平 增加法强5点 100元
	3、思想道德 增加护甲3点 150元
	4、电子学习 增加魔抗2点 150元
	5、智商逻辑 增加攻速0.2 200元
	6、保送游泳 增加移速0.1 250元
	*/
	EnhanceBookStock[0].SetConsumable(false, new Buff({ 0,Attribute({ Allies,0,0,0,50,0,50,0,0,0,0,0,0,100,0,0,0 }), EMPTY_SPECIAL, NULL, NULL }), "数学分析");
	EnhanceBookStock[0].StockNumber = 0;
	EnhanceBookStock[1].SetConsumable(false, new Buff({ 0,{ Allies,0,0,0,0,30,0,30,0,0,0,0,0,100,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "线性代数");
	EnhanceBookStock[1].StockNumber = 1;
	EnhanceBookStock[2].SetConsumable(false, new Buff({ 0,{ Allies,0,0,0,0,0,0,0,0,15,0,0,0,150,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "思想道德");
	EnhanceBookStock[2].StockNumber = 2;
	EnhanceBookStock[3].SetConsumable(false, new Buff({ 0,{ Allies,0,0,0,0,0,0,0,0,0,15,0,0,150,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "电子分析");
	EnhanceBookStock[3].StockNumber = 3;
	EnhanceBookStock[4].SetConsumable(false, new Buff({ 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0.2,200,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "数字逻辑");
	EnhanceBookStock[4].StockNumber = 4;
	EnhanceBookStock[5].SetConsumable(false, new Buff({ 0,{ Allies,0,0,0,0,0,0,0,0.1,0,0,0,0,250,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "保送游泳");
	EnhanceBookStock[5].StockNumber = 5;
}
void LoadCitadel()
{
	GPHero* Citadel = &HeroStock[0];
	Heros[0] = Citadel;//增添记录
	Shop = Citadel;
	for (short y = BATTLE_HEIGHT / 2 - 1; y <= BATTLE_HEIGHT / 2 + 1; y++)//设置主城处的砖块信息
	{
		FillConsoleOutputAttribute(hOut, CitadelColor, 3, { BATTLE_WIDTH / 2 - 1,y }, &num);//涂抹主城的颜色
		for (short x = BATTLE_WIDTH / 2 - 1; x <= BATTLE_WIDTH / 2 + 1; x++)//设置砖块信息
		{
			Active[x][y].Occupied = true;
			Active[x][y].UnitCamp = Allies;
			Active[x][y].OccupyingUnit = Citadel;
		}
	}
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, CitadelOperate, NULL, 0, NULL));//为英雄创建线程 投入使用	
}
void LoadDivider()
{
	for (short y = 0; y < SCREEN_HEIGHT; y++)
		FillConsoleOutputAttribute(hOut, 0, SCREEN_WIDTH, { 0,y }, &num);
	FillConsoleOutputAttribute(hOut, DIVIDER_COLOR, BATTLE_WIDTH, { 0,BATTLE_AREA }, &num);//加载战场与非战场的分界线
	FillConsoleOutputAttribute(hOut, DIVIDER_COLOR, BATTLE_WIDTH - INFO_FUNCTION, { INFO_FUNCTION,BATTLE_AREA + THING_HEIGHT_CHAR + 1 }, &num);//加载上下物品区分界线

	for (short y = BATTLE_AREA + 1; y < SCREEN_HEIGHT; y++)
	{
		for (short x = INFO_FUNCTION; x < SCREEN_WIDTH; x += 11)
			FillConsoleOutputAttribute(hOut, DIVIDER_COLOR, 1, { x,y }, &num);//加载功能区竖直分界线
		FillConsoleOutputAttribute(hOut, DIVIDER_COLOR, 1, { IMAGE_INFO,y }, &num);
	}
}
