#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iterator>
#include <string>

using namespace std;

int arr[300000];
vector<long long> tree;


void build_tree(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = arr[tl];
    }
    else 
    {
        int tm = (tl + tr) / 2;
        build_tree(v * 2, tl, tm);
        build_tree(v * 2 + 1, tm + 1, tr);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}

long long sum(int v, int tl, int tr, int l, int r)
{
    if (l == tl && r == tr)
    {
        return tree[v];
    }
    if (l > r)
    {
        return 0;
    }
    int tm = (tl + tr) / 2;
    return sum(v * 2, tl, tm, l, min(r, tm)) + sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

void inc(int v, int tl, int tr, int idx, int delta) 
{
  
    if (tl == tr)
    {        
        tree[v] += delta;
        return;
    }

    if (tr < idx || idx < tl) 
    {
        return;
    }

    int tm = (tl + tr) / 2;
    if (idx <= tm)
        inc(v * 2, tl, tm, idx, delta);
    else
        inc(v * 2 + 1, tm + 1, tr, idx, delta);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

int main()
{
	int n=0, t=0;
	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &t);
        arr[i] = t;
	}
    tree.resize(n * 4);
    build_tree(1, 0, n - 1);


    int q;
	cin >> q;
	string s;
	int t1=0, t2=0;
	for(int i=0;i<q;++i)
	{
		cin >> s >> t1 >> t2;
	
		if (s[0] == 'A')
			inc(1, 0, n-1, t1, t2);
		else
			cout << sum(1, 0, n-1, t1, t2-1)<<'\n';
			
	}

    return 0;
}