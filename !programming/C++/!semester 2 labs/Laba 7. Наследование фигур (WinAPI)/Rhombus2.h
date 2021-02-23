#pragma once
#include "Rhombus.h"
class Rhombus2 :
	public Rhombus
{
public:
	Rhombus2(int x, int y, double angle) :Rhombus(x, y, angle), c1(128), c2(128), c3(128) {};
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
			
			POINT pt[3] = { {Xb, Yb}, {Xc, Yc}, {x,y} };
			HRGN rg;
			rg = CreatePolygonRgn(pt, 3, WINDING);
			FillRgn(hdc, rg, CreateSolidBrush(RGB(c1,c2,c3)));

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
	int c1;
	int c2;
	int c3;
};

