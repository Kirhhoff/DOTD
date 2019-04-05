#ifndef STATUSCALLBACK_H
#define STATUSCALLBACK_H

#include"SystemDependency.h"
unsigned WINAPI UpdateGPBuff(LPVOID lpParameter);
unsigned WINAPI UpdateGPDeBuff(LPVOID lpParameter);
unsigned WINAPI UpdateAIBuff(LPVOID lpParameter);
unsigned WINAPI UpdateAIDeBuff(LPVOID lpParameter);
unsigned WINAPI FlushGPSkill(LPVOID lpParameter);
unsigned WINAPI FlushAISkill(LPVOID lpParameter);

#endif