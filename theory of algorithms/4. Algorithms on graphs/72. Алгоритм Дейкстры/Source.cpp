#include <fstream> 
#include <vector> 
#include<set>
const long long INF = LLONG_MAX;

using namespace std;
int main() {
	ifstream fi("input.txt");
	ofstream fo("output.txt");
	int n, m, u, v, w;
	fi >> n >> m;
	vector<vector<pair<int, int>>> g(n);
	for (int i = 0; i < m; i++) {
		fi >> u >> v >> w;
		g[u - 1].emplace_back(v - 1, w);
		g[v - 1].emplace_back(u - 1, w);
	}

	int s = 0;
	vector<long long> d(n, INF), p(n);
	d[s] = 0;

	set<pair<int, int>> q;
	q.emplace(d[s], s);

	while (!q.empty()) 
	{
		int temp = q.begin()->second;
		q.erase(q.begin());
		for (size_t j = 0; j < g[temp].size(); ++j)
		{
			int to = g[temp][j].first;
			int weight = g[temp][j].second;
			if (d[temp] + weight < d[to])
			{
				q.erase(make_pair(d[to], to));
				d[to] = d[temp] + weight;
				p[to] = temp;
				q.emplace(d[to], to);
			}
		}
	}
	fo << d[n - 1];
	return 0;
}