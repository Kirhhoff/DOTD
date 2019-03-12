#include"Menu.h"
#include"MouseFSM.h"
#include"MenuView.h"
#include"APIVariable.h"
#include"GameView.h"
#include"Dameon.h"
#include"ControlVariable.h"

void D(short size, COORD Start, DWORD COLOR)
{
	short Hunit = size;
	short Wunit = 2 * Hunit;
	for (short y = 0; y < Hunit; y++)
	{
		FillConsoleOutputAttribute(hOut, COLOR, 2 * Wunit + 2 * y, { Start.X ,y + Start.Y }, &num);
		FillConsoleOutputAttribute(hOut, COLOR, 2 * Wunit + 2 * y, { Start.X , Start.Y + 3 * Hunit - y - 1 }, &num);
		FillConsoleOutputAttribute(hOut, COLOR, Wunit, { Start.X ,y + Start.Y + Hunit }, &num);
		FillConsoleOutputAttribute(hOut, COLOR, Wunit, { Start.X + 2 * Wunit ,y + Start.Y + Hunit }, &num);
	}
}
void O(short size, COORD Start, DWORD COLOR)
{
	short Hunit = size;
	short Wunit = 2 * Hunit;
	for (short y = 0; y < Hunit; y++)
	{
		FillConsoleOutputAttribute(hOut, COLOR, Wunit + 4 * y, { Start.X + Wunit - 2 * y,y + Start.Y }, &num);
		FillConsoleOutputAttribute(hOut, COLOR, Wunit + 4 * y, { Start.X + Wunit - 2 * y , Start.Y + 3 * Hunit - y - 1 }, &num);
		FillConsoleOutputAttribute(hOut, COLOR, Wunit, { Start.X ,y + Start.Y + Hunit }, &num);
		FillConsoleOutputAttribute(hOut, COLOR, Wunit, { Start.X + 2 * Wunit ,y + Start.Y + Hunit }, &num);
	}
}
void T(short size, COORD Start, DWORD COLOR)
{
	short Hunit = size;
	short Wunit = 2 * Hunit;
	for (short y = 0; y < Hunit; y++)
	{
		FillConsoleOutputAttribute(hOut, COLOR, 3 * Wunit, { Start.X  ,y + Start.Y }, &num);
		FillConsoleOutputAttribute(hOut, COLOR, Wunit, { Start.X + Wunit,y + Start.Y + Hunit }, &num);
		FillConsoleOutputAttribute(hOut, COLOR, Wunit, { Start.X + Wunit ,y + Start.Y + 2 * Hunit }, &num);
	}
}
void K(short size, COORD Start, DWORD COLOR)
{
	short Hunit = size;
	short Wunit = 2 * Hunit;
	for (short y = 0; y < Hunit; y++)
	{
		FillConsoleOutputAttribute(hOut, COLOR, Wunit - 2 * y, { Start.X + 2 * Wunit ,y + Start.Y }, &num);
		FillConsoleOutputAttribute(hOut, COLOR, Wunit - 2 * y, { Start.X + 2 * Wunit , Start.Y + 3 * Hunit - y - 1 }, &num);
		FillConsoleOutputAttribute(hOut, COLOR, Wunit, { Start.X  ,y + Start.Y }, &num);
		FillConsoleOutputAttribute(hOut, COLOR, 2 * Wunit, { Start.X ,y + Start.Y + Hunit }, &num);
		FillConsoleOutputAttribute(hOut, COLOR, Wunit, { Start.X ,y + Start.Y + 2 * Hunit }, &num);
	}
}
void MainMenu()
{
	D(DOTD_SIZE, { XOTD,DOTD_Y }, Illidan_Stormrage);
	O(DOTD_SIZE, { DXTD,DOTD_Y }, Tyrande_Whisperwind);
	T(DOTD_SIZE, { DOXD,DOTD_Y }, Cairne_Bloodhoof);
	D(DOTD_SIZE, { DOTX,DOTD_Y }, Grom_Hellscream);
	O(OK_SIZE, { OK_X,YK }, CitadelColor);
	K(OK_SIZE, { OK_X,OY }, CitadelColor);
	MFState = new MFormalState;
	M1State = new M1;
	M2State = new M2;
	M3State = new M3;
	M4State = new M4;
	M0State = new M0;
	CurMenuState = TmpMenuState = MFState;

	while (ReadConsoleInput(hIn, Inputs, MAX_INPUT_RECORD, &InputOneTime) && !Go)
	{
		for (int i = 0; i < InputOneTime; i++)
			if (Inputs[i].EventType == MOUSE_EVENT)//鼠标事件
				HandleMenuInput(Inputs[i].Event.MouseEvent);
		Sleep(40);
	}
}
