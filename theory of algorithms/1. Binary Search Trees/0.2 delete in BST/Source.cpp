#include <iostream>
#include <fstream>
#include <stack>
using namespace std;


class KTNode
{
public:
	KTNode(int info = 0, KTNode* left = nullptr, KTNode* right = nullptr) :info(info), left(left), right(right) { }

	bool isLeaf()
	{
		return !left && !right;
	}
	bool hasOneSon()
	{
		return (left && !right) || (!left && right);
	}
	bool hasTwoSons()
	{
		return left && right;
	}


	int info;
	KTNode* left;
	KTNode* right;
};
class KTree {
public:
	KTree() :pRoot(nullptr) {}
	~KTree() { erase(pRoot); }

	bool insert(int x) {
		bool ret = true;
		KTNode** ppPrev = &pRoot;
		KTNode* p = pRoot;
		while (p)
		{
			if (x < p->info)
			{
				ppPrev = &p->left;
				p = p->left;
			}
			else {
				if (x > p->info)
				{
					ppPrev = &p->right;
					p = p->right;
				}
				else
				{
					ret = false;
					break;
				}
			}
		}
		if (ret)
		{
			*ppPrev = new KTNode(x);
		}
		return ret;
	}

	bool del(int x)
	{
		bool ret = true;
		KTNode** ppPrev = &pRoot;
		KTNode* p = pRoot;
		while (p)
		{
			if (x < p->info)
			{
				ppPrev = &p->left;
				p = p->left;
			}
			else {
				if (x > p->info)
				{
					ppPrev = &p->right;
					p = p->right;
				}
				else
					break;
			}
		}
		if (!p)
			ret = false;
		else
		{
			if (!p->hasTwoSons())
			{
				if (p->left)
					*ppPrev = p->left;
				else
					*ppPrev = p->right;
				delete p;
			}
			else
			{
				{
					ppPrev = &p->right;
					KTNode* pTemp = p->right;
					while (pTemp->left)
					{
						ppPrev = &pTemp->left;
						pTemp = pTemp->left;
					}
					if (pTemp->left)
						*ppPrev = pTemp->left;
					else
						*ppPrev = pTemp->right;
					p->info = pTemp->info;
					delete pTemp;
				}
			}
		}
		return ret;
	}

	KTNode* find(int x)
	{
		KTNode* p = pRoot;
		while (p)
		{
			if (p->info == x)
				break;
			else
			{
				if (x < p->info)
					p = p->left;
				else
					p = p->right;
			}
		}
		return p;
	}

	friend ostream& operator<< (ostream& os, KTree& t)
	{
		return t.printPreOrder(os, t.pRoot);
	}

private:
	ostream& printPreOrder(ostream& os, KTNode* t)
	{
		KTNode* p;
		stack<KTNode*> st;
		st.push(t);
		while (!st.empty())
		{
			p = st.top();
			st.pop();
			if (p)
			{
				os << p->info << "\n";
				st.push(p->right);
				st.push(p->left);
			}
		}
		return os;
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
	ifstream fi("input.txt");
	int temp;
	if (fi)
	{
		int x;
		fi >> x;
		while (fi >> temp)
			t.insert(temp);
		t.del(x);
	}
	else
		cout << "Reading error";
	ofstream fo("output.txt");
	fo << t;
	return 0;
}