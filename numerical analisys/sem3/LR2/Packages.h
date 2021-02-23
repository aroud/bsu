#pragma once
#include <cmath>
#include <math.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
using namespace std;

struct Bad
{
	char str[100];
	Bad() { strcpy_s(str, "Error"); }
	Bad(const char* s) { strcpy_s(str, s); }
};
