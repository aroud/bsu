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

		t.PreOrder(t.fpRoot);
		//cout << endl << t.SumValue(t.fpRoot);

		/*bool b; int k1, kmax1 = 0;
		KTNode * g1 = nullptr;
		cout << endl << t.MaxFull(t.fpRoot, b, k1, kmax1, g1)->info<<endl;*/

		bool IsAVL;
		int k,kmax=0,h;
		KTNode * g = nullptr;
		KTNode* result = t.MaxAVL(t.fpRoot, IsAVL, k, kmax, g, h);
		if (result != nullptr)
			cout << endl << result->info;
		else
			cout << " Empty tree!";
	}
	else cout << "reading error! ";
	system("pause");
	return 0;
}