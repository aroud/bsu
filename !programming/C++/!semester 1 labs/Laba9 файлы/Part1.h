#ifndef PART1_H__
#define PART1_H__
#include <iostream>
#include <fstream>
#include "Convert.h"
using namespace std;
struct Kfilm // класс для слияния, основной класс для работы
{
	Kfilm() : fyear(0), ftime(0) { fname[0] = '\0'; fstud[0] = '\0';  ftype[0] = '\0';  factores[0] = '\0'; }
	Kfilm(KRecTxtCode p1, KRecordTxt p2) :fyear(p2.r.fyear), ftime(p2.r.ftime)
	{
		strcpy_s(fname, p2.r.fname);
		strcpy_s(ftype, p2.r.ftype);
		strcpy_s(factores, p2.r.factores);
		strcpy_s(fstud, p1.r.fstud);
	}
	char fname[15];
	int fyear;
	int ftime;
	char ftype[7];
	char fstud[15];
	char factores[20];
	friend ostream& operator >> (ostream& fo, Kfilm const& rec) //написано для проверки, вывод в тхт-файл
	{
		fo << rec.fname << ";" << rec.fyear << ";" << rec.ftime << ";" << rec.ftype << ';' << rec.fstud << ';' << rec.factores;
		return fo;
	}
	friend ofstream& operator << (ofstream&  fo, Kfilm const& a)          //это уже, чтобы получить M1.bin
	{
		fo.write((char *)&a, sizeof(a));
		return fo;
	}
};
int startfilm()  /* тут идет чтение тхт файла и запись bin*/
{
	int counter = 0;
	ifstream fin("Ischodniy.txt");  /* также эти функции вернут нам, сколько элементов (строк) они записали в bin*/
	ofstream fout("Ischodniy.bin");
	RRecordFilm abin;
	KRecordTxt atxt(abin);
	while (fin >> atxt)
	{
		fout << abin;
		counter++;
	}
	fin.close();
	fout.close();
	return counter;
}
int strartcode()
{
	int counter = 0;
	ifstream fi("ischodniy kody.txt");
	ofstream fo("ischodniy kody.bin");
	RRecordCode abinc;
	KRecTxtCode atxtc(abinc);
	while (fi >> atxtc)
	{
		fo << abinc;
		counter++;
	}
	fi.close();
	fo.close();
	return counter;
}
#endif

