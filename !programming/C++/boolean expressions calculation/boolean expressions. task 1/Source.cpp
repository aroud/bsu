#pragma optimize("03")
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <fstream>
#include <tuple>
using namespace std;

vector<int> used;

int priority(string& s)
{
	int t;
	if (s[0] == '(')
		t = -1;
	else
	{
		if (s[0] == '~')
			t = 3;
		else {
			if (s == "/\\")
				t = 2;
			else
				t = 1;
		}
	}
	return t;
}
/*
строку в постфиксное
*/
auto parse(ifstream& fi)
{
	int counter_vars = 0;
	vector<string>res;
	string temp;
	stack<string> st;

	
	while (getline(fi, temp, ' '))
	{
		int tlen = temp.length();
		if (temp[tlen - 1] == '\n')
			temp = temp.substr(0, tlen - 1);
		if (temp[0] == 'x')
		{
			res .emplace_back( temp);
			string t;
			for (int i = 1; i < temp.length(); ++i)
				t += temp[i];
			int ti = stoi(t);
			if (find(used.begin(), used.end(), ti) == used.end())
				used.push_back(ti);
			if (ti > counter_vars)
				counter_vars = ti;
			continue;
		}
		if (temp == "1")
		{
			res.emplace_back(temp);
			continue;
		}
		if (temp == "0")
		{
			res.emplace_back(temp);
			continue;
		}
		if (st.empty())   //операции
		{
			st.push(temp);
			continue;
		}
		if (temp[0] == '(')  //левая скобка
		{
			st.push(temp);
			continue;
		}
		if (temp[0] == ')')  //правая скобка
		{
			while (st.top()[0] != '(')
			{
				res.emplace_back(st.top());
				st.pop();
			}
			st.pop();
			continue;
		}
		else
		{
			while (priority(temp) <= priority(st.top()))
			{
				res.emplace_back(st.top());
				st.pop();
			}
			st.push(temp);
		}
	}
	if (!st.empty())
	{
		res .emplace_back(st.top());
		st.pop();
	}
	return make_pair(res, counter_vars);
}

//подсчитать результат

void result(vector<string>& s, ofstream& fo, int n)
{

	int nn = (int)pow(2, n);
	stack<vector<bool>> st;

	vector<vector<bool>> truth_table(n);
	
	int j = nn / 2;
	int counter = 0;
	
	while (j > 0)
	{
		if (find(used.begin(), used.end(), (counter+1)) != used.end())
		{
			for (int t = 0; t < nn; ++t)
				truth_table[counter].push_back(false);
			int l = 1;
			int k = j;
			while (l <= pow(2, counter))
			{
				for (int i = k; i < k + j; ++i)
				{
					truth_table[counter][i] = true;
				}
				++l;
				k += j * 2;
			}
		}
		counter++;
		j /= 2;
	}
	vector<bool> v0(nn);
	vector<bool> v1(nn, true);
	for (int j = 0; j < s.size(); j++)
	{
		if (s[j][0] == 'x')
		{
			string t;
			for (size_t i = 1; i < s[j].length(); ++i)
				t += s[j][i];
			int ti = stoi(t);
			st.push(truth_table[ti - 1]);
			continue;
		}
		if (s[j][0] == '1')
		{
			st.push(v1);
			continue;
		}
		if (s[j][0] == '0')
		{	
			st.push(v0);
			continue;
		}
		if (s[j][0] == '~')
		{
			for (int i = 0; i < nn; ++i)
				st.top()[i] = !st.top()[i];
			continue;
		}
		else
		{
			auto b2 = st.top();
			st.pop();

			if (s[j] == "\\/")
			{
				for (int i = 0; i < nn; ++i)
					st.top()[i] = (st.top()[i] || b2[i]);
				continue;
			}
			if (s[j] == "/\\")
			{
				for (int i = 0; i < nn; ++i)
					st.top()[i] = (st.top()[i] && b2[i]);
				continue;
			}
			if (s[j] == "<=>")
			{
				for (int i = 0; i < nn; ++i)
					st.top()[i] = (st.top()[i] == b2[i]);
				continue;
			}
			if (s[j] == "->")
			{
				for (int i = 0; i < nn; ++i)
					st.top()[i] = (!st.top()[i] || b2[i]);
				continue;
			}
			if (s[j] == "^")
			{
				for (int i = 0; i < nn; ++i)
					st.top()[i] = (st.top()[i] != b2[i]);
				continue;
			}
			if (s[j] == "!")
			{
				for (int i = 0; i < nn; ++i)
					st.top()[i] = (!(st.top()[i] || b2[i]));
				continue;
			}
			if (s[j] == "|")
			{
				for (int i = 0; i < nn; ++i)
					st.top()[i] = (!(st.top()[i] && b2[i]));
				continue;
			}

		}
	}
	for (auto it : st.top())
		fo << it;
}

int main()
{
	ifstream fi("input.txt");

	auto p = parse(fi);
	
	ofstream fo("output.txt");

	int n; /*-число переменных*/
	vector<string> ps = move(p.first);
	n = p.second;

	result(ps, fo , n);

	return 0;
}

