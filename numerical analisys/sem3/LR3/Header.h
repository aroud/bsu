#pragma once
#include "Matrix.h"

//для вектора:
template<typename T>
T maximum_norm(Matrix<T> v)
{
	if (v.size_y != 1)
	{
		throw Bad("not a vector!");
		return 0.;
	}
	else
	{
		T max = v[0][0];
		for (int i = 1; i < v.size_x; ++i)
		{
			if (abs(v[i][0]) > abs(max))
				max = v[i][0];
		}
		return abs(max);
	}
}

template<typename T>
T scalar_product(Matrix<T> v1, Matrix<T> v2)  /*скалярное произведение*/
{
	if (v1.size_y != 1 || v2.size_y != 1)
	{
		throw Bad("not a vector!");
		return 0.;
	}
	if (v1.size_x != v2.size_x)
	{
		throw Bad("not a vector!");
		return 0.;
	}
	T res = 0;
	for (int i = 0; i < v1.size_x; ++i) {
		res += v1[i][0] * v2[i][0];
	}
	return res;
}

template<typename T>
Matrix<T> division(Matrix<T> v1, Matrix<T> v2)  //покоординатное деление
{
	if (v1.size_y != 1 || v2.size_y != 1)
	{
		throw Bad("not a vector!");
	}
	if (v1.size_x != v2.size_x)
	{
		throw Bad("not a vector!");
	}
	Matrix<T> m(v1.size_x, 1);
	for (int i = 0; i < v1.size_x; ++i)
	{
		if (!v2[i][0])
			throw Bad("координата делителя = 0");
		m[i][0] = v1[i][0] / v2[i][0];
	}
	return m;
}

template<typename T>
auto power_iteration(Matrix<T> A,double eps,int& counter)
{
	if (A.size_x != A.size_y)
		throw Bad("not quadratic");

	Matrix<T> y0(A.size_x, 1);
	bool b = true;
	for (int i = 0; i < A.size_x; ++i)
	{
		if (b)
		{
			y0[i][0] = 1;

		}
		/*else
		{
			y0[i][0] = 1;
		}
		b = !b;*/
	}

	auto y1 = A * y0;
	auto lambdaPrev = division(y1, y0);
	auto yPrev = A * y1;
	auto lambda = division(yPrev , y1);

	auto u = yPrev , uPrev = yPrev;
	while (maximum_norm(lambda - lambdaPrev) >= eps)
	{
		++counter;
		auto nu = A * u;
		lambdaPrev = lambda;
		lambda = division(nu, u);
		uPrev = u;
		u = nu / maximum_norm(nu);
	}
	return make_pair(lambda, uPrev);
}

template<typename T>
auto power_iteration_symmetric(Matrix<T> A, double eps, int& counter)
{
	if (A.size_x != A.size_y)
		throw Bad("not quadratic");

	Matrix<T> y0(A.size_x, 1);
	for (int i = 0; i < A.size_x; ++i)
	{
		y0[i][0] = 1;
	}

	auto y1 = A * y0;
	auto lambdaPrev = scalar_product(y1, y0) / scalar_product(y0, y0);
	auto yPrev = A * y1;
	auto lambda = scalar_product(yPrev, y1) / scalar_product(y1, y1);
	auto u = yPrev, uPrev = yPrev;
	while ((lambda - lambdaPrev) >= eps)
	{
		++counter;
		auto nu = A * u;
		lambdaPrev = lambda;
		lambda = scalar_product(nu, u)/ scalar_product(u, u);
		uPrev = u;
		u = nu / maximum_norm(nu);
	}
	return make_pair(lambda, uPrev);
}

