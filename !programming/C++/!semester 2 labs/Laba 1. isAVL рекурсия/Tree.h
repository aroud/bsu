#ifndef TREE_H__
#define TREE_H__
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
 
struct KTNode
{
	KTNode(): info(0), left(nullptr), right(nullptr){}
	explicit KTNode(int info, KTNode* left=nullptr, KTNode* right = nullptr): info(info), left(left), right(right) {}
	int info;
	KTNode* left;
	KTNode* right;
};

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
	KTNode * Find(int x) /* найти элемент*/
	{
		KTNode *p = fpRoot;
		while (p)
		{
			if (x == p->info)
				break;
			else
			{
				if (x < p->info) p = p->left;
				else p = p->right;
			}
		}
		return p;
	}
	void PreOrder(KTNode* t)
	{
		if (t)
		{
			cout << t->info << ' ';
			PreOrder(t->left);
			PreOrder(t->right);
		}
	}
	int SumValue(KTNode* t)
	{
		if (t == nullptr)
			return 0;
		else return t->info + SumValue(t->left) + SumValue(t->right);
	}
	KTNode* LgtR(KTNode* t, int& h)
	{
		if (t == nullptr) { h = 0; return nullptr; }
		else
		{
			if (IsLeaf(t))
			{
				h = 1;
				return nullptr;
			}
			else
			{
				int hl, hr;
				KTNode* pl = LgtR(t->left, hl);
				KTNode* pr = LgtR(t->right, hr);
				h = Max(hl, hr);
				if (hl > hr)
				{
					return t;
				}
				if (pl) return pl;
				else return pr;
			}
		}
	}
	KTNode* MaxFull(KTNode* t, bool& b, int& k, int& kmax, KTNode*& pKontr)
	{
		if (t == nullptr) { b = false; k = 0; return nullptr; }
		if (IsLeaf(t)) { b = true; k = 1; if (k > kmax) { kmax = k; pKontr = t; }
		return t; }
		else
		{
			bool IsFull_l, IsFull_r;
			int kl, kr;
			KTNode* pl = MaxFull(t->left, IsFull_l, kl, kmax, pKontr);
			KTNode* pr = MaxFull(t->right, IsFull_r, kr, kmax, pKontr);
			k = kl + kr + 1;
			if (IsFull_l && IsFull_r && (k >= kmax))
			{
				b = true;
				kmax = k;
				pKontr = t;
				return t;
			}
			else
			{
				b = false;
				return pKontr;
				if (pl)
					return pl;
				return pr;
			}
		}
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
		if((a-b <2) && (a-b)>-2)
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
