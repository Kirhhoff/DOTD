#ifndef UNITVARIABLE_H
#define UNITVARIABLE_H

#include"Hero.h"
#include"Element.h"
#include"SystemDependency.h"
#include"GameSetting.h"
extern GPHero HeroStock[GP_STOCK + 1];//GP英雄
extern AIHero MonsterStock[AI_STOCK + 1];//AI英雄
extern DWORD GPApperanceStock[GP_STOCK + 1];//GP英雄颜色
extern string GPNameStock[GP_STOCK + 1];//GP英雄名字
extern string AINameStock[AI_STOCK + 1];//AI英雄名字
extern Attribute GPBAttributeStock[GP_STOCK+1];//GP英雄基础属性
extern Attribute GPIAtrributeStock[GP_STOCK+1];//GP英雄增长属性
extern Attribute AIBAttributeStock[AI_STOCK+1];//AI英雄基础属性
extern Attribute AIIAttributeStock[AI_STOCK+1];//AI英雄基础属性
extern Special GPBSpecialStock[GP_STOCK + 1];//GP英雄基础special
extern Special GPISpecialStock[GP_STOCK + 1];//GP英雄增长special
extern Special AIBSpecialStock[AI_STOCK + 1];//AI英雄基础special
extern Special AIISpecialStock[AI_STOCK + 1];//AI英雄基础special

extern Skill GPSkillStock[GP_STOCK*MAX_HERO_SKILL_NUM+1];//GP英雄技能
extern Skill AISkillStock[AI_STOCK*MAX_MONSTER_SKILL_NUM+1];//AI英雄技能
extern Attribute GPSkillAttributeBStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP英雄技能基础属性
extern Attribute GPSkillAttributeIStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP英雄技能增长属性
extern Attribute AISkillAttributeBStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI英雄技能基础属性
extern Attribute AISkillAttributeIStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI英雄技能增长属性
extern Buff GPSkillBuffBStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP技能Buff基础属性
extern Buff GPSkillBuffIStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP技能Buff增长属性
extern Buff AISkillBuffBStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI技能Buff基础属性
extern Buff AISkillBuffIStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI技能Buff增长属性

extern Equipment EquipmentStock[EQUIPMENT_STOCK];
extern Consumable ConsumableStock[CONSUMABLE_STOCK];
extern Consumable EnhanceBookStock[ENHANCEBOOK_STOCK];
extern string CitadelAttackedSounds[CITADEL_ATTACKED_SOUND_NUM];

#endif