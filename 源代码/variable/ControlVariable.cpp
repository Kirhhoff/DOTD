#include"ControlVariable.h"
MouseOperateState* CurMOPState;
MouseOperateState* TmpMOPState;
FormalState* FMState;
SkillingState* SMState;
TransportingState* TMState;
ShoppingState* PMState;
MenuState* CurMenuState;
MenuState* TmpMenuState;
MFormalState* MFState;
M1* M1State;
M2* M2State;
M3* M3State;
M4* M4State;
M0* M0State;
atomic_bool isShowingDetail;//是否在显示物品详细信息
atomic_bool isShowingHero;//是否在显示英雄信息
TYPE TransportedType;//正在转移的物品的类型
COORD RelativeLoc;//鼠标移动时的相对坐标
Skill* CurTriggeredSkill;//当前正在释放的技能
short TmpSkillRange;//释放技能的范围
int money;//当前的金钱
int CurHeroPrice;//当前购买英雄所需的钱
GPHero* Heros[GP_STOCK+1];//英雄数组
AIHero* Monsters[AI_STOCK + 1];//辅导员数组
GPHero* Shop;//特别指向商店
GPHero* Gotta;//受益者
atomic_int CurNum[MAX_CAMP_NUM];//英雄与怪物数量数组
HANDLE EndFighting;//一次进攻结束的信号
HANDLE PRINTF_MUTEX;//输出锁 保证同时只有一个文本在输出
HANDLE CHASE_MUTEX;//追逐锁 保证全部设置完毕后才能开始追逐
Hero* CurSelectedHero;//当前选定的英雄
atomic_int CurTransportedEquipIndex;//当前正在转移的装备的索引
atomic_int CurTransportedThingIndex;//当前正在转移的消耗品的索引
bool Go;//是否游戏开始
int t = 0;
int LastShownType = -1;
int LastShownIndex = -1;
int Round=0;//游戏轮数
int IntervalLastTime = 0;//间隔剩余时间