#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>;
using namespace std;
int main()
{

	ifstream fi("input.txt");
	int n, m;
	fi >> n >> m;
	vector < vector<int>> matrix(n);
	for (auto it = matrix.begin(); it != matrix.end(); ++it)
	{
		for (int i = 0; i < n; ++i)
		{
			int temp = 0;
			(*it).push_back(temp);
		}
	}
	int t1, t2;
	for (int i = 0; i < m; ++i)
	{
		fi >> t1 >> t2;
		++matrix[t1 - 1][t2 - 1];
		++matrix[t2 - 1][t1 - 1];
	}
	fi.close();

	ofstream fo("output.txt");
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			fo << matrix[i][j] << ' ';
		fo << endl;
	}
	fo.close();
	
	return 0;
}