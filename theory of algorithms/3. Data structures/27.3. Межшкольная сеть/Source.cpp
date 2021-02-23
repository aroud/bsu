#define _CRT_SECURE_NO_WARNINGS
#pragma optimize("03")

#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <cstdio>

using namespace std;

vector<bool> used;
vector<int> order; //topological sort
vector<int> scc; //to mark components
vector<int>* g,* gr,* gscc;

//kosaraju's algorithm: dfs1- DFS in G, dfs2- DFS in G(t)
void dfs1(int ind) 
{
	used[ind] = true;
	for (int i = 0; i < g[ind].size(); ++i)
		if (!used[g[ind][i]])
			dfs1(g[ind][i]);
	order.push_back(ind);
}

void dfs2(int ind,int j) {
	used[ind] = true;
	scc[ind] = j;
	for (int i = 0; i < gr[ind].size(); ++i)
		if (!used[gr[ind][i]])
			dfs2(gr[ind][i],j);
}

vector<bool> marked;
vector<int> sinks;
vector<int> sources;
vector<int> isolated;
bool sink_not_found;
int w;

void search(vector<int>* gscc, int x)
{
	if (!marked[x]) {

		if (find(begin(sinks), end(sinks), x) != sinks.end()) {
			w = x;
			sink_not_found = false;
		}
		marked[x] = true;
		//each y such that (x, y) is an arc
		for (int i = 0; i < gscc[x].size(); ++i)
		{
			if (sink_not_found)
			{
				search(gscc, gscc[x][i]);
			}
		}
	}
}
int get_vertex(int comp)
{
	int res = -1;
	for (int i = 0; i < scc.size(); ++i)
	{
		if (comp == scc[i])
		{
			res = i;
			break;
		}
	}
	return res;
}

