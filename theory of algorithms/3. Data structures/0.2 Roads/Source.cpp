#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>

template <typename T>
class DisjointSetUnion
{
public:
	DisjointSetUnion(size_t n): n(n), component_count(n)
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
	std::ifstream fi("input.txt");
	std::ofstream fo("output.txt");
	if (fi) {
		int n, q, u, v;
		fi >> n >> q;
		DisjointSetUnion<int> dsu(n);
		for (int i = 0; i < q; ++i)
		{
			fi >> u >> v;
			dsu.union_sets(u, v);
			fo << dsu.get_component_count() << "\n";
		}
	}
	return 0;
}