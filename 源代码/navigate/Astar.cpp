#include"Navigate.h"
Astar::Astar(Astar* father, COORD loc, COORD des)
{
	Father = father;
	Loc = loc;
	if (Father)
		G = Father->G + (Father->Loc.X == Loc.X) ? 20 : ((Father->Loc.Y == Loc.Y) ? 10 : 22);
	else
		G = 0;
	des.X = (des.X >= Loc.X) ? des.X - Loc.X : Loc.X - des.X;
	des.Y = (des.Y >= Loc.Y) ? des.Y - Loc.Y : Loc.Y - des.Y;
	H = 10 * des.X + 20*des.Y;
	F = G + H;
	IsPath = false;
}