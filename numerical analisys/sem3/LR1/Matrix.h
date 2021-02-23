#pragma once
#include "Packages.h"
class Matrix
{
public:
	Matrix(int nx, int ny) :size_x(nx), size_y(ny)
	{
		
		random_device generator;
		// generator;
		//mt19937_64 generator;
		//default_random_engine generator;
		uniform_int_distribution<> distribution(-1000, 1000);
		vector < vector<float>> matrix1(size_x);
		for (auto it = matrix1.begin(); it != matrix1.end(); ++it)
		{
			for (int i = 0; i < size_y; ++i)
			{
				int temp = distribution(generator);
				float t = temp;
				t /= 100;
				(*it).push_back(t);
			}
		}
		matrix = matrix1;
	}
	Matrix operator* (Matrix const m)
	{

		int sizex1 = (*this).size_x;
		int sizey1 = (*this).size_y;
		int sizex2 = m.size_x;
		int sizey2 = m.size_y;
		if (sizey1 != sizex2)
			return(*this);
		Matrix temp(sizex1, sizey2);
		temp.nullify();
		for (int i = 0; i < sizex1; i++)
			for (int k = 0; k < sizey2; k++)
				for (int j = 0; j < sizex2; j++)
					temp.matrix[i][k] += ((*this).matrix[i][j]) * (m.matrix[j][k]);
		return temp;
	}
	Matrix operator- (Matrix const m)
	{
		Matrix temp(m.size_x, m.size_y);
		temp.nullify();
		for (int i = 0; i < m.size_x; ++i)
			for (int j = 0; j < m.size_y; ++j)
				temp.matrix[i][j] = matrix[i][j] - m.matrix[i][j];
		return temp;
	}
	void nullify()
	{
		for (int i = 0; i < size_x; ++i)
			for (int j = 0; j < size_y; ++j)
				matrix[i][j] = 0;
	}
	friend ostream& operator<< (ostream& os, Matrix const m)
	{

		for (int i = 0; i < m.size_x; ++i)
		{
			for (int j = 0; j < m.size_y; ++j)
			{
				os.width(12);
				os << m.matrix[i][j] << ' ';
			}
			os << endl;
		}
		return os;
	}
	int size_x;
	int size_y;
	vector<vector<float>> matrix;
};