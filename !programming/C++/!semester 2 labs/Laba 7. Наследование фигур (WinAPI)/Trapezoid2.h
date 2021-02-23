#pragma once
#include "Trapezoid.h"
class Trapezoid2 :
	public Trapezoid
{
public:
	Trapezoid2(const Trapezoid& t) :Trapezoid(t) {
		c11 = 150;
		c12 = 150;
		c13 = 150;
		c21 = 80;
		c22 = 80;
		c23 = 80;
	};
	virtual void print(HDC& hdc)
	{
		if (visible)
		{
			int xa = 0;
			int ya = 0;
			int xb = 0 + d;
			int yb = 0 - h;
			int xc = 0 + d + a;
			int yc = 0 - h;
			int xd = 0 + b;
			int yd = 0;
			int xn = d;
			int yn = 0;
			int ym = 0;
			int xm = d + a;

			int Xa = x + xa * cos(angle) + ya * sin(angle);
			int Ya = y - xa * sin(angle) + ya * cos(angle);
			int Xb = x + xb * cos(angle) + yb * sin(angle);
			int Yb = y - xb * sin(angle) + yb * cos(angle);
			int Xc = x + xc * cos(angle) + yc * sin(angle);
			int Yc = y - xc * sin(angle) + yc * cos(angle);
			int Xd = x + xd * cos(angle) + yd * sin(angle);
			int Yd = y - xd * sin(angle) + yd * cos(angle);
			int Xn = x + xn * cos(angle) + yn * sin(angle);
			int Yn = y - xn * sin(angle) + yn * cos(angle);
			int Xm = x + xm * cos(angle) + ym * sin(angle);
			int Ym = y - xm * sin(angle) + ym * cos(angle);

			POINT pt1[3] = { {Xa, Ya}, {Xb, Yb}, {Xn,Yn} };
			HRGN rg1;
			rg1 = CreatePolygonRgn(pt1, 3, WINDING);
			FillRgn(hdc, rg1, CreateSolidBrush(RGB(c11, c12, c13)));

			POINT pt2[3] = { {Xc, Yc}, {Xm, Ym}, {Xd,Yd} };
			HRGN rg2;
			rg2 = CreatePolygonRgn(pt2, 3, WINDING);
			FillRgn(hdc, rg2, CreateSolidBrush(RGB(c21, c22, c23)));

			MoveToEx(hdc, Xa, Ya, NULL);
			LineTo(hdc, Xb, Yb);
			LineTo(hdc, Xc, Yc);
			LineTo(hdc, Xd, Yd);
			LineTo(hdc, Xa, Ya);			
			MoveToEx(hdc, Xc, Yc, NULL);
			LineTo(hdc, Xm, Ym);
			MoveToEx(hdc, Xb, Yb, NULL);
			LineTo(hdc, Xn, Yn);
		}
	}
	int c11;
	int c12;
	int c13;
	int c21;
	int c22;
	int c23;

};
