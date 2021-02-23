#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

void wave_expansion(vector<vector<int>>& v, vector<pair<short, short>>& start_coord)
{
	/*
		v: прямоугольное поле
		start_coord: точка входа
	*/
	short n = v.size();
	short m = v[0].size();
	int k = start_coord.size();
	queue<pair<short, short>> q;
	for (int i = 0; i < k; ++i)
	{
		short s_x = start_coord[i].first;
		short s_y = start_coord[i].second;
		v[s_x][s_y] = 0;
		q.emplace(s_x, s_y);
	}
	
	
	short i, j;
	
	while (!q.empty())
	{
		auto temp = q.front();
		q.pop();
		i = temp.first - 1;        //вверх
		j = temp.second;
		if ((i >= 0) && v[i][j] != -3 && ((v[i][j] == -2)  || v[temp.first][temp.second] < v[i][j]-1))
		{
			v[i][j] = v[temp.first][temp.second] + 1;
			q.emplace(i, j);
		}
		i = temp.first + 1;         //вниз
		j = temp.second;
		if ((i <= n - 1) && v[i][j] != -3 && ((v[i][j] == -2) || v[temp.first][temp.second] < v[i][j]-1))
		{
			v[i][j] = v[temp.first][temp.second] + 1;
			q.emplace(i, j);
		}
		i = temp.first;				//влево
		j = temp.second - 1;
		if ((j >= 0) && v[i][j] != -3 && ((v[i][j] == -2) || v[temp.first][temp.second] < v[i][j]-1))
		{
			v[i][j] = v[temp.first][temp.second] + 1;
			q.emplace(i, j);
		}
		i = temp.first;            //вправо
		j = temp.second + 1;
		if ((j <= m - 1) && v[i][j] != -3 && ((v[i][j] == -2) || v[temp.first][temp.second] < v[i][j]-1))
		{
			v[i][j] = v[temp.first][temp.second] + 1;
			q.emplace(i, j);
		}
	}
}


int main()
{
	/*
	Input:
		  -3: стена
		  -2: свободное поле
		vamp: стартовые координаты
		 n,m: размеры поля
	*/

	ifstream fi("vampires.in");
	int n, m;
	fi >> n >> m;
	vector<vector<int>> v(n);
	vector<pair<short, short>> vamp;
	char x[2];
	fi.getline(x, 2, '\n');
	for (int i = 0; i < n; ++i)
	{
		string temp;
		getline(fi, temp);
		for (int j = 0; j < temp.length(); ++j)
		{
			if (temp[j] == '.')
				v[i].push_back(-2);
			if (temp[j] == '#')
				v[i].push_back(-3);
			if (temp[j] == 'V')
			{
				v[i].push_back(-2);
				vamp.emplace_back(i, j);
			}
		}
	}
	fi.close();

	wave_expansion(v, vamp);


	ofstream fo("vampires.out");
	int max = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (v[i][j] > max)
				max = v[i][j];
		}
	}
	fo << max;
	fo.close();
	return 0;
}