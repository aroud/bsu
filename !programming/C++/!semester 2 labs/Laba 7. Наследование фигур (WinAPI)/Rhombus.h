#pragma once
#include "KShape.h"
//задаем параллелограм длинами половин диагоналей l1,l2,углом a между ними и центром ромба (x,y)
class Rhombus :
	public KShape
{
public:
	Rhombus() :l1(60), l2(30), a(M_PI / 3),KShape() {};
	Rhombus(int l1, int l2) :l1(l1), l2(l2), a(M_PI / 3), KShape() {};
	Rhombus(int l1, int l2, int x, int y, double angle) :l1(l1), l2(l2), a(M_PI / 3), KShape(x, y, angle) {};
	Rhombus(int x, int y,double angle) :l1(60), l2(30), a(M_PI / 3), KShape(x, y,angle) {};
	void ChangeA(double a1)
	{
		double an = a1 * M_PI / 180;
		a = an;
	}
	virtual void print(HDC& hdc)
	{
		if (visible)
		{
			int xa = -l1;
			int ya = 0;
			int xb = -l2 * cos(a);
			int yb = -l2 * sin(a);
			int xc = l1;
			int yc = 0;
			int xd = l2 * cos(a);
			int yd = l2 * sin(a);
			int Xa = x + xa * cos(angle) + ya * sin(angle);
			int Ya = y - xa * sin(angle) + ya * cos(angle);
			int Xb = x + xb * cos(angle) + yb * sin(angle);
			int Yb = y - xb * sin(angle) + yb * cos(angle);
			int Xc = x + xc * cos(angle) + yc * sin(angle);
			int Yc = y - xc * sin(angle) + yc * cos(angle);
			int Xd = x + xd * cos(angle) + yd * sin(angle);
			int Yd = y - xd * sin(angle) + yd * cos(angle);
			MoveToEx(hdc, Xa, Ya, NULL);
			LineTo(hdc, Xb, Yb);
			LineTo(hdc, Xc, Yc);
			LineTo(hdc, Xd, Yd);
			LineTo(hdc, Xa, Ya);
			LineTo(hdc, Xc, Yc);
			MoveToEx(hdc, Xb, Yb, NULL);
			LineTo(hdc, Xd, Yd);
		}
	}
	virtual void Explode(double f)
	{
		factor = f;
		l1 = f * l1;
		l2 = f * l2;
	}
	int l1;
	int l2;
	double a;
};

