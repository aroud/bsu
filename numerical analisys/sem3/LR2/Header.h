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


//successive over-relaxation - метод релаксации
template <typename T>
Matrix<T> SOR(Matrix<T> A, Matrix<T> f, T eps, T w, int& counter)
{
	if (f.size_y != 1)
		throw Bad();
	Matrix<double> x0(f.size_x, 1, true);
	for (int i = 0; i < 10; ++i)
		x0[i][0] = f[i][0] / A[i][i];
	Matrix<double> xk = x0;
	Matrix<double> xk1 = xk;

	do {
		xk = xk1;
		for (int i = 0; i < xk.size_x; ++i)
		{
			double sum1 = 0, sum2 = 0;
			for (int j = 0; j < i; ++j)
				sum1 += A[i][j] * xk1[j][0];
			for (int j = i + 1; j < xk.size_x; ++j)
				sum2 += A[i][j] * xk[j][0];
			xk1[i][0] = (1 - w) * xk[i][0] + w / A[i][i] * (f[i][0] - sum1 - sum2);

		}
		counter++;
	} while (maximum_norm(xk1 - xk) > eps);
	cout << maximum_norm(xk1 - xk) << endl;
	return xk1;
}

