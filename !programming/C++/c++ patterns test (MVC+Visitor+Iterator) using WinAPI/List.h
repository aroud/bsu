#pragma once

#include "Package.h"
#include "Visitor.h"


template <typename T>
class List;

template <typename T>
class Iterator
{
	const List<T>* dq;
	int index;
public:
	Iterator(const List<T>*);
	void first();
	void next();
	bool isDone();
	T currentItem();
};

template <typename T>
class List
{
	friend class Iterator<T>;
public:
	//конструкторы
	List() : iMax(5), iTop(0) { pArr = new T[5]; }
	List(List<T>&& a) : iTop(a.iTop), iMax(a.iMax)
	{
		pArr = a.pArr;
		a.pArr = nullptr;
		a.iTop = 0;
		a.~Deque();
	}
	List(List<T> const& a) : iTop(a.iTop), iMax(a.iMax)
	{
		pArr = new T[iMax];
		for (int i = 0; i < iTop; ++i)
		{
			pArr[i] = a.pArr[i];
		}
	}
	List(std::initializer_list<T> Ilist)
	{
		pArr = new T[Ilist.size() << 1];
		iTop = 0;
		iMax = Ilist.size() * 2;
		for (auto x : Ilist)
		{
			PushBack(x);
		}
	}
	~List()
	{
		delete[] pArr;
		iTop = 0;
		iMax = 0;
	}

	//короткие методы

	void Clear()
	{
		while (!IsEmpty())
		{
			PopBack();
		}
	}
	bool IsEmpty()
	{
		return iTop == 0;
	}
	bool IsFull()
	{
		return iTop == iMax;
	}
	int Size()
	{
		return iTop;
	}

	//удаление

	void PopFront()
	{
		if (!IsEmpty())
		{
			for (int i = iTop - 1; i > 0; --i)
			{
				pArr[i-1] = pArr[i];
			}
			iTop--;
		}
	}
	void PopBack()
	{
		if (!IsEmpty()) {
			--iTop;
		}
	}

	//вставка

	void PushBack(T const& el)
	{
		if (IsFull()) {
			Enlarge();
		}
		pArr[iTop] = el;
		++iTop;
	}
	void PushFront(T const& el)
	{
		if (IsFull()) {
			Enlarge();
		}
		else
		{
			for (int i = iTop - 1; i >= 0; --i)
			{
				pArr[i + 1] = pArr[i];
			}
			pArr[0] = el;
			++iTop;
		}
	}

private:
	void Enlarge()
	{
		iMax *= 2;
		T* pTemp;
		pTemp = new T[iMax];
		for (int i = 0; i < iTop; ++i)
		{
			pTemp[i] = pArr[i];
		}
		delete[] pArr;
		pArr = nullptr;
		std::swap(pArr, pTemp);
	}
//private:
	public:
	T* pArr;
	int iTop;
	int iMax;

public:
	Iterator<T>* createIterator()const
	{
		return new Iterator<T>(this);
	}
	void accept(Visitor<T>& v)
	{
		auto it = (*this).createIterator();
		for (it->first(); !it->isDone(); it->next())
			v.visit(it->currentItem());
	}
};
template <typename T>
Iterator<T>::Iterator(const List<T>* dq1) { dq = dq1; }

template <typename T>
void Iterator<T>::first() 
{ 
	index = 0; 
}

template <typename T>
void Iterator<T>::next()
{
	if (!(index < dq->iTop)) throw Bad();
	index++;
}

template <typename T>
bool Iterator<T>::isDone()
{
	return index == (dq->iTop);
}

template <typename T>
T Iterator<T>::currentItem()
{
	return dq->pArr[index];
}