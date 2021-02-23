#pragma once
//Подключить к структуре, в Visitor 
#include <iostream>
#include <fstream>
#include <iterator>
#include <utility>
#include <stack>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <Bits.h>

using namespace std;


struct Bad
{
	char str[100];
	Bad() { strcpy_s(str, "Error"); }
	Bad(const char* s) { strcpy_s(str, s); }
};

template <typename T, typename U>
T StrToType(const U& rhs) {
	T res; std::stringstream ss(rhs);
	ss >> res;
	return res;
}

template <typename T>
std::string TypeToStr(const T& rhs) {
	std::stringstream ss;
	ss << rhs;
	return ss.str();
}