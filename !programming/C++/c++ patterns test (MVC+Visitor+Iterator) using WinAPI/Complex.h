#pragma once
#include "Package.h"
class Complex
{
public:
	Complex():re(0),im(0){}
	Complex(int r,int i) :re(r), im(i) {}
	Complex& operator= (const Complex a)
	{
		re = a.re;
		im = a.im;
		return *this;
	}
	friend istream& operator>> (istream& is, Complex& a)
	{
		is >> a.re;
		is >> a.im;
		return is;
	}
	friend ostream& operator<< (ostream& os,const Complex& a)
	{
		os << a.re;
		os << "+";
		os << a.im;
		os << "i";
		return os;
	}
	int re;
	int im;
};

string Complex_to_string(const Complex a)
{
	string str = "";
	str += to_string(a.re);
	str += "+";
	str += to_string(a.im);
	str += "i";
	return str;
	
}