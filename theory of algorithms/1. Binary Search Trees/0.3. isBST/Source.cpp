#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <limits>
#include <string>
using namespace std;


class KTNode
{
public:
	KTNode(long long info = 0, KTNode* left = nullptr, KTNode* right = nullptr) :info(info), left(left), right(right) { }

	long long info;
	KTNode* left;
	KTNode* right;
};
class KTree {
public:
	KTree() :pRoot(nullptr) {}
	//~KTree() { erase(pRoot); }

	
	bool isBST(KTNode* p, long long min, long long max)
	{
		
		if (!p)
			return true;

		if (p->info < min || p->info > max)
			return 0;

		return
			isBST(p->left, min, p->info - (long long)1) && isBST(p->right, p->info, max); 
	}
	void erase(KTNode*& t)
	{
		if (t)
		{
			erase(t->left);
			erase(t->right);
			delete t;
		}
	}
	KTNode* pRoot;
};

int main()
{
	KTree t;
	ifstream fi("bst.in");
	int temp;
	if (fi)
	{
		long long n, m, p;
		char c;
		fi >> n >> m;
		vector<KTNode*> log(n);
		t.pRoot = new KTNode(m);
		log[0] = t.pRoot;

			for (size_t i = 1; i < n; ++i)
			{
				fi >> m >> p >> c;
				KTNode* node = log[p-1];
				KTNode* temp = new KTNode(m);
				if (c == 'L')
					node->left = temp;
				else
					node->right = temp;
				log[i] = temp;

			}
	}
	else
		cout << "Reading error";
	bool b = t.isBST(t.pRoot, numeric_limits<long long>::min(), numeric_limits<long long>::max());
	ofstream fo("bst.out");
	string s = b?"YES":"NO";
	fo << s << "\n";
	return 0;
}