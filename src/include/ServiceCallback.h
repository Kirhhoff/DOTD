#ifndef SERVICECALLBACK_H
#define SERVICECALLBACK_H

#include"SystemDependency.h"
unsigned WINAPI LoadGPHero(LPVOID lpParameter);//加载一个新英雄的例程
unsigned WINAPI LoadAIHero(LPVOID lpParameter);//加载一个新英雄的例程
unsigned WINAPI Timer(LPVOID lpParameter);

#endif