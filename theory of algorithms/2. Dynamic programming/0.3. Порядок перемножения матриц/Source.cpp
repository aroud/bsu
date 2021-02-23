#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int MAX_INT = 2147483647;

void solution(vector<int>& arr, vector<vector<int>>& vv, int n) {


	for (int l = 2; l <= n; l++)
	{
		for (int i = 1; i <= n + 1 - l; i++) 
		{
			int j = i + l - 1;
			vv[i][j] = MAX_INT;
			for (int k = i; k <= j - 1; k++)
			{
				int t = vv[i][k] + vv[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
				if (vv[i][j] > t)
				{
					vv[i][j] = t;
				}
			}
		}
	}
}


struct MSize
{
	int n;
	int m;
};
int main()
{
	ifstream fi("input.txt");
	int n;
	fi >> n;
	vector<int> arr(n + 1);



	int t1, t2;
	for (int i =0; i < n; ++i)
	{
		fi >> t1 >> t2;
		arr[i] = t1;
	}
	arr[n] = t2;

	
	fi.close();

	ofstream fo("output.txt");

	vector<vector<int>> vv(n+1);
	for (int i = 0; i < n+1; ++i)
		vv[i] = vector<int>(n+1);

	solution(arr, vv, n);

	fo << vv[1][n] << "\n";

	return 0;
}