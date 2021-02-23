#include "Matrix.h"
#include "Header.h"



int main()
{
	setlocale(LC_ALL, "rus");
	Matrix<double> A(10,10,true);
	cout << "матрица A изначальная:" << endl << A << endl;
	A = A * A.transpose();
	cout << "матрица A симметрическая + положительно определенная:" << endl << A << endl;
	/*A = A * (0.01);
	A = A * (2);
	cout << "матрица A в -10,10:" << endl << A << endl;
	A.matrix_round(2);
	cout << "матрица A с необходимым округлением:" << endl << A << endl;*/
	Matrix<double> x(10, 1,true);
	cout << "точное решение x:" << endl << x <<endl;
	Matrix<double> f = A * x;
	cout << "вектор f:" << endl << f << endl;
	double eps = 0.00001;

	int counter02 = 0;
	double w02 = 0.2;
	Matrix<double> xk1 = SOR(A, f, eps, w02, counter02);
	cout << "||xk1-x|| 0.2: " << endl << maximum_norm(xk1 - x) << endl;

	int counter05 = 0;
	double w05 = 0.5;
	xk1 = SOR(A, f, eps, w05, counter05);
	cout << "||xk1-x|| 0.5: " << endl << maximum_norm(xk1 - x) << endl;

	int counter08 = 0;
	double w08 = 0.8;
	xk1 = SOR(A, f, eps, w08, counter08);
	cout << "||xk1-x|| 0.8: " << endl << maximum_norm(xk1 - x) << endl;

	int counter1 = 0;
	double w1 = 1;
	xk1 = SOR(A, f, eps, w1, counter1);
	cout << "||xk1-x|| 1.: " << endl << maximum_norm(xk1 - x) << endl;
	
	int counter13 = 0;
	double w13 = 1.3;
	xk1 = SOR(A, f, eps, w13, counter13);
	cout << "||xk1-x|| 1.3: " << endl << maximum_norm(xk1 - x) << endl;
	
	int counter15 = 0;
	double w15 = 1.5;
	xk1 = SOR(A, f, eps, w15, counter15);
	cout << "||xk1-x|| 1.5: " << endl << maximum_norm(xk1 - x) << endl;

	
	int counter18 = 0;
	double w18 = 1.8;
	xk1 = SOR(A, f, eps, w18, counter18);
	cout << "||xk1-x|| 1.8: " << endl << maximum_norm(xk1 - x) << endl;

	cout <<  counter02 << ' ' << counter05 << ' ' << counter08 << ' ' << counter1 << ' ' << counter13 << ' ' << counter15 << ' '  << counter18 << ' ' << endl;
	system("pause");
	return 0;
}
