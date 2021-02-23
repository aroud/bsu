#include <iostream>
#include <algorithm>
#include <fstream>
#include <list>
#include <array>
#include <iterator>
#include <Windows.h>
using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "1.Просмотреть состояние списка" << endl;
	cout << "2.Удалить несколько элементов с заданной позиции" << endl;
	cout << "3.Добавить несколько элементов в заданную позицию c другого list" << endl;
	cout << "4. Добавить несколько элементов из массива" << endl;
	cout << "5. Поиск наибольшего отсортированного диапазона" << endl;
	cout << "8. Поменять знаки на противоположные" << endl;
	cout << "6.Выход из программы" << endl;
	int temp = 0;
	list <int> l = { 1,4,3,6,11,9 };
	list<int>k = { 0,0,0 };
	/*array<int,3>a = { 10,10,10 };*/
	int arr[] = { 10,10,10 };
	auto ITbegin = l.begin();
	auto ITend = l.begin();
	list<int>::iterator it;
	while (temp != 6)
	{
		cin >> temp;
		switch (temp)
		{
		case 1:
			copy(l.begin(), l.end(), ostream_iterator<int>(cout, " ")); //вывод
			cout << endl;
			break;
		case 2:
			int k1, k2; //удаление
			cout << "Введите диапазон удаления:\n";
			cin >> k1 >> k2;
			advance(ITbegin, k1);
			advance(ITend, k2);
			l.erase(ITbegin, ITend);
			for (auto& i : l)
				cout << i << ' ';
			cout << endl;
			ITbegin = l.begin();
			ITend = l.begin();
			break;
		case 3: //вставка из списка по позиции
			int n;
			cout << "Введите позицию для вставки:\n";
			cin >> n;
			advance(ITbegin, n);
			l.insert(ITbegin, k.begin(), k.end());
			ITbegin = l.begin();
			copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
			cout << endl;
			break;
		case 4:
			/*array<int, 3>a = { 10,10,10 };
			l.insert(l.end(),a.begin(), a.end());*/
			for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
				l.emplace_back(arr[i]);
			}
			copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
			cout << endl;
			break;
		case 5: //наибольший отсортированный диапазон
			cout << "l:";
			for (int& i : l) std::cout << ' ' << i;
			it = is_sorted_until(l.begin(), l.end());
			cout << endl << *it << " -первый неотсортированный элемент";
			cout << endl << "Количество отсортированных: " << distance(l.begin(), it) << endl;
			break;
		case 8:
			transform(l.begin(), l.end(), l.begin(), [](int a) {return -a; });
			for (int& i : l) std::cout << ' ' << i;
		default:
			break;
		}

	}
	system("pause");
	return 0;
}