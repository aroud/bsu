#include "Matrix.h"
#include "Header.h"


int main()
{
	setlocale(LC_ALL, "rus");

	ifstream fiB("B.txt");
	ifstream fiC("C.txt");
	Matrix<double> B(fiB);
	Matrix<double> C(fiC);
	Matrix<double> A = B + C *2;
	int n = 0;
	double eps = 1 / pow(10, 6);
	auto p = power_iteration(A, eps, n);
	cout << A << p.first << p.second << n << endl;
	n = 0;
	auto p2 = power_iteration_symmetric(A, eps, n);
	cout << A << p2.first << endl << p2.second << n << endl;
	system("pause");
	return 0;
}