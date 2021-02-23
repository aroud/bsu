#include <iostream>
#include <fstream>
#include <stack>
using namespace std;


class KTNode
{
public:
	KTNode(int info = 0, KTNode* left = nullptr, KTNode* right = nullptr) :info(info), left(left), right(right) { }
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

	long long int sum()
	{
		return sum(pRoot);
	}
	long long int sum(KTNode* t)
	{
		KTNode* p;
		stack<KTNode*> st;
		st.push(t);
		long long int sum = 0;
		while (!st.empty())
		{
			p = st.top();
			st.pop();
			if (p)
			{
				sum += p->info;
				st.push(p->right);
				st.push(p->left);
			}
		}
		return sum;
	}

	friend ostream& operator<< (ostream& os, KTree& t)
	{
		return t.print_pre_order(os, t.pRoot);
	}

private:
	ostream& print_pre_order(ostream& os, KTNode* t)
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

	/*void Erase(KTNode** t)
	{
		if (*t)
		{
			Erase(&((*t)->left));
			Erase(&((*t)->right));
			delete *t;
		}
	}*/
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
		while (fi >> temp)
			t.insert(temp);
	}
	else
		cout << "Reading error";
	//cout << t;
	ofstream fo("output.txt");
	fo << t.sum();
	return 0;
}