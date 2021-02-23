#include <iostream>
using namespace std;
class KHeap {
public:
	KHeap(int x)
	{
		h = new int[x];
		HeapSize = 0;
		arraysize = x;
	}
	KHeap(KHeap const & a) :HeapSize(a.HeapSize), arraysize(a.arraysize)
	{
		h = new int[arraysize];
		for (int i = 0; i < HeapSize; ++i)  
		{
			h[i] = a.h[i];
		}
	}
	~KHeap()
	{
		delete[] h;
	}

	void insert(int n)
	{
		if (HeapSize - 1 < arraysize)
		{
			int i, parent;
			i = HeapSize;
			h[i] = n;
			parent = (i - 1) / 2;
			while (parent >= 0 && i > 0)
			{
				if (h[i] < h[parent])
				{
					int temp = h[i];
					h[i] = h[parent];
					h[parent] = temp;
				}
				i = parent;
				parent = (i - 1) / 2;
			}
			HeapSize++;
		}
	}
	void outHeap()
	{
		if (IsEmpty() != true)
		{
			int i = 0;
			int k = 1;
			while (i < HeapSize) {
				while ((i < k) && (i < HeapSize))
				{
					cout << h[i] << " ";
					i++;
				}
				cout << endl;
				k = k * 2 + 1;
			}
			cout << endl;
		}
	}
	void out()
	{
		if (IsEmpty() != true)
		{
			for (int i = 0; i < HeapSize; i++)
			{
				cout << h[i] << " ";
			}
			cout << endl;
		}
	}
	void heapify(int i)
	{
		if (IsEmpty() != true)
		{
			int left, right;
			int temp;
			left = 2 * i + 1;
			right = 2 * i + 2;
			if (left < HeapSize)
			{
				if (h[i] > h[left])
				{
					temp = h[i];
					h[i] = h[left];
					h[left] = temp;
					heapify(left);
				}
			}
			if (right < HeapSize)
			{
				if (h[i] > h[right])
				{
					temp = h[i];
					h[i] = h[right];
					h[right] = temp;
					heapify(right);
				}
			}
		}
	}
	bool IsEmpty()
	{
		if (HeapSize == 0)
			return true;
		else
			return false;
	}
	int delmin()
	{
		if (IsEmpty() != true)
		{
			int x;
			x = h[0];
			h[0] = h[HeapSize - 1];
			HeapSize--;
			heapify(0);
			return(x);
		}
	}
	void Min()
	{
		if (IsEmpty() != true) {
			cout << h[0];
		}
	}
	void Clear()
	{
		HeapSize = 0;
	}
	friend void Swap2(KHeap &a, KHeap &b);
	KHeap& operator= (KHeap & b)
	{
		if (this != &b) 
		{
			KHeap t(b);
			Swap2(t, *this);
		return *this;
		}
	}
	friend void operator<< (ostream& os, KHeap & a)
	{
		a.out();
	}
	friend void operator>>(istream& is, KHeap & a)
	{
		int x; is >> x;
		a.insert(x);
	}
	int arraysize;
	int *h;
	int HeapSize;
};
void Swap2(KHeap &a, KHeap &b)
{
	swap(a.h, b.h);
	swap(a.arraysize, b.arraysize);
	swap(a.HeapSize, b.HeapSize);
}
KHeap f(KHeap h)
{
	h.insert(8);
	return h;
}
int main()
{
	int n;
	cout << "Enter number of elements";
	cin >> n;
	int temp;
	KHeap a(10);
	for (int i = 0; i < n; ++i)
	{
		cin >> temp;
		a.insert(temp);
	}
	cout << a;
	KHeap c = f(a);
	cout << a;
	cout << c;
	system("pause");
	return 0;
}