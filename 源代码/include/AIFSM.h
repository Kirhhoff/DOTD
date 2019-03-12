#ifndef AIFSM_H
#define AIFSM_H

#include"SystemDependency.h"
#include"HeroForward.h"
class AIState
{
protected:
	SYSTEMTIME BeginTest;
	SYSTEMTIME EndTest;
	COORD LastDestination;
public:
	AIHero * Object;
	virtual void Act()=0;
	virtual ~AIState() {};
};
class AIStillState:virtual public AIState
{
public:
	bool JustAttacked;
	virtual void Act();
	virtual ~AIStillState() {};
};
class AIPChaseState:virtual public AIState
{
public:
	virtual void Act();
	virtual ~AIPChaseState() {};

};
class AINChaseState :virtual public AIState
{
public:
	virtual void Act();
	virtual ~AINChaseState() {};
};

#endif