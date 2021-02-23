#pragma once
#include <windows.h>
class KLoc     
{
public:
	KLoc() :x(0), y(0) {};
	KLoc(int _x, int _y) :x(_x), y(_y) {};
	int x;
	int y;
};

