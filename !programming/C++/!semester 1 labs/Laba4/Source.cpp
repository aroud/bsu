#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int n;
	cin >> n;
	cout << "¬ведите строку не более " << n << "  символов"<< endl;
	char *s = new char[n];
	cin.get();
	cin.getline(s, n);
	int x=0,i = 0, j = 1, k = 1;
	while (s[j])
	{
		if (s[i] != s[j])
		{
			if (x == 0)
			{
				s[k] = s[j];
				i++;
				j++;
				k++;
			}
			else
			{
				s[i] = s[j];
				j++;
			}
			x = 0;
		}
		else
		{
			j++; x = 1;
		}
	}
	if (x == 0)
		s[k] = s[j];
	else
		s[i] = s[j];
	cout << s << endl;
	
	system ("pause");
	delete[] s;
	return 0;
}

