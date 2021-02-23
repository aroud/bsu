#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

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

	int height = 0;

	int MSL = 0;

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

	void algorithm()
	{
		defNodeMSLHeight(pRoot);
		defMSL();
		fillRoots(pRoot);

		KTNode* t = roots[0];
		KTNode* prev = t;
		if (t->left)
		{
			t = t->left;
			while (t->left && t->left->height == (t->height - 1))
			{
				prev = t;
				t = t->left;
			}
			if (t->right && t->right->height == (t->height - 1))
			{
				t = t->right;
				while (t->left && t->left->height == (t->height - 1))
				{
					t = t->left;
				}
				del(t->info);
				return;
			}
			del(prev->info);
			return;
		}

		if (t->right)
		{
			if (t->right->MSL == MSL)
			{
				func(t->right);
				return;
			}
			t = t->right;
			
			while (t->left && (t->left->height == (t->height - 1)||(t->left->MSL == MSL)))
			{
				t = t->left;
				if (t->MSL == MSL)
				{
					func(t);
					return;
				}
			}
			del(t->info);
			return;
		}
		t = roots[1];
		while (t->left && t->left != roots[0] && (t->left->height == (t->height - 1) || (t->left->MSL == MSL)))
		{
			t = t->left;
			if (t->MSL == MSL)
			{
				func(t);
				return;
			}
		}
		del(t->info);
		return;
	}
	

	friend ostream& operator<< (ostream& os, KTree& t)
	{
		return t.printPreOrder(os, t.pRoot);
	}

private:

	void func(KTNode* t)
	{
		if (t->left)
		{
			t = t->left;

			while (t->left && (t->left->height == (t->height - 1) || (t->left->MSL == MSL)))
			{
				t = t->left;
				if (t->MSL == MSL)
				{
					func(t);
					return;
				}
			}
			del(t->info);
			return;
		}
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

	void fillRoots(KTNode* t)
	{
		if (t->left)
			fillRoots(t->left);
		if (t->MSL == MSL)
			roots.push_back(t);
		if (t->right)
			fillRoots(t->right);
	}

	void defMSL()
	{
		KTNode* p;
		stack<KTNode*> st;
		st.push(pRoot);

		int max = 0;

		while (!st.empty())
		{
			p = st.top();
			st.pop();
			if (p)
			{
				if (p->MSL > max)
					max = p->MSL;
				st.push(p->right);
				st.push(p->left);
			}
		}
		MSL = max;
	}

	void defNodeMSLHeight(KTNode* t)
	{
		if (t)
		{
			defNodeMSLHeight(t->left);
			defNodeMSLHeight(t->right);

			int hl = -1;
			int hr = -1;
			if (t->left)
				hl = t->left->height;
			if (t->right)
				hr = t->right->height;
			t->height = max(hl, hr) + 1;

			if (t->hasOneSon())
			{
				if (t->left)
					t->MSL = t->left->height + 1;
				else
					t->MSL = t->right->height + 1;
			}
			if (t->hasTwoSons())
				t->MSL = t->left->height + t->right->height + 2;
		}
	}

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
	int counter = 0;
	int MSL = 0;
	KTNode* pRoot;

	vector<KTNode*> roots;
};



int main()
{
	KTree t;
	ifstream fi("in.txt");
	int temp;
	if (fi)
	{
		while (fi >> temp)
			t.insert(temp);
	}
	else
		cout << "Reading error";
	ofstream fo("out.txt");
	t.algorithm();
	fo << t;
	return 0;
}