#include <fstream>;
#include <vector>
using namespace std;
int main()
{
	ifstream fi("input.txt");
	int n, m;
	fi >> n >> m;
	int t1, t2;
	vector<vector<int>> v(n);
	
	for (int i = 0; i < m; ++i)
	{
		fi >> t1 >> t2;
		v[t1 - 1].emplace_back(t2);
		v[t2 - 1].emplace_back(t1);
	}
	ofstream fo("output.txt");
	for (int i = 0; i < n; ++i)
	{
		fo << v[i].size() << ' ';
		for (auto it = v[i].begin(); it != v[i].end(); ++it)
		{
			fo << *it<<' ';
		}
		fo << '\n';
	}
	return 0;
}