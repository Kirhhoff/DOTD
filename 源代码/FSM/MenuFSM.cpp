#include"MouseFSM.h"
#include"ConsoleView.h"
#include"APIVariable.h"
#include"SoundCallback.h"
#include"GameView.h"
#include"MenuView.h"
#include"Menu.h"
#include"ControlVariable.h"
short M1::LastY = DOTD_Y;
short M2::LastY = DOTD_Y;
short M3::LastY = DOTD_Y;
short M4::LastY = DOTD_Y;
void M1::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	if (NewEvent.dwEventFlags == MOUSE_MOVED)
		SolveMouseMoved(NewEvent.dwMousePosition);
}
void M1::SolveMouseMoved(COORD MovedLoc)
{
	if (MovedLoc.X >= XOTD && MovedLoc.X < (XOTD + 30))
	{
		for (short y = LastY; y < LastY + 15; y++)
			FillConsoleOutputAttribute(hOut, 0, 30, { XOTD,y }, &num);
		short y1;
		short y2 = MovedLoc.Y + 15;
		if (y2 > SCREEN_HEIGHT)
		{
			y1 = SCREEN_HEIGHT - 15;
			y2 = SCREEN_HEIGHT;
		}
		else
			y1 = MovedLoc.Y;
		D(DOTD_SIZE, { XOTD,y1 }, Illidan_Stormrage);
		LastY = y1;
	}
	else
	{
		TmpMenuState = MFState;
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMouseInOut, (void*)(int(MouseOut)), 0, NULL));
	}
}
void M2::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	if (NewEvent.dwEventFlags == MOUSE_MOVED)
		SolveMouseMoved(NewEvent.dwMousePosition);
}
void M2::SolveMouseMoved(COORD MovedLoc)
{
	if (MovedLoc.X >= DXTD && MovedLoc.X < (DXTD + 30))
	{
		for (short y = LastY; y < LastY + 15; y++)
			FillConsoleOutputAttribute(hOut, 0, 30, { DXTD,y }, &num);
		short y1;
		short y2 = MovedLoc.Y + 15;
		if (y2 > SCREEN_HEIGHT)
		{
			y1 = SCREEN_HEIGHT - 15;
			y2 = SCREEN_HEIGHT;
		}
		else
			y1 = MovedLoc.Y;
		O(DOTD_SIZE, { DXTD,y1 }, Tyrande_Whisperwind);
		LastY = y1;
	}
	else
	{
		TmpMenuState = MFState;
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMouseInOut, (void*)(int(MouseOut)), 0, NULL));
	}
}
void M3::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	if (NewEvent.dwEventFlags == MOUSE_MOVED)
		SolveMouseMoved(NewEvent.dwMousePosition);
}
void M3::SolveMouseMoved(COORD MovedLoc)
{
	if (MovedLoc.X >= DOXD && MovedLoc.X < (DOXD + 30))
	{
		for (short y = LastY; y < LastY + 15; y++)
			FillConsoleOutputAttribute(hOut, 0, 30, { DOXD,y }, &num);
		short y1;
		short y2 = MovedLoc.Y + 15;
		if (y2 > SCREEN_HEIGHT)
		{
			y1 = SCREEN_HEIGHT - 15;
			y2 = SCREEN_HEIGHT;
		}
		else
			y1 = MovedLoc.Y;
		T(DOTD_SIZE, { DOXD,y1 }, Cairne_Bloodhoof);
		LastY = y1;
	}
	else
	{
		TmpMenuState = MFState;
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMouseInOut, (void*)(int(MouseOut)), 0, NULL));
	}
}
void M4::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	if (NewEvent.dwEventFlags == MOUSE_MOVED)
		SolveMouseMoved(NewEvent.dwMousePosition);
}
void M4::SolveMouseMoved(COORD MovedLoc)
{
	if (MovedLoc.X >= DOTX && MovedLoc.X < (DOTX + 30))
	{
		for (short y = LastY; y < LastY + 15; y++)
			FillConsoleOutputAttribute(hOut, 0, 30, { DOTX,y }, &num);
		short y1;
		short y2 = MovedLoc.Y + 15;
		if (y2 > SCREEN_HEIGHT)
		{
			y1 = SCREEN_HEIGHT - 15;
			y2 = SCREEN_HEIGHT;
		}
		else
			y1 = MovedLoc.Y;
		D(DOTD_SIZE, { DOTX,y1 }, Grom_Hellscream);
		LastY = y1;
	}
	else
	{
		TmpMenuState = MFState;
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMouseInOut, (void*)(int(MouseOut)), 0, NULL));
	}
}
void M0::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	switch (NewEvent.dwEventFlags)
	{
	case 0:
	{
		if (NewEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMouseInOut, (void*)(int(GO)), 0, NULL));
		else if (NewEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			;
		else
			SolveMouseReleased(NewEvent.dwMousePosition);
	}
	break;
	case MOUSE_MOVED:
		SolveMouseMoved(NewEvent.dwMousePosition);
	break;
	default:
		break;
	}
}
void M0::SolveMouseMoved(COORD MovedLoc)
{
	if (MovedLoc.X < OK_CLEAN)
	{
		for (short y = 0; y < SCREEN_HEIGHT; y++)
			FillConsoleOutputAttribute(hOut, 0, SCREEN_WIDTH - OK_CLEAN, { OK_CLEAN,y }, &num);
		O(OK_SIZE, { OK_X,YK }, CitadelColor);
		K(OK_SIZE, { OK_X,OY }, CitadelColor);
		TmpMenuState = MFState;
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMouseInOut, (void*)(int(Ready)), 0, NULL));
	}
}
void M0::SolveMouseReleased(COORD Destination)
{
	if (Destination.X >= OK_CLEAN)
		Go = true;
}
