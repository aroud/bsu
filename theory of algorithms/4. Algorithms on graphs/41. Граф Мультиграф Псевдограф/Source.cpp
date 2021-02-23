#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream fi("input.txt");
	int n, m;
	fi >> n >> m;
	int t1, t2;
	bool l = false;
	bool mult = false;
	vector<vector<short>> v(n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			v[i].push_back(0);
	}

	for (int i = 0; i < m; ++i)
	{
		fi >> t1 >> t2;
		
		if (t1==t2)
			l = true;
		if (v[t1 - 1][t2 - 1] > 0 || v[t2 - 1][t1 - 1] > 0)
			mult = true;
		++v[t1 - 1][t2 - 1];
		++v[t2 - 1][t1 - 1];
	}
	fi.close();
	ofstream fo("output.txt");
	if (!l && !mult)
		fo << "Yes" << endl << "Yes" << endl << "Yes" << endl;
	else
	{
		if (!l)
			fo << "No" << endl << "Yes" << endl << "Yes" << endl;
		else
			fo << "No" << endl << "No" << endl << "Yes" << endl;
	}
	fo.close();
	return 0;
}