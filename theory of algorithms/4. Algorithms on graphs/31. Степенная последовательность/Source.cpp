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
	int* arr = new int[n];
	for (int i = 0; i < n; ++i)
		arr[i] = 0;
	int t1, t2;
	for (int i = 0; i < m; ++i)
	{
		fi >> t1 >> t2;
		++arr[t1 - 1];
		++arr[t2 - 1];
	}
	fi.close();
	
	vector<int> v(arr, arr + n);
	make_heap(v.begin(), v.end(), [](int a, int b) {return a > b; });
	sort_heap(v.begin(), v.end(), [](int a, int b) {return a > b; });
	ofstream fo("output.txt");
	for (int i = 0; i < n; ++i)
	{
		fo << v[i] << ' ';
	}
		fo.close();
	delete[] arr;
	return 0;
}