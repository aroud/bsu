#include <map>
#include <fstream>

int main()
{
	std::ifstream fi("input.txt");
	std::map<int, int> m;
	int n, t1, t2;
	fi >> n;
	for (int i = 0; i < n-1; ++i)
	{
		fi >> t1 >> t2;
		m.emplace(t2-1, t1);
	}
	std::ofstream fo("output.txt");
	for (int i = 0; i < n; ++i)
	{
		auto it = m.find(i);
		if (it != m.end())
			fo << it->second << ' ';
		else
			fo << 0 << ' ';
	}
	return 0;
}