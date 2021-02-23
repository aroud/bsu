#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <iterator>
#include <thread>
#include <numeric>
#include <complex>
#include <initializer_list>
#include <functional>
#include <utility>
#include <new>
#include <climits>
#include <cassert>
#include <algorithm>
#include <iomanip>

#include <vector>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <list>
#include <array>
#include <bitset>
#include <unordered_map>
#include <unordered_set>

#include <random>
#include <time.h>

using namespace std;

struct Bad
{
	char str[100];
	Bad() { strcpy_s(str, "Error"); }
	Bad(const char* s) { strcpy_s(str, s); }
};
