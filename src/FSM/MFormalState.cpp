#include"MouseFSM.h"
#include"SoundCallback.h"
#include"MenuView.h"
#include"ConsoleView.h"
#include"Menu.h"
#include"APIVariable.h"
#include"GameView.h"
#include"ControlVariable.h"

void MFormalState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	if (NewEvent.dwEventFlags == MOUSE_MOVED)
		SolveMouseMoved(NewEvent.dwMousePosition);
}
void MFormalState::SolveMouseMoved(COORD MovedLoc)
{
	if (MovedLoc.X >= XOTD && MovedLoc.X < (XOTD + 30))
	{
		TmpMenuState = M1State;
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMouseInOut, (void*)(int(MouseIn)), 0, NULL));
	}
	else if (MovedLoc.X >= DXTD && MovedLoc.X < (DXTD + 30))
	{
		TmpMenuState = M2State;
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMouseInOut, (void*)(int(MouseIn)), 0, NULL));
	}
	else if (MovedLoc.X >= DOXD && MovedLoc.X < (DOXD + 30))
	{
		TmpMenuState = M3State;
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMouseInOut, (void*)(int(MouseIn)), 0, NULL));
	}
	else if (MovedLoc.X >= DOTX && MovedLoc.X < (DOTX + 30))
	{
		TmpMenuState = M4State;
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMouseInOut, (void*)(int(MouseIn)), 0, NULL));
	}
	else if (MovedLoc.X >= OK_CLEAN)
	{
		for (short y = 0; y < SCREEN_HEIGHT; y++)
			FillConsoleOutputAttribute(hOut, CitadelColor, SCREEN_WIDTH - OK_CLEAN, { OK_CLEAN,y }, &num);
		O(OK_SIZE, { OK_X,YK }, DIVIDER_COLOR);
		K(OK_SIZE, { OK_X,OY }, DIVIDER_COLOR);
		TmpMenuState = M0State;
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMouseInOut, (void*)(int(Ready)), 0, NULL));
	}
}
