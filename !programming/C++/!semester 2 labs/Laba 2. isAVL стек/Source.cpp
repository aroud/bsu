#include "Tree.h"

int main()
{
	KSimpleTree t;
	ifstream fi("in.txt");
	if (fi)
	{
		int x;
		while (fi >> x)
		{
			t.insert(x);
		}
		t.avl();
	}
	else cout << "reading error! ";
	system("pause");
	return 0;
}