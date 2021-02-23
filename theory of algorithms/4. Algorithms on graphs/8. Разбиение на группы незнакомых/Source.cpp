#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <iostream>
#define COL1 1
#define COL2 2

using namespace std;
int main()
{
	ifstream fi("input.in");
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

	vector<pair<int, int>> nodes(n);
	stack<pair<int, int>> st;
	bool exist = true;
	bool t = true;
	for (int i = 0; i < n; ++i) //для несвязного
	{
		if (nodes[i].first != 0)     //уже проработанная вершина вершина
			continue;
		if (t)
		{
			st.emplace(i, COL1);
			t = !t;
		}
		else
		{
			st.emplace(i, COL2);
			t = !t;
		}
		while (!st.empty())
		{
			auto node = st.top();
			st.pop();

			if (nodes[node.first].first == 2) continue;

			nodes[node.first].first = 2;
			nodes[node.first].second = node.second;

			for (int j = n - 1; j >= 0; --j)
			{
				if (v[node.first][j] == 1 && nodes[j].first != 2)
				{
					if (nodes[j].first == 1 && nodes[j].second == node.second)
					{
						exist = false;
						break;
					}
					else
					{
						if (node.second == COL1)
						{
							st.emplace(j, COL2);
							nodes[j].first = 1; // помечаю вершину как обнаруженную
							nodes[j].second = COL2;
						}
						else
						{
							st.emplace(j, COL1);
							nodes[j].first = 1; // помечаю вершину как обнаруженную
							nodes[j].second = COL1;
						}

					}
				}
			}
			if (!exist)
				break;
		}
		if (!exist)
			break;
	}
	ofstream fo("output.out");
	if (!exist)
		fo << "NO";
	else
	{
		fo << "YES" << endl;
		for (int i = 0; i < n; ++i)
			if (nodes[i].second == COL1)
				fo << i + 1 << ' ';
	}
	fo.close();

	return 0;
}