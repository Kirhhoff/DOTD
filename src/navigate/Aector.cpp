#include"Navigate.h"
#include"Reload.h"
Aector::Aector():CurMaxSize(AECTOR_DEFAULT_SIZE),CurSize(0)
{
	Content = new Astar*[CurMaxSize] {};
}
Aector::~Aector()
{
	Clean();
	delete[] Content;
}
void Aector::ReAector()
{
	Astar** Bigger = new Astar*[2 * CurMaxSize];
	for (int i = 0; i < CurMaxSize; i++)
		Bigger[i] = Content[i];
	delete[] Content;
	Content = Bigger;
	CurMaxSize *= 2;
}
void Aector::Add(Astar* Newstar)
{
	if (CurSize == CurMaxSize)
		ReAector();
	Content[CurSize++] = Newstar;
}
bool Aector::find(COORD Loc)
{
	for (int i = 0; i < CurSize; i++)
		if (Content[i]->Loc == Loc)
			return true;
	return false;
}
void Aector::Clean()
{
	for (int i = 0; i < CurSize; i++)
		if(!(Content[i]->IsPath))
			delete Content[i];
	CurSize = 0;
}