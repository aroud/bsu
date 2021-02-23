#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <climits>
using namespace std;

int main()
{
	ifstream fi("input.txt");
	int n, m;
	fi >> n >> m;

	vector<int> arr;
	map<int, int> map;

	vector<int> temp;

	int t = 0;

	if (n >= m) {
		arr.resize(n);
		for (int i = 0; i < n; ++i)
		{
			fi >> t;
			arr.push_back(t);
		}
		for (int i = 0; i < m; ++i)
		{
			fi >> t;
			map[t] = i;
		}
	}
	else
	{
		arr.resize(m);
		for (int i = 0; i < n; ++i)
		{
			fi >> t;
			map[t] = i;
		}
		for (int i = 0; i < m; ++i)
		{
			fi >> t;
			arr.push_back(t);
		}
	}


	for_each(begin(arr), end(arr), [&temp, &map](int x)
		{
			auto it = map.find(x);
			if (it != end(map))
				temp.push_back((*it).second);
		});

	vector<int> res(temp.size() + 1, INT_MAX);
	res[0] = INT_MIN;

	for (int i = 0; i < temp.size(); i++) {
		int j = distance(res.begin(), upper_bound(res.begin(), res.end(), temp[i]));
		if (res[j - 1] < temp[i] && temp[i] < res[j])
			res[j] = temp[i];
	}
	int i = 0;
	while (i < res.size() && res[i] != INT_MAX )
	{
		++i;
	}
	--i;

	ofstream fo("output.txt");
	fo << i;
	return 0;
}