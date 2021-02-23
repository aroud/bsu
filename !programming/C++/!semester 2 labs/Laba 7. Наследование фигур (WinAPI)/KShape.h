#pragma once
#define _USE_MATH_DEFINES
#include "KPoint.h"
#include <cmath>
#include <math.h>

class KShape :
	public KPoint
{
public:
	KShape() :KPoint(),angle(0),factor(1) {};
	KShape(int x, int y, double a) :KPoint(x,y), angle(a * M_PI / 180),factor(1) {};
	KShape(double a) :KPoint(), angle(a * M_PI / 180),factor(1) {};
	double angle;
	virtual void Rotate(int a)
	{
		double an = a * M_PI / 180;
		angle = an;
	}
	virtual void print(HDC& hdc)
	{
		if (visible)
		{
			MoveToEx(hdc, x+(-40*factor)*cos(angle) + (40)*sin(angle), (-1)*(-40 * factor)*sin(angle) + y+(40)*cos(angle), NULL);
			LineTo(hdc, x + (+40 * factor)*cos(angle) + (40)*sin(angle), (-1)*(40 * factor)*sin(angle) + y + (40)*cos(angle));
			LineTo(hdc, x + (40 * factor)*cos(angle) + (-40)*sin(angle), (-1)*(40 * factor)*sin(angle) + y + (-40)*cos(angle));
			LineTo(hdc, x + (-40 * factor)*cos(angle) + (-40)*sin(angle), (-1)*(-40 * factor)*sin(angle) + y + (-40)*cos(angle));
			LineTo(hdc, x + (-40 * factor)*cos(angle) + (40)*sin(angle), (-1)*(-40 * factor)*sin(angle) + y + (40)*cos(angle));
		}
		
	}
	virtual void Explode(double f) override
	{
		factor = f;
	}
	double factor;
};

