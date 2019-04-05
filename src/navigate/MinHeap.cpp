#include"Navigate.h"
#include"Reload.h"
MinHeap::MinHeap():CurMaxSize(MINHEAP_DEFAULT_SIZE),CurSize(0),FoundIndex(0)
{
	Content = new Astar*[CurMaxSize+1] {};
}
MinHeap::~MinHeap()
{
	Clean();
	delete[] Content;
}
void MinHeap::ReHeap() 
{
	Astar** Bigger = new Astar*[CurMaxSize * 2+1];
	for (int i = 1; i <= CurMaxSize; i++)
		Bigger[i] = Content[i];
	delete[] Content;
	Content = Bigger;
	CurMaxSize *= 2;
}
void MinHeap::Swap(int i, int j)
{
	auto tmp = Content[i];
	Content[i] = Content[j];
	Content[j] = tmp;
}
Astar* MinHeap::find(COORD Loc)
{
	for (int i = 1; i < CurSize; i++)
		if (Content[i]->Loc == Loc)
		{
			FoundIndex = i;
			return Content[i];
		}
	return 0;
}
Astar* MinHeap::remove()
{
	if (!CurSize)
		return 0;
	auto tmp = Content[1];
	Content[1] = Content[CurSize--];
	if (CurSize)
		HeapifyDown(1);
	return tmp;
}
void MinHeap::insert(Astar* Newstar)
{
	if (CurSize == CurMaxSize)
		ReHeap();
	Content[++CurSize] = Newstar;
	HeapifyUp(CurSize);
}
void MinHeap::Heapify()
{
	if (FoundIndex == 1)
		HeapifyDown(1);
	else
	{
		if (Content[FoundIndex]->F < Content[FoundIndex / 2]->F)
			HeapifyUp(FoundIndex);
		else
			HeapifyDown(FoundIndex);
	}
}
void MinHeap::HeapifyDown(int index)
{
	for (;index*2+1<=CurSize;)
	{
		if ((Content[index]->F <= Content[index * 2]->F) && (Content[index]->F <= Content[index * 2 + 1]->F))//如果两个子节点均不小于该节点 则无需维护
			break;
		else//那么该节点至少大于两个子节点中的一个
		{
			if (Content[index * 2]->F <= Content[index * 2 + 1]->F)//当左节点较小时
			{
				Swap(index, index * 2);//那么当前节点的位子应该让给最小的左节点
				index = index * 2;
			}
			else//当右节点较小时
			{
				Swap(index, index * 2 + 1);//那么当前节点的位子应该让给最小的右节点
				index = index * 2 + 1;
			}
		}
	}
	if (index * 2 > CurSize)
		return;
	else
		if (Content[index]->F > Content[index * 2]->F)
			Swap(index, index * 2);
}
void MinHeap::HeapifyUp(int index)
{
	for (;index/2;)
	{
		if (Content[index]->F < Content[index / 2]->F)
		{
			Swap(index, index / 2);
			index /= 2;
		}
		else
			return;
	}
}
void MinHeap::Clean()
{
	for (int i = 1; i <= CurSize; i++)
		if(!(Content[i]->IsPath))
			delete Content[i];
	CurSize = 0;
}