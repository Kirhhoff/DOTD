#ifndef MOUSEFSM_H
#define MOUSEFSM_H

#include"SystemDependency.h"
class MouseOperateState
{
protected:
	virtual void ShowDetail(int FTYPE, int REALINDEX);
	virtual void TriggerFunction(COORD Destination) {};
	virtual void SolveMouseReleased(COORD Destination) = 0;
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent) =0;
	static bool LeftButtonPressed;
	virtual ~MouseOperateState() {};
};
class FormalState :virtual public MouseOperateState
{
	virtual void TriggerFunction(COORD Destination);
	virtual void SolveMouseReleased(COORD Destination) ;
	virtual void SolveMouseMoved(COORD MovedLoc) ;
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
	virtual ~FormalState() {};
};
class SkillingState:virtual public MouseOperateState
{
	virtual void SolveMouseReleased(COORD Destination);
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
	virtual ~SkillingState() {};
};
class TransportingState :virtual public MouseOperateState
{
	virtual void SolveMouseReleased(COORD Destination);
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
	virtual ~TransportingState() {};
};
class ShoppingState:virtual public MouseOperateState
{
	virtual void ShowDetail(int FTYPE, int REALINDEX);
	virtual void TriggerFunction(COORD Destination);
	virtual void SolveMouseReleased(COORD Destination);
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
	virtual ~ShoppingState() {};
};








class MenuState :public MouseOperateState
{
	virtual void SolveMouseReleased(COORD Destination) {};
	virtual void SolveMouseMoved(COORD MovedLoc)=0;
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent) = 0;
	virtual ~MenuState() {};
};
class MFormalState :public MenuState
{
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
	virtual ~MFormalState() {};
};
class M1 :public MenuState
{
	virtual void SolveMouseReleased(COORD Destination) {};
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
	virtual ~M1() {};
	static short LastY;
};
class M2 :public MenuState
{
	virtual void SolveMouseReleased(COORD Destination) {};
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
	virtual ~M2() {};
	static short LastY;
};
class M3 :public MenuState
{
	virtual void SolveMouseReleased(COORD Destination) {};
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
	virtual ~M3() {};
	static short LastY;
};
class M4 :public MenuState
{
	virtual void SolveMouseReleased(COORD Destination) {};
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
	virtual ~M4() {};
	static short LastY;
};
class M0 :public MenuState
{
	virtual void SolveMouseReleased(COORD Destination);
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
	virtual ~M0() {};
};

#endif