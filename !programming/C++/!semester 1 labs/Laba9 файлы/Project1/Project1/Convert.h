#ifndef CONVERT_H__/*  в этом файле лежат 2 пары структур для фильмов и для кодов + 2 "надстройки" для массива, состоящие из пары структур.*/
#define CONVERT_H__
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
struct RRecordFilm
{
	RRecordFilm() : fyear(0), ftime(0), fcode(0) { fname[0] = '\0'; ftype[0] = '\0';  factores[0] = '\0'; }
	friend ifstream& operator >> (ifstream& fi, RRecordFilm& rec)
	{
		fi.read((char *)&rec, sizeof(rec));
		return fi;
	}
	friend ofstream& operator << (ofstream&  fo, RRecordFilm const& aRec)
	{
		fo.write((char *)&aRec, sizeof(aRec));
		return fo;
	}
	char fname[15];
	int fyear;
	int ftime;
	char ftype[7];
	int fcode;
	char factores[20];
};
struct KRecordTxt
{
	KRecordTxt(RRecordFilm& aRec) : r(aRec) { }
	RRecordFilm & r;
	friend istream& operator >> (istream& fi, KRecordTxt& aRec)
	{
		string s;
		if (getline(fi, s))
		{
			istringstream ss(s);
			string sf;

			ss.getline(aRec.r.fname, 14, '\t');

			getline(ss, sf, '\t');
			aRec.r.fyear = stoi(sf);//year

			getline(ss, sf, '\t');//time
			aRec.r.ftime = stoi(sf);

			ss.getline(aRec.r.ftype, 6, '\t');//type

			getline(ss, sf, '\t');
			aRec.r.fcode = stoi(sf);//code

			ss.getline(aRec.r.factores, 19, '\n');//actores
		}
		return fi;
	}
	friend ostream& operator << (ostream& fo, KRecordTxt const& rec)
	{
		fo << rec.r.fname << ";" << rec.r.fyear << ";" << rec.r.ftime << ";" << rec.r.ftype << ';' << rec.r.fcode << ';' << rec.r.factores;
		return fo;
	}
};

struct RRecordCode
{
	RRecordCode() : fcode(0) { fstud[0] = '\0'; }
	//	RRecordCode(int kcode, char* kstud) : fcode(kcode) { strncpy(fstud, kstud, 14); }

	friend ifstream& operator >> (ifstream& fi, RRecordCode& rec)
	{
		fi.read((char *)&rec, sizeof(rec));
		return fi;
	}
	friend ofstream& operator << (ofstream&  fo, RRecordCode const& aRec)
	{
		fo.write((char *)&aRec, sizeof(aRec));
		return fo;
	}
	int fcode;
	char fstud[15];
};
struct KRecTxtCode
{
	KRecTxtCode(RRecordCode& aRec) : r(aRec) { }
	RRecordCode & r;

	friend istream& operator >> (istream& fi, KRecTxtCode& aRec)
	{
		string s;
		if (getline(fi, s))
		{
			istringstream ss(s);
			string sf;

			getline(ss, sf, '\t');
			aRec.r.fcode = stoi(sf);//code
			ss.getline(aRec.r.fstud, 14, '\n');//stud
		}
		return fi;
	}
	friend ostream& operator << (ostream& fo, KRecTxtCode const& rec)
	{
		fo << rec.r.fcode << ";" << rec.r.fstud;
		return fo;
	}
};


struct arrfilm
{
	arrfilm():b(),t(b){}
	RRecordFilm b;
	KRecordTxt t;
};
struct arrcode
{
	arrcode() :b(), t(b) {}
	RRecordCode b;
	KRecTxtCode t;
};
#endif