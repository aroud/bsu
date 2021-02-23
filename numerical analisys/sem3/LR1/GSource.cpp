#include "Gauss.h"
#include "Triagdiagonal.h"
//для вектора:
float maximum_norm(Matrix const v)
{
	if (v.size_y != 1)
	{
		throw Bad("not a vector!");
		return 0.;
	}
	else
	{
		float max = v.matrix[0][0];
		for (int i = 1; i < v.size_x; ++i)
		{
			if (abs(v.matrix[i][0]) > abs(max))
				max = v.matrix[i][0];
		}
		return abs(max);
	}
}
//для верхне-треугольной:
float DetA(Matrix const& m, int numberOfSwaps) {
	float det = pow(-1, numberOfSwaps);
	for (int i = 0; i < m.size_x; ++i) {
		det *= m.matrix[i][i];
	}
	return det;
}

int main()
{
	setlocale(LC_ALL, "rus");
	Matrix A(10,10);
	cout << "матрица A:" << endl << A << endl;
	Matrix x(10, 1);
	cout << "точное решение x:" << endl << x <<endl;
	Matrix f = A * x;
	cout << "вектор f:" << endl << f << endl;
	
	int counter = 0;
	Matrix A_copy1 = A;
	Matrix A_copy2 = A;
	Matrix A_copy3 = A;
	Matrix f_copy1 = f;
	Matrix f_copy2 = f;
	

	Matrix E(10, 10);
	E.nullify();
	for (int i = 0; i < E.size_x; ++i)
		E.matrix[i][i] = 1;
	Matrix E_copy1 = E;
	Matrix X = gauss(A, f, counter);
	
	cout << "решение X:" << endl << X << endl;
	
	cout <<"||AX-f||= "<< maximum_norm(A_copy1 * X - f_copy1) << endl;
	cout <<"||x-X||= " << maximum_norm(x-X) << endl;
	cout << "detA= " << DetA(A,counter) << endl;
	Matrix I = gauss(A_copy2, E_copy1, counter);
	
	cout << "A^(-1)" << endl << I << endl;
	cout << "A^(-1)*A" << endl << I*A_copy3 << endl;

	/*----------------------начало 2ого задания---------------------*/


	cout << endl;
	random_device generator;
	//minstd_rand generator;
	//mt19937_64 generator;
	//default_random_engine generator;
	
	uniform_int_distribution<> distribution(-1000, 1000);
	uniform_int_distribution<> distribution2(2000, 4000);
	vector<float> a,b,c;
	int n = 10;
	for (int i = 0; i < n+1; ++i)
	{
		int temp = distribution(generator);
		float t = temp;
		t /= 100;
		a.push_back(t);
	}
	for (int i = 0; i < n+1; ++i)
	{
		int temp = distribution(generator);
		float t = temp;
		t /= 100;
		b.push_back(t);
	}
	/*чтоб разброс побольше был*/
	for (int i = 0; i < n+1; ++i)
	{
		int temp = distribution2(generator);
		float t = temp;
		t /= 100;
		int tt = distribution(generator);
		if(tt>0)
			c.push_back(t);
		else
			c.push_back(-t);
		
	}
	cout << "a: ";
	for (auto it = a.begin() + 1; it != a.end(); ++it)
		cout << *it << ' ';
	cout << endl;
	cout << "b: ";
	for (auto it = b.begin(); it != b.end()-1; ++it)
		cout << *it << ' ';
	cout << endl;
	cout << "c: ";
	for (auto it = c.begin(); it != c.end(); ++it)
		cout << *it << ' ';
	cout << endl;

	//проверочки

	bool isgood = true;
	for (int i = 0; i < n+1; ++i)
		if (abs(a[i]) == 0 || abs(b[i]) == 0 || abs(c[i]) == 0)
			isgood = false;
	if(abs(c[0])<=abs(b[0]))
		isgood = false;
	if (abs(c[n]) <= abs(a[n]))
		isgood = false;
	for (int i = 1; i <= n - 1; ++i)
	{
		if (abs(c[i]) <= abs(a[i]) + abs(b[i]))
			isgood = false;
	}
	if (isgood) {

		/*заполняю матрицу*/
		Matrix m(11, 11);
		m.nullify();
		for (int i = 0; i <= 10; ++i)
			m.matrix[i][i] = c[i];
		for (int i = 0; i <= 10 - 1; ++i)
			m.matrix[i + 1][i] = -a[i + 1];
		for (int i = 0; i <= 10 - 1; ++i)
			m.matrix[i][i + 1] = -b[i];
		cout << m << endl;
		/*у-рандомная*/
		Matrix y(n + 1, 1);
		Matrix F = m * y;
		vector<float> fv(n + 1);
		for (int i = 0; i <= n; ++i)
		{
			fv[i] = F.matrix[i][0];
		}
		cout << "f:\n" << F;
		cout << "Точное решение:\n" << y << endl;
		Matrix Y = thomas_algorithm(a, b, c, fv, n);
		cout << "решение:\n" << Y << endl;
		cout << "||AX-f||= " << maximum_norm(m * Y - F) << endl;
		cout << "||x-X||= " << maximum_norm(y - Y) << endl;

	}
	system("pause");
	return 0;
}
