#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> v(n);

	int t;
	for (int i = 0; i < n; ++i)
	{
		cin >> t;
		v[i] = t;
	}

	vector<int> length(n, 1);
	vector<int> prev(n);
	for (int i = 0; i < n; ++i)
	{
		prev[i] = i;
	}
	int max = 1;
	int max_index = 0;

	if (v.size() == 1)
	{
		cout << 1 << "\n" << 1 << "\n";
		return 0;
	}

	for (int i=0;i<n;++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (v[j])
			{
				if (v[i] % v[j] == 0)
				{
					t = length[j] + 1;
					if (t > length[i])
					{
						length[i] = t;
						if (t > max)
						{
							max = t;
							max_index = i;
						}
						prev[i] = j;

					}
				}
			}
		}
	}
	
	cout << max << "\n";
	
	int i = max_index;

	vector<int>res;
	while (i != prev[i])
	{
		res.push_back(i + 1);
		i = prev[i];
	}
	res.push_back(i + 1);

	reverse_copy(begin(res), end(res), ostream_iterator<int>(cout, " "));
	cout << endl;
	

	return 0;
}