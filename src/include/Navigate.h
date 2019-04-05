#ifndef NAVIGATE_H
#define NAVIGATE_H

#include"SystemDependency.h"
class Astar
{
public:
	Astar * Father;
	Astar* Next;
	COORD Loc;
	bool IsPath;
	int F;
	int G;
	int H;
	Astar(Astar* father, COORD loc, COORD des);
};

class Aector
{
	enum { AECTOR_DEFAULT_SIZE = 20 };
	int CurMaxSize;
	int CurSize;
	Astar** Content;
public:
	Aector();
	~Aector();
	void Add(Astar* NewSatar);
	bool find(COORD Loc);
	void ReAector();
	void Clean();
};
class MinHeap
{
	enum { MINHEAP_DEFAULT_SIZE = 50 };
	Astar** Content;
	int CurMaxSize;
	int CurSize;
	void Swap(int i, int j);
	int FoundIndex;
public:
	MinHeap();
	~MinHeap();
	void insert(Astar* NewAstar);
	void HeapifyUp(int index);
	void HeapifyDown(int index);
	void Heapify();
	Astar* remove();
	Astar* find(COORD);
	void ReHeap();
	void Clean();
};

#endif