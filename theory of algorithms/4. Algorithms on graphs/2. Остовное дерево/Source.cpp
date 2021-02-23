#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <iostream>
using namespace std;
int main()
{
	ifstream fi("input.txt");
	int n;
	fi >> n;
	int m = 0;
	vector<vector<int>> v(n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			int t;
			fi >> t;
			if (t && j > i)
				m++;
			v[i].emplace_back(t);
		}
	fi.close();

	vector<bool> nodes(n);
	queue<int> q;
	stack<pair<int, int>> edges;
	q.push(0);
	while (!q.empty())
	{
		int node = q.front();
		q.pop();
		nodes[node] = true;
		for (int j = 0; j < n; j++)
		{
			if (v[node][j] == 1 && nodes[j] == false)
			{
				q.push(j);
				nodes[j] = 1;
				edges.emplace(node + 1, j + 1);
			}
		}
	}
	bool res = true;

	for (int i = 0; i < n; ++i)
		if (!nodes[i])
			res = false;
	ofstream fo("output.txt");
	if (!res)
		fo << -1;
	else
	{
		fo << edges.size() << endl;
		while (!edges.empty())
		{
			auto p = edges.top();
			fo << p.first << ' ' << p.second << endl;
			edges.pop();
		}
	}
	fo.close();

	return 0;
}