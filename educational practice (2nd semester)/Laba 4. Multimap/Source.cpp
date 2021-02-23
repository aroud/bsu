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
	cout << "1. Добавить элементы из заданного диапазона (из массива или из другого отображения)" << endl;
	cout << "2.Удалить элемент" << endl;
	cout << "3.Поиск  количества элементов, ключи которых равны К" << endl;
	cout << "4.Обменивает  значения двух объектов (отображений)" << endl;
	cout << "5. Замена элемента" << endl;
	cout << "6. Сравнение  отображений" << endl;
	cout << "7.Выход из программы" << endl;
	cout << "0.Вывести multimap" << endl;
	int temp = 0;
	multimap<double, string, greater<double>> m = { {10,"Иванов"},{20,"Петров"}, {30,"Сидоров"},{30,"Кузнецов"},{20,"Соколов"} };
	multimap<double, string, greater<double>> mequal = { {10,"Иванов"},{20,"Петров"}, {30,"Сидоров"},{30,"Кузнецов"},{20,"Соколов"} };
	multimap<double, string> mforins = { {100,"Иванов1"},{100,"Иванов2"}, {100,"Иванов3"} };
	multimap<double, string, greater<double>> mchange = {{50,"Шевченко"}, {60,"Бобков"},{70,"Волков"} };
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
