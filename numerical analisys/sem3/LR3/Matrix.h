#pragma once
#include "Packages.h"
template <typename T>
class Matrix
{
public:
	Matrix(int nx, int ny, bool) :size_x(nx), size_y(ny)
	{
		
		random_device generator;
		uniform_int_distribution<> distribution(-1000, 1000);
		vector < vector<T>> matrix1(size_x);
		for (auto it = matrix1.begin(); it != matrix1.end(); ++it)
		{
			for (int i = 0; i < size_y; ++i)
			{
				int temp = distribution(generator);
				T t = temp;
				t /= 100;
				(*it).push_back(t);
			}
		}
		matrix = matrix1;
	}
	Matrix(int nx, int ny) :size_x(nx), size_y(ny)
	{
		vector < vector<T>> matrix1(size_x);
		for (auto it = matrix1.begin(); it != matrix1.end(); ++it)
		{
			for (int i = 0; i < size_y; ++i)
			{
				(*it).push_back(0);
			}
		}
		matrix = matrix1;
	}
	Matrix(ifstream& fi)
	/*¬вод: разеры матрицы + сама матрица, через побел*/
	{
		fi >> size_x >> size_y;
		vector <vector<T>> matrix1(size_x);
		for (auto it = matrix1.begin(); it != matrix1.end(); ++it)
		{
			for (int i = 0; i < size_y; ++i)
			{
				T t;
				fi >> t;
				(*it).push_back(t);
			}
		}
		matrix = matrix1;
	}
	void matrix_round(int p)
	{
		for (int i = 0; i < size_x; ++i)
			for (int j = 0; j < size_y; ++j)
				matrix[i][j] = round(matrix[i][j] * pow(10,p)) / pow(10, p);
	}
	Matrix<T> operator* (Matrix<T> const m)
	{
		int sizex1 = (*this).size_x;
		int sizey1 = (*this).size_y;
		int sizex2 = m.size_x;
		int sizey2 = m.size_y;
		if (sizey1 != sizex2)
			return(*this);
		Matrix<T> temp(sizex1, sizey2);
		temp.nullify();
		for (int i = 0; i < sizex1; i++)
			for (int k = 0; k < sizey2; k++)
				for (int j = 0; j < sizex2; j++)
					temp.matrix[i][k] += ((*this).matrix[i][j]) * (m.matrix[j][k]);
		return temp;
	}
	Matrix<T> operator* (T c)
	{
		Matrix<T> temp = *this;
		for (int i = 0; i < temp.size_x; ++i)
			for (int j = 0; j < temp.size_y; ++j)
				temp[i][j] *= c;
		return temp;
	}
	Matrix<T> operator/ (T c)
	{
		Matrix<T> temp = *this;
		for (int i = 0; i < temp.size_x; ++i)
			for (int j = 0; j < temp.size_y; ++j)
				temp[i][j] /= c;
		return temp;
	}
	Matrix<T> operator+ (Matrix<T> const m)
	{
		Matrix<T> temp(m.size_x, m.size_y);
		temp.nullify();
		for (int i = 0; i < m.size_x; ++i)
			for (int j = 0; j < m.size_y; ++j)
				temp.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
		return temp;
	}
	Matrix<T> operator- (Matrix<T> const m)
	{
		Matrix<T> temp(m.size_x, m.size_y);
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
	friend ostream& operator<< (ostream& os, Matrix<T> const m)
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
	Matrix transpose()
	{
		Matrix<T> At(size_y, size_x);
		for (int i = 0; i < size_x; ++i)
			for (int j = 0; j < size_y; ++j)
				At.matrix[j][i] = matrix[i][j];
		return At;
	}
	vector<T>& operator[] (int i)
	{
		return matrix[i];
	}

	int size_x;
	int size_y;
	vector<vector<T>> matrix;
};