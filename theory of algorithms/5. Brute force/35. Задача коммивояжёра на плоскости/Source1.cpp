#include <fstream>
#include <cmath>
#include <limits>
#include <vector>
#include <list>
#include <algorithm>


using namespace std;



template<typename T>
class Matrix {
public:
	/*explicit Matrix(int size = 0, T value = 0) :items(size, std::vector<T>(size, value)), rows(size), columns(size) {
		initRowsColumns();
	}*/

	inline vector<T>& operator[] (int i)
	{
		return items[i];
	}

	inline int size() {
		return items.size();
	}


	inline int rowIndex(int row) {
		return rows[row];
	}


	inline int columnIndex(int column) {
		return columns[column];
	}



	void removeRowColumn(int row, int column) {
		rows.erase(begin(rows) + row);
		columns.erase(begin(columns) + column);
		items.erase(items.begin() + row);
		for (int i = 0; i < items.size(); i++)
			items[i].erase(items[i].begin() + column);
	}



	inline void initRowsColumns() {
		for (int i = 0; i < rows.size(); i++)
		{
			rows[i] = i;
			columns[i] = i;
		}
	}

	vector<vector<T>> items;
	vector<int> rows;
	vector<int> columns;
};


Matrix<double> source;

double record = DBL_MAX;
double inf = DBL_MAX;
vector<pair<int, int>> best_path;
vector<int> result;
vector<pair<int, int>> last_path;


double zeroValue(Matrix<double>& m, int row, int column) {

	double row_min = DBL_MAX;
	double column_min = DBL_MAX;
	int n = m.size();

	for (int i = 0; i < n; ++i) {
		if (i != row)
		{
			if (row_min > m[i][column])
			{
				row_min = m[i][column];
			}
		}
		if (i != column)
		{
			if (column_min > m[column][i])
			{
				column_min = m[column][i];
			}
		}
	}

	return row_min + column_min;
}


pair<int, int> findBestZero(Matrix<double>& m)
{
	vector<pair<int, int>> zeroes;
	vector<double> values;
	double max_val = -1;
	int n = m.size();

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (!m[i][j])
			{
				double val = zeroValue(m, i, j);
				if (max_val <= val)
				{
					max_val = val;
					zeroes.emplace_back(i, j);
					values.push_back(val);
				}

			}
		}
	}

	for (int i = 0; i < zeroes.size(); ++i)
	{
		if (values[i] == max_val)
			return zeroes[i];
	}
}

double subtractFromMatrix(Matrix<double>& m)
{
	double result = 0;
	int n = m.size();
	double min;
	for (int i = 0; i < n; ++i)
	{
		min = DBL_MAX;
		for (int j = 0; j < n; ++j)
		{
			if (m[i][j] < min)
			{
				min = m[i][j];
			}
		}
		for (int j = 0; j < n; ++j)
		{
			if (m[i][j] != DBL_MAX)
			{
				m[i][j] -= min;
			}
		}
		result += min;
	}

	for (int j = 0; j < n; ++j)
	{
		min = DBL_MAX;
		for (int i = 0; i < n; ++i)
		{
			if (m[i][j] < min)
			{
				min = m[i][j];
			}
		}
		for (int i = 0; i < n; ++i)
		{
			if (m[i][j] != DBL_MAX)
			{
				m[i][j] -= min;
			}
		}
		result += min;
	}

	return result;
}


void addInfinity(Matrix<double>& m) {

	int n = m.size();

	vector<bool> infInRow(n);
	vector<bool> infInColumn(n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (m[i][j] == DBL_MAX) {
				infInRow[i] = true;
				infInColumn[j] = true;
			}
		}
	}

	int i;
	for (int k = 0; k < n; k++)
	{
		if (!infInRow[k])
		{
			i = k;
			break;
		}
	}

	for (int j = 0; j < n; j++) {
		if (!infInColumn[j])
		{
			m[i][j] = DBL_MAX;
			break;
		}
	}
}


double cost(vector<pair<int, int>>& v)
{
	double sum = 0;
	for (auto& it : v)
	{
		sum += source[it.first][it.second];
	}
	return sum;
}


void changeIfBetter(vector<pair<int, int>>& v) {
	double cur = cost(v);

	if (record < cur)
	{
		return;
	}

	record = cur;
	best_path = v;
}


void handleMatrix(Matrix<double>& m, vector<pair<int, int>> path, double bottomLimit)
{
	if (m.size() == 2)
	{
		last_path = path;

		int i = (m[0][0] == DBL_MAX) ? 1 : 0;
		path.emplace_back(m.rowIndex(0), m.columnIndex(i));
		path.emplace_back(m.rowIndex(1), m.columnIndex(1 - i));
		changeIfBetter(path);
	}
	else
	{
		Matrix<double> matrix(m);
		bottomLimit += subtractFromMatrix(matrix);

		if (bottomLimit > record)
		{
			last_path = path;
		}
		else
		{
			auto edge = findBestZero(matrix);

			auto m1(matrix);
			m1.removeRowColumn(edge.first, edge.second);


			auto new_path(path);
			new_path.emplace_back(matrix.rowIndex(edge.first), matrix.columnIndex(edge.second));
			addInfinity(m1);



			auto m2(matrix);
			m2[edge.first][edge.second] = DBL_MAX;



			handleMatrix(m1, new_path, bottomLimit);
			handleMatrix(m2, path, bottomLimit);

		}
	}
}



int main()
{

	ifstream fi("input.txt");
	ofstream fo("output.txt");
	int n;
	fi >> n;

	vector<double> x_in(n);
	vector<double> y_in(n);

	double x, y;
	for (int i = 0; i < n; i++)
	{
		fi >> x >> y;
		x_in[i] = x;
		y_in[i] = y;
	}

	if (n == 1)
		fo << 0 << '\n';
	else
	{
		source.items.resize(n);
		for (int i = 0; i < n; ++i)
		{
			source[i].resize(n);
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
					source[i][j] = DBL_MAX;
				}
			}
		}
		source.rows.resize(n);
		source.columns.resize(n);

		source.initRowsColumns();


		handleMatrix(source, vector<pair<int, int>>(), 0);

		fo << record << '\n';
	}
	return 0;
}