#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <iterator>
#include <set>
#include <cmath>
#include <locale>
#include <stack>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

class Rational {
public:
	Rational(): num(0),denom(1) {}

	Rational(int numerator, int denominator) {
		if (!denominator)
			throw invalid_argument("Invalid argument");
		num = numerator;
		denom = denominator;
		Normalize();
	}

	int Numerator() const {
		return num;
	}

	int Denominator() const {
		return denom;
	}
	bool operator<(Rational const& r)const
	{
		return (r - (*this)).Numerator() > 0;
	}
	Rational& operator+= (Rational const& r2)
	{
		num = num * r2.Denominator() + r2.Numerator() * denom;
		denom *= r2.Denominator();
		Normalize();
		return *this;
	}
	Rational& operator-= (Rational const& r2)
	{
		(*this) += (-r2);
		return *this;
	}
	Rational operator+(Rational const& r2)const {
		Rational r(*this);
		r += r2;
		return r;
	}
	Rational operator-(Rational const& r2)const {
		Rational r(*this);
		r -= r2;
		return r;
	}
	Rational operator-()const {
		Rational r(num,-denom);
		return r;
	}
	bool operator==(Rational const& r2)const
	{
		return (num == r2.Numerator()) && (denom == r2.Denominator());
	}
	Rational& operator*= (Rational const& r2)
	{
		num *= r2.Numerator();
		denom *= r2.Denominator();
		Normalize();
		return *this;
	}
	Rational& operator/= (Rational const& r2)
	{
		if (!r2.Numerator())
			throw domain_error("Division by zero");
		num *= r2.Denominator();
		denom *= r2.Numerator();
		Normalize();
		return *this;
	}
	Rational operator*(Rational const& r2)const {
		Rational r(*this);
		r *= r2;
		return r;
	}
	Rational operator/(Rational const& r2)const {
		Rational r(*this);
		r /= r2;
		return r;
	}
	friend ostream& operator<<(ostream& os, Rational const& r)
	{
		os << r.Numerator() << '/' << r.Denominator();
		return os;
	}
	Rational& operator= (Rational const& r)
	{
		change(r.Numerator(), r.Denominator());
		return *this;
	}
	friend istream& operator>>(istream& in, Rational& r)
	{
		int t1, t2;
		if (in >> t1 && in.ignore(1) && in >> t2) {
			Rational t(t1, t2);
			r = t;
		}
		else
			throw runtime_error("wrong input");
		return in;
	}
private:
	void change(int n, int d)
	{
		num = n;
		denom = d;
		Normalize();
	}
	void Normalize() {
		if ((num < 0 && denom < 0) || (num > 0 && denom < 0))
		{
			num = -num;
			denom = -denom;
		}
		if (num == 0)
			denom = 1;
		int temp = abs(num);
		int gcd = GCD(temp, denom);
		num /= gcd;
		denom /= gcd;
	}
	int GCD(int a, int b)
	{
		int t;
		while (b) {
			t = b;
			b = a % b;
			a = t;
		}
		return a;
	}
private:
	int num;
	int denom;
};

int main() {
	try {
		Rational r1,r2;
		string s;
		cin >> r1 >> s >> r2;
		if (s == "+")
			cout << r1 + r2;
		else if (s == "-")
			cout << r1 - r2;
		else if (s == "*")
			cout << r1 * r2;
		else if (s == "/")
			cout << r1 / r2;
	}
	catch (invalid_argument& ia) {
		cout << ia.what();
	}
	catch (domain_error & de) {
		cout << de.what();
	}
	
	catch (runtime_error& re) {
		cout << re.what();
	}

	
	return 0;
}