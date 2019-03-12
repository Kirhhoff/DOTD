#ifndef HERO_H
#define HERO_H

#include"SystemDependency.h"
#include"GameSetting.h"
#include"Element.h"
#include"Enumeration.h"
#include"NavigateForward.h"
#include"AIFSMForward.h"
//以下是英雄类
class Hero 
{
protected:
	int CurExperical;//当前的经验值
	int ExpercialNeeded;//升级所需经验值
	Attribute BaseAttribute;//0级的属性
	Attribute IncAttribute;//每次升级增加的属性
	Special BaseSpecial;
	Special IncSpecial;
public:
	//该部分成员需要在每次重生时初始化
	int number;//英雄在本阵营的编号
	bool dead;//是否已经死亡
	COORD KerLoc;//标记其内核位置
	COORD Destination;//标记其目的地
	Skill* Skills[MAX_THING_NUM_H];//英雄的技能
	Equipment* Equipments[MAX_THING_NUM_H];//英雄的装备
	Attribute uAttribute;//英雄的基础属性
	Special special;//英雄的特殊效果 要挨个手动初始化
	int level;//英雄等级
	int LeftSkillPoint;//剩余的技能点
	Buff* Head;
	Buff* Rear;
	Hero* HeroToChase;//要追逐的对象

	//
	HANDLE BuffMsg;
	HANDLE DeBuffMsg;
	HANDLE SkillCDMsg;
	HANDLE hmutex;
	MinHeap* Open;
	Aector* Close;
	Astar* PathBegin;
	Astar* NextLoc;

	//该部分成员只需在游戏开始时初始化
	int StockNumber;//英雄在库中的编号
	DWORD Apperance;//英雄的外观 要挨个手动初始化
	string name;//英雄名字
	string SelectedSound[MAX_SOUND_NUM];//被选择音效
	string DieSound;//死亡音效
	CAMP camp;//英雄阵营

	///该部分是AI与GP共有的方法
	bool FindPath();
	void Jmp(COORD NextKerLoc);
	bool GetEquipment(Equipment* NewEquipment);
	void PrintSelf();//在KerLoc处打印自己
	void PrintInformation();//显示英雄信息
	void PrintImage();//显示头像
	void PrintHappy();
	void PrintGeneral();
	void PrintSad();
	void EraseSelf();//在KerLoc处抹去自己
	void ShowSelf();//在KerLoc处显示自己
	void SuckBlood(int blood);//主要是用于吸血
	void SuckEnergy(int magic);//主要是用于吸蓝
	void GetEquipmentEffection(Injury EquipmentEffection);//获得装备效果
	void GetEffectedByBuff(Buff* BuffEffection);//获得技能 消耗品的效果影响
	void GetEffectedByDeBuff(Buff* BuffEffection);//获得敌方/减益效果
	void GetSkillEffection(Skill* skill);//受到技能效果
	void LoseEquipment(int index);//失去装备
	void GetSlowRecovery(Attribute& ThingEff);//因为回复效果来自消耗品 技能 因此大多驻留在内存中 可以传引用
	void GetSlowInjury(Attribute& ThingEff);//缓慢掉血
	void LoadBIAttribute(Attribute Base, Attribute Inc);//加载基础和增长属性 仅在游戏开始时调用
	void LoadBISpecial(Special Base, Special Inc);

	///该部分是虚方法
	virtual void GetSelected();
	virtual void GetInjuried(Hero* Attacker);//受到伤害
	virtual void LoadReuseAttribute();//加载重利用属性 仅在游戏开始时调用
	virtual void Operating() = 0;//运行函数 英雄依次为主体
	virtual void PrintFunction() = 0;//
	virtual void Rebrith()=0;//重生
	virtual void Die() = 0;//死亡
	virtual void GenerateReward() = 0;//获得奖励

	Hero() {};
	virtual~Hero() {};
};
class GPHero:virtual public Hero
{
	virtual void Rebrith();//英雄重生
	virtual void Die();//英雄死亡
public:
	///以下是GP特有的成员
	//该部分每次重生时需要初始化
	Consumable * Consumables[MAX_THING_NUM_H];//英雄的消耗品
	Consumable* EnhanceBooks[MAX_THING_NUM_H];//商店卖的强化书
	bool isChasing;//是否正在跟随

	//
	HANDLE AttackMsg;
	HANDLE MoveMsg;
	HANDLE ChaseMsg;

	//该部分仅在游戏开始初始化
	string MoveSounds[MAX_SOUND_NUM];//移动音效
	string AttackSounds[MAX_SOUND_NUM-1];//攻击音效
	string AttackedSound;//受到攻击音效
	string BoughtSound;//购买音效
	string LackSound;//缺钱音效
	string DeathAnnounce;//死亡通知音效
	
	///以下是GP特有的方法
	void LevelUp();
	void MoveTo(COORD destination);
	void TransportEquipTo(int HeroIndex);
	void TransportConsumableTo(int HeroIndex);
	void LoseConsumable(int index);//失去消耗品
	bool GetConsumable(Consumable* NewConsumable);//得到消耗品
	void UseConsumable(int index);
	void GetExperical(int experical);//获得经验
	
	///以下是虚方法
	virtual void GetSelected();
	virtual void LoadReuseAttribute();//初始化时设置重利用属性 仅在游戏开始时调用
	virtual void Operating();
	virtual void GetInjuried(Hero* Attacker);//受到伤害
	virtual void PrintFunction();//
	virtual void GenerateReward();
	

	GPHero() {};
	virtual~GPHero() {};
};
class AIHero :virtual public Hero
{
	virtual void Rebrith();//辅导员重生
	virtual void Die();//辅导员死亡
public:
	///以下是AI特有的成员
	//该部分每次重生时需要初始化
	AIState* CurAIState;
	AIState* TmpAIState;
	AIState* AIStates[AI_STATE_NUM];
	
	//该部分仅在游戏开始初始化

	///以下是GP特有的方法
	void SetRebrithLevel(int NewLevel);

	///以下是虚方法
	virtual void GetSelected();
	virtual void GetInjuried(Hero* Attacker);//受到伤害
	virtual void LoadReuseAttribute();//初始化时设置重利用属性 仅在游戏开始时调用
	virtual void Operating();
	virtual void PrintFunction();//
	virtual void GenerateReward();
	
	
	AIHero() {};
	virtual~AIHero() {};
};

#endif