#include <fstream>
#include <cmath>
#include <limits>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

template<typename T>
class Matrix
{
public:
	explicit Matrix(size_t size = 0, T value = 0) : n(size)  {
		if (n)
		{
			items = new T * [n];
			for (int i = 0; i < n; ++i)
			{
				items[i] = new T[n];
			}
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					items[i][j] = value;
		}
	}
	Matrix(const Matrix<T>& m): n(m.n)
	{
		if (n)
		{
			items = new T * [n];
			for (int i = 0; i < n; ++i)
			{
				items[i] = new T[n];
			}
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					items[i][j] = m[i][j];
		}
	}
	Matrix(Matrix&& m) : n(m.n)
	{
		items = m.items;
		m.items = nullptr;
		m.~Matrix();
	}

	Matrix& operator=(const Matrix& m)
	{
		if (items) {
			for (int i = 0; i < n; ++i)
				delete[] items[i];
			delete[] items;
		}
		n = m.n;
		items = new T * [n];
		for (int i = 0; i < n; ++i)
		{
			items[i] = new T[n];
		}
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				items[i][j] = m[i][j];
		return *this;
	}

	Matrix& operator=(Matrix&& m)
	{
		if (items) {
			for (int i = 0; i < n; ++i)
				delete[] items[i];
			delete[] items;
		}
		n = m.n;
		items = m.items;
		m.items = nullptr;
		m.~Matrix();
		return *this;
	}

	~Matrix() {
		if (items)
		{
			for (int i = 0; i < n; ++i)
				delete[] items[i];
			delete[] items;
		}
	}

	inline T* operator[] (int i) const
	{
		return items[i];
	}

	void setInfRowColumn(int row, int column) {
		for (int i = 0; i < n; ++i)
		{
			items[row][i] = numeric_limits<T>::max();
			items[i][column] = numeric_limits<T>::max();
		}
	}
	size_t n;
	T** items;
};

template<typename T>
class Node
{
public:
	Node(Matrix<T>& parentMatrix, int level, int i, int j) :
		reducedMatrix(parentMatrix), level(level), vertex(j), cost(0) {
		if (level)
		{
			reducedMatrix.setInfRowColumn(i, j);
		}
		reducedMatrix[j][0] = numeric_limits<T>::max();
	}
	
	Matrix<T> reducedMatrix;
	T cost = 0;
	int vertex;
	int level;
};

template<typename T>
T subtractFromMatrix(Matrix<T>& m) 
{
	T result = 0;
	size_t n = m.n;
	T min;
	for (int i = 0; i < n; ++i)
	{
		min = numeric_limits<T>::max();
		for (int j = 0; j < n; ++j)
		{
			if (m[i][j] < min)
			{
				min = m[i][j];
			}
		}
		for (int j = 0; j < n; ++j)
		{
			if (m[i][j] != numeric_limits<T>::max())
			{
				m[i][j] -= min;
			}
		}
		result += (min==numeric_limits<T>::max())?0:min;
	}

	for (int j = 0; j < n; ++j)
	{
		min = numeric_limits<T>::max();
		for (int i = 0; i < n; ++i)
		{
			if (m[i][j] < min)
			{
				min = m[i][j];
			}
		}
		for (int i = 0; i < n; ++i)
		{
			if (m[i][j] != numeric_limits<T>::max())
			{
				m[i][j] -= min;
			}
		}
		result += (min == numeric_limits<T>::max()) ? 0 : min;
	}

	return result;
}

template<typename T>
class comp {
public:
	bool operator()(const Node<T>& n1, const Node<T>& n2) 
	{
		return n1.cost > n2.cost;
	}
};



template <typename T>
T solve(Matrix<T>& source, int n)
{
	priority_queue<Node<T>, vector<Node<T>>, comp<T>> pq;

	Node<T> root(source, 0, -1, 0);
	root.cost = subtractFromMatrix(root.reducedMatrix);
	pq.push(root);

	while (!pq.empty())
	{
		Node<T> min (pq.top());
		pq.pop();

		int i = min.vertex;

		if (min.level == n - 1)
		{
			return min.cost;
		}

		for (int j = 0; j < n; ++j)
		{
			if (min.reducedMatrix[i][j] != numeric_limits<T>::max())
			{
				Node<T> child (min.reducedMatrix, min.level + 1, i, j);
				/*T t1 = min.cost;
				T t2 = min.reducedMatrix[i][j];
				T t3 = subtractFromMatrix(child.reducedMatrix);
				child.cost = t1 + t2 + t3;*/
				child.cost = min.cost + min.reducedMatrix[i][j] + subtractFromMatrix(child.reducedMatrix);
				pq.push(child);
			}
		}
	}
}




int main()
{
	ifstream fi("input.txt");
	ofstream fo("output.txt");
	int n;
	fi >> n;

	Matrix<double> source(n, 0);

	vector<double> x_in(n);
	vector<double> y_in(n);

	for (int i = 0; i < n; i++)
	{
		fi >> x_in[i] >> y_in[i];
	}


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				source[i][j] = sqrt((x_in[i] - x_in[j]) * (x_in[i] - x_in[j]) + (y_in[i] - y_in[j]) * (y_in[i] - y_in[j]));
			}
			else
			{
				source[i][j] = numeric_limits<double>::max();
			}
		}
	}

	fo << solve(source, n) << '\n';

	/*long double INF = LDBL_MAX;
	Matrix<long double> m;
	m.items=
	{
	   {INF, 20,   18,   12,   8},
	   {5,   INF, 14,   7,   11},
	   {12,   18,   INF, 6,   11},
	   {11,   17,   11,   INF, 12},
	   {5,   5,   5,   5,   INF}
	};
	cout << solve(m, m.size());*/
	return 0;
}
