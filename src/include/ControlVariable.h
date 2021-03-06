#ifndef CONTROLVARIABLE_H
#define CONTROLVARIABLE_H

#include"SystemDependency.h"
#include"HeroForward.h"
#include"Enumeration.h"
#include"MouseFSMForward.h"
#include"MenuFSMForward.h"
#include"ElementForward.h"
#include"GameSetting.h"

extern MouseOperateState* CurMOPState;
extern MouseOperateState* TmpMOPState;
extern FormalState* FMState;
extern SkillingState* SMState;
extern TransportingState* TMState;
extern ShoppingState* PMState;
extern MenuState* CurMenuState;
extern MenuState* TmpMenuState;
extern MFormalState* MFState;
extern M1* M1State;
extern M2* M2State;
extern M3* M3State;
extern M4* M4State;
extern M0* M0State;
extern atomic_bool isShowingDetail;//是否在显示物品详细信息
extern atomic_bool isShowingHero;//是否在显示英雄信息
extern TYPE TransportedType;//正在转移的物品的类型
extern COORD RelativeLoc;//鼠标移动时的相对坐标
extern Skill* CurTriggeredSkill;//当前正在释放的技能
extern short TmpSkillRange;//释放技能的范围
extern int money;//当前的金钱
extern int CurHeroPrice;//当前购买英雄所需的钱
extern GPHero* Heros[GP_STOCK+1];//英雄数组
extern AIHero* Monsters[AI_STOCK + 1];//辅导员数组
extern GPHero* Shop;//特别指向商店
extern GPHero* Gotta;//受益者
extern atomic_int CurNum[MAX_CAMP_NUM];//英雄与怪物数量数组
extern string CitadelAttackedSounds[CITADEL_ATTACKED_SOUND_NUM];
extern HANDLE EndFighting;//一次进攻结束的信号
extern HANDLE PRINTF_MUTEX;//输出锁 保证同时只有一个文本在输出
extern HANDLE CHASE_MUTEX;//追逐锁 保证全部设置完毕后才能开始追逐
extern Hero* CurSelectedHero;//当前选定的英雄
extern atomic_int CurTransportedEquipIndex;//当前正在转移的装备的索引
extern atomic_int CurTransportedThingIndex;//当前正在转移的消耗品的索引
extern bool Go;//是否游戏开始
extern int t;
extern int LastShownType;
extern int LastShownIndex;
extern int Round;//游戏轮数
extern int IntervalLastTime;//间隔剩余时间

#endif