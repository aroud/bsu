#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>
#include <sstream>
#include <algorithm>
using namespace std;
int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(0));
	int r = rand() % 100;
	string rand = to_string(r);
	cout << "������� ������: ";
	string s;
	getline(cin, s);
	cout << endl;
	string::iterator it;
	for (it = s.begin(); it < s.end(); it++)
		cout << *it;
	cout << endl;

	istringstream iss(s);
	char ch;
	while (iss >> ch)
	{
		if (isdigit(ch))
		{
			iss.putback(ch);
			int a;
			iss >> a;
			cout << a << endl;
		}
	}


	cout << "������� �����: ";
	string c;
	int ci;
	cin >> ci;
	c = to_string(ci);
	size_t temp = s.find(c);        
	if (temp <= s.size()) { cout << temp; }
	else { cout << "����� �� �������"; }


	size_t k;
	cout << endl << "������� ����� k: ";  
	cin >> k;
	
	if (k <= s.size())
		s.insert(k, rand);
	cout << endl << s;
	s.erase(0,3);
	cout << s<<endl;
	reverse(begin(s), end(s));
	cout << s<<endl;
	string s5 = " ������� ��������! ";
	s.swap(s5);
	cout << s;
	system("pause");
	return 0;
}