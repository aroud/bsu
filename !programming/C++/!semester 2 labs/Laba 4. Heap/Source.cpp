#include <vector>
#include "Heap.h"

KHeap<double> f(KHeap<double> a)
{
	return a;
}
int main()
{
	int n;
	cout << "Enter number of elements" << endl;
	cin >> n;

	KHeap <Test> a(10);
	double temp;
	for (int i = 0; i < n; ++i)
	{
		cin >> temp;
		a.EmplaceBack(temp,1);
	}
	a.outHeap();
	KHeap<double> b = { 1.1,2.2,3.3,4.4 };
	b.outHeap();
	KHeap<double> c(1);
	c = f(b);
	c.outHeap();

	for (auto it = c.begin(); it != c.end(); ++it)
		cout << *it<<' ';
	cout << endl;
	for (auto const& x : c)
		cout << x<<' ';
	KHeap<double> e = { 1.1 };
	Swap2(e, c);
	for (auto const& x : c)
		cout << x << ' ';
	system("pause");
	return 0;
}