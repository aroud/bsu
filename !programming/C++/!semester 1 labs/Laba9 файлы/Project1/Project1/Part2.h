#ifndef PART2_H__
#define PART2_H__
#include <iostream>
#include <fstream>
#include "Convert.h"
#include "Part1.h"
#include <Windows.h>
int _2MaxTime(Kfilm* a,int k)
{
	int max = 0;
	for (int i = 1; i < k; ++i)
	{
		if (a[i].ftime > a[max].ftime)
			max = i;
	}
	return max;
}
int cmp_film(const void* a1, const void* a2)
{
	Kfilm* b1 = (Kfilm*)a1;
	Kfilm* b2 = (Kfilm*)a2;
	return strcmp(b2->fname,b1->fname);
}
void _6NameSort(Kfilm* a, int k)
{
	qsort(a, k, sizeof(Kfilm), cmp_film);
}
void _3ChangeActor(Kfilm* a, int num)
{
	cout << " ������� ������ ������: ";
	cin.get();
	cin.getline(a[num].factores,19);
}
void _4Del(Kfilm* a, int &k)
{
	for (int i = 0; i < k; ++i)
	{
		if (a[i].fname[0] == 'M')
		{
			for (int j = i; j < k - 1; ++j)
			{
				a[j] = a[j + 1];
			}
			
			k--;
		}
	}
}
void _5Change(Kfilm* a, int k)
{
	int min = 0;
	int max = 0;
	for (int i = 0; i < k; ++i)
	{
		if (a[i].fyear > a[max].fyear)
			max = i;
		if (a[i].fyear < a[min].fyear)
			min = i;
	}
	Kfilm temp;
	temp = a[max];
	a[max] = a[min];
	a[min] = temp;
}
void _1Out(Kfilm* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << a[i].fname << '\t' << a[i].fyear << '\t' << a[i].ftime<<'\n';
	}
}
int menu(Kfilm* arr, int &kf)                 // ����
{
	//setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	cout << "������� �����: " << endl;
	cout << "�������� ������ ������� � ��������� �������� ������, ���� ������� � ������������: 1 " << endl;
	cout << "�������� �������� � ������ ������������ ������������: 2 " << endl;
	cout << "�������� �������� �� ������� ��������� ������; ����������� ������ ������ � ����������: 3 " << endl;
	cout << "������� ������, � ������� �������� ������ ���������� �� ����� �̻: 4 " << endl;
	cout << "�������� ������� ������ � ����������� � ������������ ������ �������: 5" << endl;
	cout << "����������� �������� ������ � ������� ��������: 6" << endl;
	cout << "����� �� ����: 0" << endl;
	int n = 1;
	while (n)
	{
		cin >> n;
		switch (n)
		{
		
		case 1: {_1Out(arr, kf); cout << " ������� ��������� �����: "; break; }
		case 2: { cout >> arr[_2MaxTime(arr, kf)] << endl; cout << " ������� ��������� �����: "; break;
		}
		case 3: 
		{
			int num;
			cout << "������� ����� ������ (��������� ������� � 1, ���� ���������)"<<endl;
			cin >> num;
			_3ChangeActor(arr, num-1);
			cout << " ������� ��������� �����: ";
			break;
		}
		case 4: {_4Del(arr, kf); cout << " ������� ��������� �����: "; break; }
		case 5: { _5Change(arr, kf); cout << " ������� ��������� �����: "; break; }
		case 6: 
		{
			_6NameSort(arr,kf);
			for (int i = 0; i < kf; ++i)
			{
				cout >> arr[i] << '\n';
			}
			cout << " ������� ��������� �����: ";
			break; 
		}
		case 7:
		{
			for (int i = 0; i < kf; ++i)
			{
				cout >> arr[i] << endl;
			}
			break;
		}
		case 0: return 0;
		
		default: return 0;
		}
	}
	
}
#endif
