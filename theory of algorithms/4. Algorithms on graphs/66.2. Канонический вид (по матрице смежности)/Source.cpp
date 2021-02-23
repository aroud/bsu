#include <map>
#include <fstream>

int main()
{
	std::ifstream fi("input.txt");
	std::map<int, int> m;
	int n, t;
	fi >> n;
	for (int i = 0; i < n ; ++i)
		for (int j = 0; j < n; ++j)
		{
			fi >> t;
			if (t)
				m.emplace(j, i+1);
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