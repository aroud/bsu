#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <cmath>
#include <vector>
#define M_PI 3.1415926535897932384626433832795
using namespace std;
static const long double cos1 = cos(M_PI / 180);
static const long double sin1 = sin(M_PI / 180);
double f_max(vector<double> a,int n)
{
	double max = a[0];
	for (int i = 1; i < n; ++i)
	{
		if (a[i] - max > 0.000001)
			max = a[i];
		
	}
	return max;
}
double f_min(vector<double> a, int n)
{
	double min = a[0];
	for (int i = 1; i < n; ++i)
	{
		if (a[i] - min < 0.000001)
			min = a[i];
	}
	return min;
}

int main()
{
	double x, y;
	cout << "Vvedite nachalnye koordinaty: x, y"<<endl;
	cin >> x>> y;
	cout << "Vvedite kolichestvo tochek vigury"<<endl;
	int n;
	cin >> n;
	vector <int> napr(n - 1);
	cout << "Vvedite " << n-1 << " napravleniy"<<endl;
	for (int i = 0; i < n-1; ++i)
	{
		cin >> napr[i];
	}
	double xmax;
	double ymax;
	double xmin;
	double ymin;
	double a;
	double b;
	vector <double> elongatedness(90);
	vector <double> xk(n), yk(n);
	xk[0] = x;
	yk[0] = y;
	for (int j = 1; j < n; j++) //вносим координаты
	{
		switch (napr[j-1])
		{
		case 0: {xk[j] = xk[j - 1] + 1; yk[j] = yk[j - 1]; break; }
		case 1: {xk[j] = xk[j - 1] + 1; yk[j] = yk[j - 1] - 1; break; }
		case 2: {xk[j] = xk[j - 1];   yk[j] = yk[j - 1] - 1; break; }
		case 3: {xk[j] = xk[j - 1] - 1; yk[j] = yk[j - 1] - 1; break; }
		case 4: {xk[j] = xk[j - 1] - 1; yk[j] = yk[j - 1]; break; }
		case 5: {xk[j] = xk[j - 1] - 1; yk[j] = yk[j - 1] + 1; break; }
		case 6: {xk[j] = xk[j - 1];   yk[j] = yk[j - 1] + 1; break; }
		case 7: {xk[j] = xk[j - 1] + 1; yk[j] = yk[j - 1] + 1; }
		}
	}
   // поворот и подсчет удлиненности
		for (int l = 0; l < 90; l++)
		{
			for (int e = 0; e < n; e++)
			{
				double rad = (M_PI) / 180;
				double temp = xk[e];
				double temp2 = yk[e];
				xk[e] = (temp * cos1 - sin1 * temp2);
				yk[e] = (temp2 * cos1 + temp * sin1);

			}
			xmax = f_max(xk, n);
			ymax = f_max(yk, n);
			xmin = f_min(xk, n);
			ymin = f_min(yk, n);
			a = (xmax - xmin);
			b = (ymax - ymin);
			if (a - b > 0.000001)
			{
				elongatedness[l] = a / b;
			}
			else //(a - b < 0.000001)
			{
				elongatedness[l] = b / a;
			}
	    }
	double ans = f_max(elongatedness, 90); //вывод ответа
	cout << ans << endl;
	system("pause");
	return 0;
}