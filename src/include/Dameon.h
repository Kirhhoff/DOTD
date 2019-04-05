#ifndef DAMEON_H
#define DAMEON_H

#include"SystemDependency.h"
#include"Enumeration.h"
void ShowGameProgress();
void EraseGameProgress();
void BuyHero(int HeroNumber);
void EraseThing(TYPE T, int index);//T可以是SKILL CONSUMBALE EQUIPMENT index范围0-5
void BeginTransportOrUpSkill(COORD Destination);
void GameOver();


void HandleMenuInput(MOUSE_EVENT_RECORD NewEvent);
void HandleKeyInput(KEY_EVENT_RECORD NewEvent) ;
void HandleMouseInput(MOUSE_EVENT_RECORD NewEvent);

#endif