#pragma once
#include "Matrix.h"
Matrix thomas_algorithm(vector<float>& a, vector<float>& b, vector<float>& c, vector<float>& f, int n)
{
	vector<float>beta;
	for (int i = 0; i < n + 2; ++i)
		beta.push_back(0.);
	vector<float>alpha;
	for (int i = 0; i < n + 1; ++i)
		alpha.push_back(0.);
	alpha[1] = b[0] / c[0];
	beta[1] = f[0] / c[0];
	for (int i = 1; i <= n - 1; ++i)
	{
		alpha[i + 1] = b[i] / (c[i] - a[i] * alpha[i]);
		beta[i + 1] = (f[i] + a[i] * beta[i]) / (c[i] - a[i] * alpha[i]);
	}
	beta[n + 1] = (f[n] + a[n] * beta[n]) / (c[n] - a[n] * alpha[n]);
	vector<float> y(n + 1);
	y[n] = beta[n + 1];
	for (int i = n - 1; i >= 0; --i)
	{
		y[i] = alpha[i + 1] * y[i + 1] + beta[i + 1];
	}
	Matrix m(n + 1, 1);
	for (int i = 0; i <= n; ++i)
		m.matrix[i][0] = y[i];
	return m;
}


