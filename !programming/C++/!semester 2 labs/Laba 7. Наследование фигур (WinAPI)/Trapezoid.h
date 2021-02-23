#pragma once
#include "KShape.h"
//Пусть a<b
//x,y - нижняя левая вершина трапеции
//a - верхнее основание
//b - нижнее основание
//h - высота трапеции
//d - проекция левой стороны на нижнее основание


class Trapezoid :
	public KShape
{
public:
	Trapezoid(int x, int y, double angle, int a, int b, int h, int d) :KShape(x, y, angle), a(a), b(b), h(h), d(d) {};
	virtual void print(HDC& hdc)
	{
		if (visible)
		{
			int xa = 0;
			int ya = 0;
			int xb = 0 + d;
			int yb = 0-h;
			int xc = 0 + d + a;
			int yc = 0 - h;
			int xd = 0 + b;
			int yd = 0;

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
			
		}
	}
	virtual void Explode(double f)
	{
		factor = f;
		a = f * a;
		b = f * b;
		h = f * h;
		d = f * d;
	}
	int a;
	int b;
	int h;
	int d;
};

