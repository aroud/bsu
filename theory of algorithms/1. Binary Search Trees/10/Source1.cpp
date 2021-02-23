#include <fstream>
#include <iostream>
#include <stack>

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
	KTNode(int info = 0, KTNode* up = nullptr, KTNode* left = nullptr, KTNode* right = nullptr) :info(info), up(up), left(left), right(right) { }

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

	int height = 0;
	int lh = 0;
	int MSL = 0;

	long long b = 0;
	long long a = 0;



	KTNode* left;
	KTNode* right;
	KTNode* up;


};
class KTree {
public:
	KTree() :pRoot(nullptr) {}
	~KTree() { erase(pRoot); }

	bool insert(int x) {
		bool ret = true;
		KTNode** ppPrev = &pRoot;
		KTNode* p = pRoot, * prev = nullptr;
		while (p)
		{
			if (x < p->info)
			{
				ppPrev = &p->left;
				prev = p;
				p = p->left;
			}
			else {
				if (x > p->info)
				{
					ppPrev = &p->right;
					prev = p;
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
			*ppPrev = new KTNode(x, prev);
		}
		return ret;
	}

	void delPostOrder()
	{
		delPostOrder(pRoot);
	}

	void countMS()
	{
		prepare(pRoot);
		KTNode* p;
		std::stack<KTNode*> st;
		st.push(pRoot);

		while (!st.empty())
		{
			p = st.top();
			st.pop();
			if (p)
			{
				if (p->MSL == MSL)
				{
					long long l1 = 1, l2 = 1;

					if (p->left)
						l1 = p->left->lh;

					if (p->right)
						l2 = p->right->lh;

					p->b = l1 * l2;
				}


				if (p->hasTwoSons())
				{
					if (p->left->height > p->right->height)
					{
						p->left->a = p->a + p->b;
						p->right->a = p->b;
					}
					else {
						if (p->left->height < p->right->height) {
							p->left->a = p->b;
							p->right->a = p->a + p->b;
						}
						else
						{
							p->left->a = p->b + (p->left->lh) * (p->a) / (p->lh);
							p->right->a = p->b + (p->right->lh) * (p->a) / (p->lh);
						}
					}
				}

				if (p->hasOneSon())
				{
					if (p->left)
						p->left->a = p->a + p->b;
					else
						p->right->a = p->a + p->b;
				}
				

				long long c = p->a + p->b;

				if (c > MSNumber)
					MSNumber = c;

				st.push(p->right);
				st.push(p->left);
			}
		}
	}


	friend std::ostream& operator<< (std::ostream& os, KTree& t)
	{
		return t.printPreOrder(os, t.pRoot);
	}

private:

	KTNode* delPostOrder(KTNode* t)
	{
		KTNode* lmin = nullptr, * rmin = nullptr;
		if (t->left)
			lmin = delPostOrder(t->left);
		if (t->right)
			rmin = delPostOrder(t->right);
		if ((t->a + t->b) == MSNumber)
			return del(t, lmin, rmin);
		if (lmin)
			return lmin;
		else
			return t;
	}

	KTNode* del(KTNode* p, KTNode*& lmin, KTNode*& rmin)
	{
		KTNode** ppPrev = &pRoot;

		if (p->up)
		{
			if (p->up->left && p->up->left == p)
			{
				ppPrev = &p->up->left;
			}
			else
			{
				ppPrev = &p->up->right;
			}
		}
		if (p->isLeaf())
		{
			*ppPrev = nullptr;
			delete p;
			return nullptr;
		}
		if (p->hasOneSon())
		{
			if (p->left)
			{
				*ppPrev = p->left;
				p->left->up = p->up;
				delete p;
				return lmin;
			}
			else
			{
				KTNode* pTemp = p->right;
				*ppPrev = pTemp;
				pTemp->up = p->up;
				delete p;
				return rmin;

			}
		}
		//two sons:
		if (rmin->up->left == rmin)
		{
			ppPrev = &(rmin->up->left);

			if (rmin->right)
			{
				*ppPrev = rmin->right;
				rmin->right->up = rmin->up;
			}
			else
				*ppPrev = nullptr;
			p->info = rmin->info;
			delete rmin;
		}
		else
		{
			*ppPrev = rmin;
			rmin->up = p->up;
			rmin->left = p->left;
			p->left->up = rmin;
			delete p;
		}
		return lmin;
	}

	void prepare(KTNode* t)
	{
		if (t->left)
			prepare(t->left);
		if (t->right)
			prepare(t->right);



		//подсчет высот

		int hl = -1;
		int hr = -1;
		if (t->left)
			hl = t->left->height;
		if (t->right)
			hr = t->right->height;
		t->height = max(hl, hr) + 1;



		//подсчет длины наибольшего полупути с корнем в вершине

		if (t->hasOneSon())
		{
			if (t->left)
				t->MSL = t->left->height + 1;
			else
				t->MSL = t->right->height + 1;
		}
		if (t->hasTwoSons())
			t->MSL = t->left->height + t->right->height + 2;
		if (t->MSL > MSL)
			MSL = t->MSL;
		


		//число листьев, лежащих на пути из вершины на расстоянии h(v)
		if (t->isLeaf())
			t->lh = 1;
		else
		{
			if (t->hasOneSon())
			{
				if (t->left)
					t->lh = t->left->lh;
				else
					t->lh = t->right->lh;
			}
			else
			{
				if (t->left->height == t->right->height)
					t->lh = t->left->lh + t->right->lh;
				else
				{
					if (t->left->height > t->right->height)
						t->lh = t->left->lh;
					else
						t->lh = t->right->lh;
				}
			}
		}
	}

	std::ostream& printPreOrder(std::ostream& os, KTNode* t)
	{
		KTNode* p;
		std::stack<KTNode*> st;
		st.push(t);
		while (!st.empty())
		{
			p = st.top();
			st.pop();

			os << p->info << "\n";
			if(p->right)
				st.push(p->right);
			if(p->left)
				st.push(p->left);

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
	long long MSNumber = 0;
	int MSL = 0;
	KTNode* pRoot;
};

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);


	KTree t;
	std::ifstream fi("in.txt");
	std::ofstream fo("out.txt");
	int temp;
	if (fi)
	{
		while (fi >> temp)
			t.insert(temp);
	}
	else
		fo << "Reading error";
	
	t.countMS();
	t.delPostOrder();
	fo << t;
	return 0;
}