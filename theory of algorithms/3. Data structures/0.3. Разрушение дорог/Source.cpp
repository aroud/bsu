#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

class DSU
{
public:
	DSU(int n) : n(n), component_count(n) {
		parent = new int[n + 1];
		rank = new int[n + 1];
		for (int v = 1; v <= n; ++v)
		{
			parent[v] = v;
			rank[v] = 0;
		}
	}
	~DSU()
	{
		delete[] parent;
		delete[] rank;
	}

	int find_set(int v) {
		if (v == parent[v])
			return v;
		return parent[v] = find_set(parent[v]);
	}

	void union_sets(int a, int b) {
		a = find_set(a);
		b = find_set(b);
		if (a != b)
		{
			if (rank[a] < rank[b])
				swap(a, b);
			parent[b] = a;
			if (rank[a] == rank[b])
				++rank[a];
			--component_count;
		}
	}

	int get_component_count()
	{
		return component_count;
	}

	int component_count;
	int* parent;
	int* rank;
	int n;
};
template <typename T>
class DisjointSetUnion
{
public:
	DisjointSetUnion(size_t n) : n(n), component_count(n)
	{
		parent.resize(n + 1, -1);
		parent[0] = 0;
	}

	T& find_set(T& x)
	{
		if (parent[x] < 0)
		{
			return x;
		}
		parent[x] = find_set(parent[x]);
		return parent[x];
	}
	void union_sets(T x, T y) {
		x = find_set(x);
		y = find_set(y);
		if (x != y)
		{
			if (parent[x] > parent[y])
			{
				std::swap(x, y);
			}
			T t = parent[y];
			parent[y] = x;
			parent[x] += t;
			--component_count;
		}
	}
	size_t get_size()
	{
		return n;
	}
	size_t get_component_count()
	{
		return component_count;
	}
private:
	size_t n;
	size_t component_count;
	std::vector<T> parent;
};


int main()
{
	ifstream fi("input.txt");
	
	int n, m, q;
	fi >> n >> m >> q;
	vector<pair<int,int>> v(m);
	vector<bool> vb(m, true);
	vector<int> destr(q);
	for (auto& el : v)
	{
		fi >> el.first;
		fi >> el.second;
	}
	int t;
	for (int i = 0; i < q; ++i)
	{
		fi >> t;
		--t;
		destr[i] = t;
		vb[t] = false;
	}
	DisjointSetUnion<int> dsu(n);
	//DSU dsu(n);
	for (int i = 0; i < m; ++i)
	{
		if (vb[i])
		{
			dsu.union_sets(v[i].first, v[i].second);
		}
	}
	vector<bool> res(q);
	for (int i = q - 1; i >= 0; --i)
	{
		if (dsu.get_component_count() == 1)
		{
			for (int j = i; j >= 0; --j)
				res[j] = true;
			break;
		}
		else
		{
			dsu.union_sets(v[destr[i]].first, v[destr[i]].second);
		}
	}

	ofstream fo("output.txt");
	copy(res.begin(), res.end(), ostream_iterator<bool>(fo));
	fo << "\n";

	return 0;
}