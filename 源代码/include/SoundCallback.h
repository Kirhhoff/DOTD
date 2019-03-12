#ifndef SOUNDCALLBACK_H
#define SOUNDCALLBACK_H

#include"SystemDependency.h"
unsigned WINAPI PlayMoveSound(LPVOID lpParameter);
unsigned WINAPI PlayAttackSound(LPVOID lpParameter);
unsigned WINAPI PlayAttackedSound(LPVOID lpParameter);
unsigned WINAPI PlayBoughtSound(LPVOID lpParameter);
unsigned WINAPI PlaySelectedSound(LPVOID lpParameter);
unsigned WINAPI GPPlayDieSound(LPVOID lpParameter);
unsigned WINAPI AIPlayDieSound(LPVOID lpParameter);
unsigned WINAPI PlayLackSound(LPVOID lpParameter);
unsigned WINAPI PlayClickSound(LPVOID lpParameter);
unsigned WINAPI PlayBackgroundSound(LPVOID lpParameter);
unsigned WINAPI PlayMouseInOut(LPVOID lpParameter);
unsigned WINAPI PlayRoundSound(LPVOID lpParameter);
unsigned WINAPI PlaySystemSound(LPVOID lpParameter);

#endif