#ifndef TREE_H__
#define TREE_H__
#include <iostream>
#include <cmath>
#include <fstream>
#include <stack>
#include <vector>
using namespace std;
struct KTNode
{
	KTNode() : info(0), left(nullptr), right(nullptr) {}
	explicit KTNode(int info, KTNode* left = nullptr, KTNode* right = nullptr) : info(info), left(left), right(right) {}
	int info;
	KTNode* left;
	KTNode* right;
};
struct KTuple4
{
	KTuple4(bool IsRoot1, KTNode * p, int hli = 0, int hri = 0, int ki = 0, bool IsAVLi = true, bool IsAVLli = true, bool IsAVLri = true) :
		IsRoot(IsRoot1), p(p), hl(hli), hr(hri), k(ki), IsAVL(IsAVLi), IsAVLl(IsAVLli), IsAVLr(IsAVLri) {}
	bool IsRoot;
	KTNode * p;
	int hl;
	int hr;
	int k;
	bool IsAVL;
	bool IsAVLl;
	bool IsAVLr;
};
KTuple4 * FindParent(vector<KTuple4>&st, KTNode* t)
{
	if (st.empty())
		return nullptr;
	else
		return st.back().IsRoot ? &st.back() : &*(st.end() - 2);
}
class KSimpleTree
{
public:
	KSimpleTree() : fpRoot(nullptr) {}
	bool insert(int x)
	{
		bool BRet = true;
		KTNode** ppPrev = &fpRoot;
		KTNode * p = fpRoot;
		while (p)
		{
			if (x < p->info)
			{
				ppPrev = &p->left;
				p = p->left;
			}
			else
			{
				if (x > p->info)
				{
					ppPrev = &p->right;
					p = p->right;
				}
				else
				{
					BRet = false;
					break;
				}
			}
		}
		if (p == nullptr)
		{
			*ppPrev = new KTNode(x);
		}
		return BRet;
	}
	void PreOrder(KTNode* t)
	{
		stack <KTNode*> st;
		st.push(t);
		while (!st.empty())
		{
			KTNode* q = st.top();
			st.pop();
			if (q)
			{
				cout << q->info << ' ';
				st.push(q->right);
				st.push(q->left);
			}
		}
	}
	void avl()
	{
		if ((this->fpRoot) != nullptr)
		{
			PreOrder(fpRoot);
			cout << endl;
			KTuple4 a(false, nullptr);
			a = MAXAVL();
			cout << a.p->info << endl;
		}
	}
	KTuple4 MAXAVL()
	{
		KTuple4 temp(false,nullptr);
		int h = 0, k = 0;
		vector<KTuple4> st{ KTuple4(false,fpRoot) };
		while (!st.empty())
		{
			auto tpl = st.back(); st.pop_back();
			if (tpl.p)
			{
				if (tpl.IsRoot)
				{
					if (!(tpl.IsAVLl && tpl.IsAVLr) || !AVL(tpl.hl, tpl.hr))
					{
						tpl.IsAVL = false;
					}
					else 
					{
						if (tpl.k >= temp.k)
						{
							temp = tpl;
						}
					}
					auto pTpl = FindParent(st, tpl.p);
					if (pTpl == nullptr)
					{
						h = 1 + Max(tpl.hl, tpl.hr);
						k = tpl.k + 1;
					}
					else
					{
						if(tpl.p == (*pTpl).p->left)
						{
							(*pTpl).hl = Max(tpl.hl, tpl.hr) + 1;
							(*pTpl).k += (tpl.k + 1);
							(*pTpl).IsAVLl = tpl.IsAVL;
						}
						else
						{
							(*pTpl).hr = Max(tpl.hl, tpl.hr) + 1;
							(*pTpl).k += (tpl.k + 1);
							(*pTpl).IsAVLr = tpl.IsAVL;
						}

					}
				}
				else
				{
					st.push_back(KTuple4(true, tpl.p));
					st.push_back(KTuple4(false, tpl.p->right));
					st.push_back(KTuple4(false, tpl.p->left));
				}
			}
		}
		/*cout << endl << k << endl;
		return h;*/
		return temp;
	}
	KTNode* MaxAVL(KTNode*t, bool& IsAVL, int& k, int& kmax, KTNode*& pKontr, int& h)
	{
		if (t == nullptr) { IsAVL = true; k = 0; h = 0; return nullptr; }
		if (IsLeaf(t))
		{
			IsAVL = true; k = 1; h = 1; if (k > kmax) { kmax = k; pKontr = t; }
			return t;
		}
		else
		{
			int hl, hr;
			int kl, kr;
			bool IsAVL_l, IsAVL_r;
			KTNode* pl = MaxAVL(t->left, IsAVL_l, kl, kmax, pKontr, hl);
			KTNode* pr = MaxAVL(t->right, IsAVL_r, kr, kmax, pKontr, hr);
			k = kl + kr + 1;
			h = Max(hl, hr) + 1;
			if (IsAVL_l && IsAVL_r && (k >= kmax) && AVL(hl, hr))
			{
				IsAVL = true;
				kmax = k;
				pKontr = t;
				return t;
			}
			if (IsAVL_l && IsAVL_r && AVL(hl, hr))
			{
				IsAVL = true;
				return t;
			}
			else
			{
				IsAVL = false;
				return pKontr;
				if (pl)
					return pl;
				return pr;
			}
		}
	}
	bool IsLeaf(KTNode* t)
	{
		if ((t->left == nullptr) && (t->right == nullptr))
			return true;
		else return false;
	}
	KTNode* fpRoot;
private:
	bool AVL(int a, int b)
	{
		if ((a - b < 2) && (a - b) > -2)
			return true;
		else
			return false;
	}
	int Max(int a, int b)
	{
		if (a < b)
			return b;
		else
			return a;
	}
};

#endif


