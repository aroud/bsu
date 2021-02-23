#pragma once
#include "KLoc.h"
class KPoint :
	public KLoc
{
public:
	KPoint() :KLoc(), visible(false) {};
	KPoint(int x, int y) :KLoc(x, y), visible(false) {};
	virtual void print(HDC& hdc)
	{
		if (visible)
			Rectangle(hdc, x - 1, y + 1, x + 1, y - 1);
	}
	void MoveTo(int _x, int _y)
	{
		x = _x;
		y = _y;		
	}
	void Show()
	{
		visible = true;
	}
	void Hide()
	{
		visible = false;
	}
	void Shift(int dx, int dy)
	{
		x += dx;
		y += dy;
	}
	virtual void Rotate(int a) {};
	virtual void Explode(double a) {};
	bool visible;
};

