#include <iostream>
#include "windows.h"

using namespace std;

class KNode
{
public:
	KNode() : fInfo(0), fNext(nullptr) {}
	explicit KNode(int aInfo) : fInfo(aInfo), fNext(nullptr) {}
	KNode(int aInfo, KNode * aNext) : fInfo(aInfo), fNext(aNext) {}
	int fInfo;
	KNode * fNext;
};

class KSimpleList
{
public:
	KSimpleList() : first(nullptr), pLast(&first) {}
	~KSimpleList() { Erase(first); }
	void PushBack(int x)
	{
		KNode *p = new KNode(x);
		*pLast = p;
		pLast = &p->fNext;
	}
	void Print() const
	{
		KNode * p = first;
		while (p != nullptr)
		{
			cout << p->fInfo << " ";
			p = p->fNext;
		}
	}

	int Sum()
	{
		int c = 0;
		KNode * p = first;
		while (p != nullptr)
		{
			c += p->fInfo;
			p = p->fNext;
		}
		return c;
	}
	bool PopFront()
	{
		if (IsEmpty()) return false;
		else // —писок не пустой
		{
			KNode * p = first;
			first = first->fNext;
			if (first == nullptr) pLast = &first;
			delete p;
			return true;
		}
	}

	bool PopBackIneffective(int x) { return true; }
	int Front() const { return first->fInfo; }
	int Back() const { return ((KNode *)(((char *)pLast) - offsetof(KNode, fNext)))->fInfo; }

	bool IsEmpty() const { return first == nullptr; }
	int Length()
	{
		int c = 0;
		KNode * p = first;
		while (p != nullptr)
		{
			c++;
			p = p->fNext;
		}
		return c;
	}

	void Lab()
	{
		int x = Length();
		if (first != nullptr) {
			int xprev = first->fInfo;
			KNode*xp = first->fNext;

			if (x == 2)
				if (xprev < xp->fInfo)
				{
					PopFront();
				}
			if (x >= 3)
			{

				KNode *start = first;
				KNode*q = first->fNext;
				int prev = q->fInfo;
				KNode*p = q->fNext;
				while (p != nullptr)
				{
					KNode *del;
					if (prev >= p->fInfo)
					{
						prev = p->fInfo;
						p = p->fNext;
						q = q->fNext;
						start = start->fNext;
					}
					else
					{
						del = q;
						q = q->fNext;
						delete del;
						prev = p->fInfo;
						p = p->fNext;
						start->fNext = q;
					}
				}
				int yprev = first->fInfo;
				KNode*yp = first->fNext;
				if (yprev < yp->fInfo)
					PopFront();
			}
		}
	}
private:
	void Erase(KNode* &p)
	{
		KNode * p1;
		while (p)
		{
			p1 = p;
			p = p->fNext;
			delete p1;
		}
	}

private:
	KNode * first; 
	KNode ** pLast;
					
};

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	KSimpleList l;
	int n;
	cout << "¬ведите n: ";
	cin >> n;
	cout << "¬ведите " << n << " целых чисел:" << endl;
	for (int i = 0; i < n; ++i)
	{
		int x;
		cin >> x;
		l.PushBack(x);
	}
	l.Lab();
	l.Print();
	system("pause");
	return 0;
}

