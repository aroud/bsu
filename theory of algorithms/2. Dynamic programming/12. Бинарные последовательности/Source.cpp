#pragma comment(linker, "/STACK:16777216")

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>


using namespace std;

void str_reverse(char* str) {
	char* str_end = strchr(str, 0);
	std::reverse(str, str_end);
}

void lcs(short** pa, int m, int n, char*& s1, char*& s2)
{
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				pa[i][j] = pa[i - 1][j - 1] + 1;
			}
			else if (pa[i - 1][j] <= pa[i][j - 1])
			{
				pa[i][j] = pa[i][j - 1];
			}
			else if (pa[i - 1][j] > pa[i][j - 1])
			{
				pa[i][j] = pa[i - 1][j];
			}
		}
	}
}

bool prepare(char*& s1, int& m, char*& s2, int& n)
{
	while (m && !(s1[0] - '0'))
	{
		++s1;
		--m;
	}

	while (n && !(s2[0] - '0'))
	{
		++s2;
		--n;
	}
	if (!(m && n))
		return true;
	return false;
}


void backtrack(string& res, int& size, char* s1, char* s2, int i, int j, short** pa)
{
	while (i > 0 && j > 0)
	{
		if (s1[i-1] == s2[j-1])
		{
			res[size] = s1[i-1];
			++size;
			--i;
			--j;
		}
		else if (pa[i][j - 1] < pa[i - 1][j])
		{
			--i;
		}
		else if (pa[i][j - 1] > pa[i - 1][j])
		{
			--j;
		}
		else if (s1[i-1] == '1')
		{
			int t = j;
			while (t && s2[t-1] != '1')
				--t;
			if (pa[i][j] == pa[i][t])
				j = t;
			else
				--i;
		}
		else
		{
			int t = i;
			while (t && s1[t-1] != '1')
				--t;
			if (pa[i][j] == pa[t][j])
				i = t;
			else
				--j;
		}
	}
}

int main()
{
	ifstream fi("input.txt");
	int m, n;
	fi >> m >> n;
	char* s1 = new char[m + 1];
	char* s2 = new char[n + 1];
	fi >> s1 >> s2;
	int msize = max(m, n);
	string res = "";
	res.resize(msize);

	ofstream fo("output.txt");


	int size = 0;
	char* copy_1 = s1, * copy_2 = s2;
	bool b = prepare(s1, m, s2, n);
	if (b)
	{
		fo << 0 << "\n";
		delete[] copy_1;
		delete[] copy_2;
		return 0;
	}

	if (m < n)
	{
		swap(s1, s2);
		swap(m, n);
	}

	str_reverse(s1);
	str_reverse(s2);

	short** pa = new short* [m + 1];
	for (int i = 0; i < m + 1; ++i)
		pa[i] = new short[n + 1];

	for (int i = 1; i <= m; ++i)
		pa[i][0] = 0;
	for (int j = 0; j <= n; ++j)
		pa[0][j] = 0;

	lcs(pa, m, n, s1, s2);
	
	backtrack(res, size, s1, s2, m, n, pa);

	fo << size << "\n";
	for (int i = 0; i < size; ++i)
		fo << res[i];
	fo << "\n";

	for (int i = 0; i < m + 1; ++i)
		delete[] pa[i];
	delete[] pa;

	delete[] copy_1;
	delete[] copy_2;


	return 0;
}
