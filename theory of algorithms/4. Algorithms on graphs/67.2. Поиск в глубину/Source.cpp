#include <vector>
#include <fstream>
#include <stack>
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
			if (t)
				v[i].emplace_back(j);
		}
	fi.close();

	vector<int> used(n);
	vector<int> numbers(n);
	stack<int> st;
	int counter = 1;
	for (int i = 0; i < n; ++i)
	{
		if (used[i])
			continue;
		st.push(i);
		while (!st.empty())
		{
			int node = st.top();

			st.pop();

			if (used[node] == 2)
				continue;

			used[node] = 2;

			numbers[node] = counter;
			counter++;
			for (int j = v[node].size()-1; j >= 0; j--)
			{ 
				int t = v[node][j];
				if ( used[t] != 2)
				{
					st.push(t);
					used[t] = 1;
				}
			}
		}
	}
	
	ofstream fo("output.txt");

	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(fo, " "));

	fo.close();
	return 0;
}