#pragma once
#include "Package.h"
#include "Complex.h"

template <typename T>
class Visitor {
public:
	virtual void visit(T a) = 0;
	virtual ~Visitor() = default;
};

template <typename T>
class SumElements : public Visitor<T> {
public:
	T sum = 0;
public:
	void visit(T ref) override {
		sum += ref;
	}
};

template <typename T>
class FormString : public Visitor<T> {
public:
	string s = "";
public:
	void visit(T ref) override {
		s += to_string(ref);
		s += "\n";
	}
};
template <>
class FormString<Complex> : public Visitor<Complex> {
public:
	string s = "";
public:
	void visit(Complex ref) override {
		s += to_string(ref.re);
		s += '\t';
		s += to_string(ref.im);
		s += "\n";
	}
};

template <typename T>
class MinMax : public Visitor<T> {
public:
	bool firsttime = false;
	T min, max;
public:
	void visit(T ref) override {
		if (!firsttime)
		{
			min = ref;
			max = ref;
		}
		firsttime = true;
		if (ref < min)
			min = ref;
		if (ref > max)
			max = ref;
	}
};
template <>
class MinMax<Complex> : public Visitor<Complex> {
public:
	bool firsttime = false;
	Complex min, max;
public:
	void visit(Complex ref) override {
		if (!firsttime)
		{
			min = ref;
			max = ref;
		}
		firsttime = true;
		if (ref.re < min.re)
			min = ref;
		if (ref.im > max.im)
			max = ref;
	}
};
template <typename T>
class CountElements : public Visitor<T>{
public:
	int count = 0;
public:
	void visit(T ref) override {
		count ++;
	}
};
