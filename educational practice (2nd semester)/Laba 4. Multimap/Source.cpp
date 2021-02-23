#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <Windows.h>
using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "1. �������� �������� �� ��������� ��������� (�� ������� ��� �� ������� �����������)" << endl;
	cout << "2.������� �������" << endl;
	cout << "3.�����  ���������� ���������, ����� ������� ����� �" << endl;
	cout << "4.����������  �������� ���� �������� (�����������)" << endl;
	cout << "5. ������ ��������" << endl;
	cout << "6. ���������  �����������" << endl;
	cout << "7.����� �� ���������" << endl;
	cout << "0.������� multimap" << endl;
	int temp = 0;
	multimap<double, string, greater<double>> m = { {10,"������"},{20,"������"}, {30,"�������"},{30,"��������"},{20,"�������"} };
	multimap<double, string, greater<double>> mequal = { {10,"������"},{20,"������"}, {30,"�������"},{30,"��������"},{20,"�������"} };
	multimap<double, string> mforins = { {100,"������1"},{100,"������2"}, {100,"������3"} };
	multimap<double, string, greater<double>> mchange = {{50,"��������"}, {60,"������"},{70,"������"} };
	for (auto it = m.begin(); it != m.end(); ++it)
		cout << '(' << (*it).first << ',' << (*it).second << ')' << ' ';
	while (temp != 7)
	{
		cin >> temp;
		switch(temp)
		{
		case 0:
		{
			for (auto i : m)
				cout << i.first << ' ' << i.second << endl;
			break;
		}
		case 1:
		{
			m.insert(mforins.begin(), mforins.end());
			break;
		}
		case 2:
		{
			cout << "Enter age" << endl;
			double t;
			cin >> t;
			auto it = m.find(t);
			if (it != m.end())
				m.erase(it);
			break;
		}
		case 3:
		{
			cout << "Enter K" << endl;
			double t;
			cin >> t;
			cout << m.count(t) << endl;
			break;
		}
		case 4:
		{
			m.swap(mchange);
			break;
		}
		case 5:
		{
			cout << "Enter age" << endl;
			double t;
			string s;
			cin >> t;
			auto itf = m.find(t);
			m.erase(itf);
			cout << "Enter new age and name" << endl;
			cin >> t >> s;
			m.insert(make_pair(t, s));
			break;
		}
		case 6:
		{
			if (m > mequal)
				cout << "Is greater"<<endl;
			else
			{
				if (m == mequal)
					cout << "Is equal" << endl;
				else
					cout << "is less" << endl;
			}
			break;
		}
		default:
			break;
		}
	}
	system("pause");
	return 0;
}
