#include"SoundCallback.h"
#include"Hero.h"
#include"ControlVariable.h"
#include"UnitVariable.h"

unsigned WINAPI PlayMoveSound(LPVOID lpParameter)
{
	GPHero* Tmp = (GPHero*)lpParameter;
	mciSendString(Tmp->MoveSounds[++t%MAX_SOUND_NUM].c_str(), NULL, 0, NULL);
	mciSendString("play aa wait", NULL, 0, NULL);
	mciSendString("close aa", NULL, 0, NULL);
	return 0;
}
unsigned WINAPI PlayAttackSound(LPVOID lpParameter)
{
	GPHero* Tmp = (GPHero*)lpParameter;
	
	mciSendString(Tmp->AttackSounds[++t%(MAX_SOUND_NUM-1)].c_str(), NULL, 0, NULL);
	mciSendString("play aa wait", NULL, 0, NULL);
	mciSendString("close aa", NULL, 0, NULL);
	return 0;
}
unsigned WINAPI PlayAttackedSound(LPVOID lpParameter)
{
	GPHero* Tmp = (GPHero*)lpParameter;
	mciSendString(Tmp->AttackedSound.c_str(), NULL, 0, NULL);
	mciSendString("play aa wait", NULL, 0, NULL);
	mciSendString("close aa", NULL, 0, NULL);
	return 0;
}
unsigned WINAPI PlayBoughtSound(LPVOID lpParameter)
{
	GPHero* Tmp = (GPHero*)lpParameter;
	mciSendString(Tmp->BoughtSound.c_str(), NULL, 0, NULL);
	mciSendString("play aa wait", NULL, 0, NULL);
	mciSendString("close aa", NULL, 0, NULL);
	return 0;
}
unsigned WINAPI PlaySelectedSound(LPVOID lpParameter)
{
	Hero* Tmp = (Hero*)lpParameter;
	mciSendString(Tmp->SelectedSound[++t%MAX_SOUND_NUM].c_str(), NULL, 0, NULL);
	mciSendString("play aa wait", NULL, 0, NULL);
	mciSendString("close aa", NULL, 0, NULL);
	return 0;
}
unsigned WINAPI GPPlayDieSound(LPVOID lpParameter)
{
	GPHero* Tmp = (GPHero*)lpParameter;
	mciSendString(Tmp->DieSound.c_str(), NULL, 0, NULL);
	mciSendString("play aa wait", NULL, 0, NULL);
	mciSendString("close aa", NULL, 0, NULL);
	mciSendString(Tmp->DeathAnnounce.c_str(), NULL, 0, NULL);
	mciSendString("play aa wait", NULL, 0, NULL);
	mciSendString("close aa", NULL, 0, NULL);
	return 0;
}
unsigned WINAPI AIPlayDieSound(LPVOID lpParameter)
{
	AIHero* Tmp = (AIHero*)lpParameter;
	mciSendString(Tmp->DieSound.c_str(), NULL, 0, NULL);
	mciSendString("play aa wait", NULL, 0, NULL);
	mciSendString("close aa", NULL, 0, NULL);
	return 0;
}
unsigned WINAPI PlayLackSound(LPVOID lpParameter)
{
	GPHero* Tmp = (GPHero*)lpParameter;
	mciSendString(Tmp->LackSound.c_str(), NULL, 0, NULL);
	mciSendString("play aa wait", NULL, 0, NULL);
	mciSendString("close aa", NULL, 0, NULL);
	return 0;
}
unsigned WINAPI PlayClickSound(LPVOID lpParameter)
{
	mciSendString("open 开始.wav alias aa", NULL, 0, NULL);
	mciSendString("play aa wait", NULL, 0, NULL);
	mciSendString("close aa", NULL, 0, NULL);
	return 0;
}
unsigned WINAPI PlayBackgroundSound(LPVOID lpParameter)
{	
	while (1)
	{
			mciSendString("open B1.mp3 alias aa", NULL, 0, NULL);
			mciSendString("play aa wait", NULL, 0, NULL);
			mciSendString("close aa", NULL, 0, NULL);
			mciSendString("open B2.mp3 alias aa", NULL, 0, NULL);
			mciSendString("play aa wait", NULL, 0, NULL);
			mciSendString("close aa", NULL, 0, NULL);
			mciSendString("open B3.mp3 alias aa", NULL, 0, NULL);
			mciSendString("play aa wait", NULL, 0, NULL);
			mciSendString("close aa", NULL, 0, NULL);
	}

		return 0;
}
unsigned WINAPI PlayMouseInOut(LPVOID lpParameter)
{
	int Token = (int)lpParameter;
	switch (Token)
	{
	case MouseIn:
	{
		PlaySound("移入.wav", NULL, SND_FILENAME | SND_ASYNC|SND_NOSTOP);
	}
	break;
	case MouseOut:
	{
		PlaySound("移出.wav", NULL, SND_FILENAME | SND_ASYNC| SND_NOSTOP);
	}
	break;
	case Ready:
	{
		PlaySound("预备.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	break;
	case GO:
	{
		PlaySound("开始.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	break;
	default:
		break;

	}

	return 0;
}
unsigned WINAPI PlayRoundSound(LPVOID lpParameter)
{
	int Token = (int)lpParameter;
	switch (Token)
	{
	case RoundEnd:
	{
		mciSendString("open 本轮结束.wav alias aa", NULL, 0, NULL);
		mciSendString("play aa wait", NULL, 0, NULL);
		mciSendString("close aa", NULL, 0, NULL);
	}
	break;
	case RoundStart:
	{
		mciSendString("open 本轮开始.wav alias aa", NULL, 0, NULL);
		mciSendString("play aa wait", NULL, 0, NULL);
		mciSendString("close aa", NULL, 0, NULL);
	}
	break;
	default:
		break;

	}
	return 0;

}
unsigned WINAPI PlaySystemSound(LPVOID lpParameter)
{
	int Token = (int)lpParameter;
	switch (Token)
	{
	case Invalid:
	{
		mciSendString("open 无效.wav alias aa", NULL, 0, NULL);
		mciSendString("play aa wait", NULL, 0, NULL);
		mciSendString("close aa", NULL, 0, NULL);
	}
	break;
	case Click:
	{
		mciSendString("open 开始.wav alias aa", NULL, 0, NULL);
		mciSendString("play aa wait", NULL, 0, NULL);
		mciSendString("close aa", NULL, 0, NULL);
	}
	break;
	case HeroLevelUp:
	{
		mciSendString("open 升级.wav alias aa", NULL, 0, NULL);
		mciSendString("play aa wait", NULL, 0, NULL);
		mciSendString("close aa", NULL, 0, NULL);
	}
	break;
	case TriggerSkill:
	{
		mciSendString("open 释放技能.wav alias aa", NULL, 0, NULL);
		mciSendString("play aa wait", NULL, 0, NULL);
		mciSendString("close aa", NULL, 0, NULL);
	}
	break; 
	case TriggerConsumable:
	{
		mciSendString("open 使用消耗品.wav alias aa", NULL, 0, NULL);
		mciSendString("play aa wait", NULL, 0, NULL);
		mciSendString("close aa", NULL, 0, NULL);
	}
	break;
	case TriggerEnhanceBook:
	{
		mciSendString("open 强化书.wav alias aa", NULL, 0, NULL);
		mciSendString("play aa wait", NULL, 0, NULL);
		mciSendString("close aa", NULL, 0, NULL);
	}
	break;
	case CitadelAttacked:
	{
		srand(time(NULL));
		srand(rand() + 71);
		mciSendString(CitadelAttackedSounds[rand()% CITADEL_ATTACKED_SOUND_NUM].c_str(), NULL, 0, NULL);
		mciSendString("play aa wait", NULL, 0, NULL);
		mciSendString("close aa", NULL, 0, NULL);
	}
	default:
		break;
	}
	return 0;

}