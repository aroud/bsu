#pragma once
#include "Matrix.h"

Matrix gauss(Matrix& A, Matrix& f, int& swapNumber)
{

	int size = A.size_x;
	int size_sol = f.size_y;
	//матрица решений:
	Matrix solutions(size,size_sol);
	solutions.nullify();
	


	//проход по диагональным:
	for (int i = 0; i < size - 1; ++i) {
		//поиск главного элемента:
		float maxElement = abs(A.matrix[i][i]);
		int maxIndex = i;
		int k = 0;
		for (k = i + 1; k < size; ++k) 
		{
			if (abs(A.matrix[k][i]) > maxElement) 
			{
				maxIndex = k;
				maxElement = abs(A.matrix[k][i]);
			}
		}
		
		// обмен строк:
		if (i != maxIndex)
		{
			A.matrix[i].swap(A.matrix[maxIndex]);
			f.matrix[i].swap(f.matrix[maxIndex]);
			++swapNumber;
		}

	
		//пересчет свободных членов, элементов матрицы
		for (int k = i + 1; k < size; ++k) 
		{
			float l = (float)(A.matrix[k][i] / A.matrix[i][i]);
			for (int j = i; j < size; ++j) 
			{
				A.matrix[k][j] -= (l * A.matrix[i][j]);
			}
			for (int j = 0; j < size_sol; ++j)
			{
				f.matrix[k][j] -= (l * f.matrix[i][j]);
			}
		}
	}

	//если матрица вырожденна€:
	bool b = false;
	for (int i = 0; i < size; ++i)
	{
		if (A.matrix[i][i] == 0)
			b = true;
	}
	if (b)
	{
		throw Bad("¬ырожденна€ матрица");
	}

	//подсчет решений:
	for (int j = 0; j < size_sol; ++j) {
		for (int i = size - 1; i >= 0; --i) {
			float y = 0;
			for (int k = i + 1; k < size; ++k) {
				y += A.matrix[i][k] * solutions.matrix[k][j];
			}
			solutions.matrix[i][j] = (f.matrix[i][j] - y) / A.matrix[i][i];
		}
	}
	return solutions;
}


