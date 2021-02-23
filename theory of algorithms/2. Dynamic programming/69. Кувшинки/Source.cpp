#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;


int main()
{
	int n;
	ifstream fi("input.txt");
	fi >> n;
	int* arr = new int[n];

	int t;
	for (int i = 0; i < n; ++i)
	{
		fi >> t;
		arr[i] = t;
	}
	ofstream fo("output.txt");


	int* dp = new int[n];


	dp[0] = arr[0];

	if (n == 2)
	{
		fo << -1;
		return 0;
	}
	if (n >= 3)
	{
		dp[2] = arr[0] + arr[2];
		if (n >= 4)
		{
			dp[3] = arr[0] + arr[3];
			if (n >= 5)
				dp[4] = dp[2] + arr[4];
		}
	}

	for (int i = 5; i < n; ++i)
	{
		dp[i] = max(dp[i - 2], dp[i - 3]) + arr[i];
	}
	fo << dp[n - 1] << '\n';

	for (int i = 0; i < n; ++i)
		cout << dp[i] << " ";
	cout << endl;

	delete[] arr;
	delete[] dp;
	return 0;
}