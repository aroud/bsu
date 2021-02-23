#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;
int main()
{
	ifstream fi("input.txt");
	int n;
	fi >> n;

	vector<vector<int>> v(n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			int t;
			fi >> t;
			if(t)
				v[i].emplace_back(j);
		}
	fi.close();

	for (int i = 0; i < n; ++i)
		sort(v[i].begin(), v[i].end());
		
	
	vector<bool> used(n);
	vector<int> numbers(n);
	queue<int> q;
	int counter = 1;
	for (int s = 0; s < n; ++s)
	{
		if (used[s])
			continue;


		q.push(s);
		used[s] = true;

		numbers[s] = counter;
		counter++;
		

		while (!q.empty())
		{
			int vertex = q.front();
			q.pop();

			for (size_t i = 0; i < v[vertex].size(); ++i) {

				int t = v[vertex][i];

				if (!used[t]) 
				{
					used[t] = true;
					q.push(t);
					numbers[t] = counter;
					counter++;
				}
			}
		}

	}

	ofstream fo("output.txt");

	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(fo, " "));

	fo.close();
	
	return 0;
}