int main()
{
	ifstream fi("input.txt");
	int n = 0, t = 0;
	fi >> n;

	//main graph G
	g = new vector<int>[n];
	//G(transposed)
	gr = new vector<int>[n];



	for (int i = 0; i < n; ++i)
	{
		while (fi >> t && t)
		{
			g[i].push_back(t - 1);
			gr[t - 1].push_back(i);
		}
	}

	used.resize(n, false);
	scc.resize(n);
	for (int i = 0; i < n; ++i)
	{
		if (!used[i])
		{
			dfs1(i);
		}
	}

	fill(begin(used), end(used), false);
	int n_scc = 0;
	for (int i = n - 1; i >= 0; --i)
	{
		int ind = order[i];
		if (!used[ind])
		{
			dfs2(ind, n_scc);
			++n_scc;
		}
	}

	//condensation of a directed graph G
	gscc = new vector<int>[n_scc];
	vector<bool> is_source(n_scc, true);
	vector<bool> is_sink(n_scc, true);
	vector<bool> is_isolated(n_scc, true);
	int component1, component2;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < g[i].size(); ++j)
		{
			component1 = scc[i];
			component2 = scc[g[i][j]];
			if (component1 != component2)
			{
				gscc[component1].push_back(component2);
				is_isolated[component1] = false;
				is_isolated[component2] = false;
				is_source[component2] = false;
				is_sink[component1] = false;
			}
		}
	}
	for (int i = 0; i < n_scc; ++i)
	{
		sort(gscc[i].begin(), gscc[i].end());
		gscc[i].erase(unique(gscc[i].begin(), gscc[i].end()), gscc[i].end());
	}


	for (int i = 0; i < n_scc; ++i)
	{
		if (is_isolated[i])
		{
			isolated.push_back(i);
			is_sink[i] = false;
			is_source[i] = false;
		}
	}
	for (int i = 0; i < n_scc; ++i)
	{
		if (is_sink[i])
		{
			sinks.push_back(i);
		}
		else if (is_source[i])
		{
			sources.push_back(i);
		}
	}


	int answer_1 = sources.size() + isolated.size();
	int answer_2; // max(s,t) + q is lower bound

	//initialize all nodes to be unmarked
	marked.resize(n_scc);


	vector<int> v_vect; //0...p...s
	vector<int> w_vect;   //0...p...t

	vector<bool> sources_in(sources.size());
	vector<bool> sinks_in(sinks.size());

	int v;
	for (int i = 0; i < sources.size(); ++i)
	{
		v = sources[i];
		if (!marked[v])
		{
			w = -1;
			sink_not_found = true;
			search(gscc, v);
			if (w != -1)
			{
				v_vect.push_back(v);
				w_vect.push_back(w);
				sources_in[i] = true;
				sinks_in[i] = true;
			}
		}
	}
	int p = v_vect.size() - 1;
	
	for (int i = 0; i < sources.size(); ++i)
	{
		if (!sources_in[i])
		{
			v_vect.push_back(sources[i]);
		}
	}
	for (int i = 0; i < sinks.size(); ++i)
	{
		if (!sinks_in[i])
		{
			w_vect.push_back(sinks[i]);
		}
	}
	
	int s = sources.size() - 1;  //s,q,t-last elements in sourses, sinks, isolated
	t = sinks.size() - 1;    //so each vector: elements [from 0 to s/t/q]
	int q = isolated.size() - 1;

	vector<pair<int, int>> a_scc;


	for (int i = 0; i < p; i++)
	{
		a_scc.emplace_back(make_pair(w_vect[i], v_vect[i + 1]));
	}
	for (int i = p + 1; i <= min(s, t); i++) {
		a_scc.emplace_back(make_pair(w_vect[i], v_vect[i]));
	}
	if (p != -1) 
	{
		if (s <= t)
		{
			for (int i = s + 1; i < t; i++) {
				a_scc.emplace_back(make_pair(w_vect[i], w_vect[i + 1]));
			}

			if (q == -1 && s == t)
			{
				a_scc.emplace_back(make_pair(w_vect[p], v_vect[0]));
			}
			else {
				a_scc.emplace_back(make_pair(w_vect[p], w_vect[s + 1]));

				if (!(q + 1))
				{
					a_scc.emplace_back(make_pair(w_vect[t], v_vect[0]));
				}
				else
				{
					a_scc.emplace_back(make_pair(w_vect[t], isolated[0]));
					a_scc.emplace_back(make_pair(isolated[q], v_vect[0]));
					for (int i = 0; i < q; ++i)
					{
						a_scc.emplace_back(make_pair(isolated[i], isolated[i + 1]));
					}
				}
			}
		}
		else // s > t
		{
			for (int i = t + 1; i < s; i++) {
				a_scc.emplace_back(v_vect[i], v_vect[i + 1]);
			}

			a_scc.emplace_back(v_vect[p], v_vect[t + 1]);

			if (!(q + 1))
			{
				a_scc.emplace_back(w_vect[p], v_vect[0]);
			}
			else {
				for (int i = 0; i < q; ++i)
				{
					a_scc.emplace_back(isolated[i], isolated[i + 1]);
				}
				a_scc.emplace_back(w_vect[p], isolated[0]);
				a_scc.emplace_back(isolated[q], v_vect[0]);
			}
		}
	}
	else
	{
		
		for (int i = 0; i < q; ++i)
		{
			a_scc.emplace_back(isolated[i], isolated[i + 1]);
		}
		if (q > 0)
			a_scc.emplace_back(isolated[q], isolated[0]);
	}
	answer_2 = a_scc.size();
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	freopen("output.txt", "w", stdout);
	printf("%d\n", answer_1);
	printf("%d\n", answer_2);

	for (int i = 0; i < answer_2; ++i)
	{
		printf("%d ", get_vertex(a_scc[i].first)+1);
		printf("%d\n", get_vertex(a_scc[i].second)+1);
	}

	delete[] g;
	delete[] gr;
	delete[] gscc;
	return 0;
}