#include <iostream>
//#include <stdlib.h>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int *a = new int[n];
	for (int j = 0;j < n;j++)
	{
		cin >> a[j];
	}
	int *d = new int[n];
	for (int i = 0;i < n; ++i)
	{
		d[i] = 1;
		for (int k = 0; k < i; ++k)
		{
			if (a[k] < a[i])
				d[i] = fmax (d[i], 1 + d[k]);
		}
	}
	int ans = d[0];
	for (int i = 0; i<n; ++i)
		ans = fmax (ans, d[i]);
	cout << ans << endl;
	system("pause");
	return 0;
}