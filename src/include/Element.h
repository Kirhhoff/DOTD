#ifndef ELEMENT_H
#define ELEMENT_H

#include"Enumeration.h"
#include"SystemDependency.h"
#include"HeroForward.h"
//该结构记录方格信息
struct BRICK_INFO
{
	bool Occupied;//是否被单位占据
	CAMP UnitCamp;//占据单位的阵营
	Hero* OccupyingUnit;//占据的单位
};

//以下是效果结构
struct Attribute
{
	CAMP Camp;//阵营  或者效果的作用阵营
	int Number;//自己在阵营内的编号
	int Md;//魔抗
	int Pd;//护甲
	int MaxBlood;//当前最大血量
	int MaxEnergy;//当前最大能量
	int Blood;//当前血量
	int Energy;//能量
	double Speed;//速度
	int Pa;//物理输出
	int Ma;//魔法输出
	int CrRate;//暴击率
	double Frequence;//攻击速率 
	

	int RewardM;//杀死的赏金
	int  RewardE;//杀死的经验

	int LastTime;//持续时间 为0说明是一次性效果
	int AttackRange;//攻击范围 
};
struct Special
{
	int SuckBlood;
	int SuckMagic;
	int PhysicalPercent;
	int MagicPercent;
};
struct Injury
{
	Attribute* BaseAttack;
	Special* special;
};
struct Buff {
	int TimeLeft;//剩余持续时间
	Attribute Effection;
	Special special;
	Buff* Prev;
	Buff* Next;
};

//以下是物品类
class Skill
{
	Attribute BaseValue;//基础值
	Attribute IncValue;//增长值
	Buff BaseBValue;//基础值
	Buff IncBValue;//增长值
	int level;
public:
	Hero * Owner;//拥有者
	string name;
	Attribute * Effection;
	Buff* buff;//如果不是buff就设为null
	int StockNumber;
	int index;//在英雄技能栏中的位置
	bool JustFlushed;//刚好被刷新
	int CD;//技能CD
	int LastCD;//剩余CD
	int EnergyConsume;//能量消耗
	double ADR;//技能AD加成
	double APR;//技能AP加成
	int Range() { return Effection->AttackRange; }
	void LevelUp();
	void SetLevel(int DirectLevel);
	void PrintName();
	void SetSkill(Attribute basevalue, Attribute incvalue, Buff baseBvalue, Buff incBvalue);
	Skill() { Effection = new Attribute; buff = new Buff; }
};
class Equipment
{
	Injury EquipEffection;
public:
	int StockNumber;
	string name;
	Injury GetEffection() { return EquipEffection; }
	void PrintName(int index);
	Equipment() {};
	void Set(Injury, string);
};
class Consumable
{
	Buff* ConsumableEffetion;//消耗品效果
public:
	bool Range;
	int StockNumber;
	string name;
	Buff* Effect() { return ConsumableEffetion; }
	CAMP EffectionCamp() { return ConsumableEffetion->Effection.Camp; }
	void PrintName(int index);
	void PrintName(int index,int);//这是给强化书的版本
	void SetConsumable(bool range, Buff* effectionC, string Name) { ConsumableEffetion = effectionC; Range = range; name = Name; }
};

#endif