#include <vector>
#include <queue>
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
	for(int i=0;i<n;++i)
		for (int j = 0; j < n; ++j)
		{
			
			int t;
			fi >> t;
			if (t && j > i)
				m++;
			v[i].emplace_back(t);
		}
	
	vector<bool> nodes(n);
	queue<int> q;
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
			}
		}
	}
	bool res = true;

	for (int i = 0; i < n; ++i)
		if (!nodes[i])
			res = false;
	if (!(m == n - 1))
		res = false;
	ofstream fo("output.txt");
	if (res)
		fo << "YES";
	else
		fo << "NO";
	fo.close();	
	fi.close();
	return 0;
}