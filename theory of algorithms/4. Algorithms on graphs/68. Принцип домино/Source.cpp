#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;
int main()
{
	ifstream fi("in.txt");
	int n;
	fi >> n;

	vector<vector<int>> v(n);
	for (int i = 0; i < n; ++i)
	{
		int k;
		fi >> k;
		for (int j = 0; j < k; ++j)
		{
			int t;
			fi >> t;
			v[i].emplace_back(t-1);
		}
	}
	fi.close();

	vector<pair<bool,int>> answers(n);
	queue<int> q;


	for (int s = 0; s < n; ++s)
	{
		vector<bool> used(n);
		vector<int> numbers(n);

		q.push(s);
		used[s] = true;

		numbers[s] = 0;

		while (!q.empty())
		{
			int vertex = q.front();
			q.pop();

			int tcounter = numbers[vertex] + 1;
			for (size_t i = 0; i < v[vertex].size(); ++i) {

				int t = v[vertex][i];

				if (!used[t])
				{
					used[t] = true;
					q.push(t);
					numbers[t] = tcounter;
				}
			}
		}
		bool tb = true;
		for (int i = 0; i < n; ++i)
		{
			if (!used[i])
			{
				tb = false;
				break;
			}
		}
		answers[s].first = tb;
		if (tb)
		{
			int max = 0;
			for (int i = 0; i < n; ++i)
			{
				if (numbers[i] > max)
					max = numbers[i];
			}
			answers[s].second = max;
		}
	}
	ofstream fo("out.txt");
	int a = -1;
	int numb = 0;
	for (int i = 0; i < n; ++i)
	{
		if (answers[i].first)
			if (answers[i].second>=a)
			{
				a = answers[i].second;
				numb = i+1;
			}
	}
	if (a == -1)
		fo << "impossible";
	else
	{
		fo << a << '\n' << numb;
	}

	fo.close();

	return 0;
}