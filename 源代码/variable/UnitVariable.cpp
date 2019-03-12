#include"UnitVariable.h"

GPHero HeroStock[GP_STOCK + 1];//GP英雄
AIHero MonsterStock[AI_STOCK + 1];//AI英雄
DWORD GPApperanceStock[GP_STOCK + 1];//GP英雄颜色
string GPNameStock[GP_STOCK + 1];//GP英雄名字
string AINameStock[AI_STOCK + 1];//AI英雄名字
Attribute GPBAttributeStock[GP_STOCK+1];//GP英雄基础属性
Attribute GPIAtrributeStock[GP_STOCK+1];//GP英雄增长属性
Attribute AIBAttributeStock[AI_STOCK+1];//AI英雄基础属性
Attribute AIIAttributeStock[AI_STOCK+1];//AI英雄基础属性
Special GPBSpecialStock[GP_STOCK + 1];//GP英雄基础special
Special GPISpecialStock[GP_STOCK + 1];//GP英雄增长special
Special AIBSpecialStock[AI_STOCK + 1];//AI英雄基础special
Special AIISpecialStock[AI_STOCK + 1];//AI英雄基础special

Skill GPSkillStock[GP_STOCK*MAX_HERO_SKILL_NUM+1];//GP英雄技能
Skill AISkillStock[AI_STOCK*MAX_MONSTER_SKILL_NUM+1];//AI英雄技能
Attribute GPSkillAttributeBStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP英雄技能基础属性
Attribute GPSkillAttributeIStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP英雄技能增长属性
Attribute AISkillAttributeBStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI英雄技能基础属性
Attribute AISkillAttributeIStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI英雄技能增长属性
Buff GPSkillBuffBStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP技能Buff基础属性
Buff GPSkillBuffIStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP技能Buff增长属性
Buff AISkillBuffBStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI技能Buff基础属性
Buff AISkillBuffIStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI技能Buff增长属性

Equipment EquipmentStock[EQUIPMENT_STOCK];
Consumable ConsumableStock[CONSUMABLE_STOCK];
Consumable EnhanceBookStock[ENHANCEBOOK_STOCK];
string CitadelAttackedSounds[CITADEL_ATTACKED_SOUND_NUM];