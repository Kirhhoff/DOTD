#include"Element.h"
#define MAX_THING_NUM   6;//最多持有的(强化书/消耗品/装备/我方英雄技能)数量
#define MAX_MONSTER_SKILL_NUM   3;//辅导员最多持有的技能数量
#define SKILL_CHAR   '#';//技能填充字符
#define ATTACK_CHAR   '#';//攻击填充字符
#define EQUIPMENT_STOCK   6;//装备种类数
#define CONSUMABLE_STOCK   6;//消耗品种类数
#define ENHANCEBOOK_STOCK   6;//强化书种类书
#define SKILL_STOCK   60;//技能
#define GP_STOCK   4;//英雄种类数
#define AI_STOCK   3;//辅导员种类数
#define SELL_RATE   6;//折价率
#define INTERVAL   15;//相邻两轮的游戏时间间隔
#define INC_HERO_EXPERICAL 500;//升级经验增长值
#define INC_HERO_PRICE 1000;//英雄价格增长值
#define SecondMonsterTurnUp 5;//第二个辅导员出现的轮数
#define ThirdMonsterTurnUp 10;//第三个辅导员出现的轮数
#define RoundsToGetMoreOneEqipment 3;//隔几轮辅导员拿到一件新的装备
#define TestTime 1000;//检测攻击的时间长度/毫秒计

#define MAX_HERO_SKILL_NUM   6;
#define MAX_HERO_LEVEL   10;
#define MAX_THING_NUM_H 6;
#define MAX_SOUND_NUM   4;
#define MAX_MOVE_SOUND_NUM 8;
#define MAX_ATTACK_SOUND_NUM 8;
#define CITADEL_ATTACKED_SOUND_NUM   6;


