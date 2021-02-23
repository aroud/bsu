#pragma optimize("03")

#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <tuple>
using namespace std;
 
/*вход:
	0 и 1 — формулы.
	Если x — переменная, то x — формула.
	Если A и B — формулы, то ( A op B ) — формула, где op — одна из допустимых бинарных операций.
	Если A — формула, то ( op A ) — формула, где op — одна из допустимых унарных операций.
	Других формул нет.
	унарные операции :
		~ отрицание.
	бинарные операции :
		\/ дизъюнкция;
		/\ конъюнкция;
		-> импликация;
		<=> эквивалентность;
		^ сумма по модулю 2;
		| штрих Шеффера;
		! стрелка Пирса.
*/



int priority(string& s)
{
	int t;
	if (s == "(")
		t = -1;
	else 
	{
		if (s == "~")
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
опеpанды пеpеписываются в выходную стpоку, а знаки опеpаций заносятся в стек на основе следующих сообpажений:

а) если стек пуст, то опеpация из входной стpоки пеpеписывается в стек;

б) опеpация выталкивает из стека все опеpации с большим или pавным пpиоpитетом в выходную стpоку;

в) если очеpедной символ из исходной стpоки есть откpывающая скобка, то он пpоталкивается в стек;

г) закpывающая кpуглая скобка выталкивает все опеpации из стека до ближайшей откpывающей скобки,
сами скобки в выходную стpоку не пеpеписываются, а уничтожают дpуг дpуга.
*/

auto parse(string& s)
{
	int counter_vars = 0;
	string res = "";
	stringstream ss(s);
	string temp;
	stack<string> st;
	/*while (ss >> temp) {

	}*/
	while (getline(ss, temp, ' '))
	{
		if (temp[0] == 'x')
		{
			res += (temp + ' ');
			string t;
			for (int i = 1; i < temp.length(); ++i)
				t += temp[i];
			int ti = stoi(t);
			if (ti > counter_vars)
				counter_vars = ti;
			continue;
		}
		if (temp == "1")
		{
			res += (temp + ' ');
			continue;
		}
		if (temp == "0")
		{
			res += (temp + ' ');
			continue;
		}
		if (st.empty())   //операции
		{
			st.push(temp);
			continue;
		}
		if (temp == "(")  //левая скобка
		{
			st.push(temp);
			continue;
		}
		if (temp == ")")  //правая скобка
		{
			while (st.top() != "(")
			{
				res += (st.top() + ' ');
				st.pop();
			}
			st.pop();
			continue;
		}
		else
		{
			while (priority(temp) <= priority(st.top()))
			{
				res += (st.top() + ' ');
				st.pop();
			}
			st.push(temp);
		}
	}
	if (!st.empty())
	{
		res += (st.top() + ' ');
		st.pop();
	}
	res[res.length() - 1] = ' ';
	
	return make_pair(res,counter_vars);
}

auto BIN(int a, int n) 
{
	vector<bool> v(n);
	for (int i = n-1; i >= 0; i--) {            
		if (a % 2 == 0) { v[i] = false; }
		else {v[i] = true; }
		a = a / 2;
	}
	return v;
}
auto BIN2(int a, int n)
{
	vector<bool> v(n);
	for (int i = n - 1; i >= 0; i--)
	{
		v[n - i - 1] = (a >> i) & 0x01;
	}
	return v;
}

bool result(string& s,vector<bool>& truth_table)
{
	stringstream ss(s);
	stack<bool> st;
	string temp;
	while (getline(ss, temp, ' '))
	{
		if (temp[0] == 'x')
		{
			string t;
			for (int i = 1; i < temp.length(); ++i)
				t += temp[i];
			int ti = stoi(t);
			st.push(truth_table[ti - 1]);
			continue;
		}
		if (temp == "1")
		{
			st.push(true);
			continue;
		}
		if (temp == "0")
		{
			st.push(false);
			continue;
		}
		if (temp == "~")
		{
			bool t = st.top();
			st.pop();
			st.push(!t);
			continue;
		}
		bool b2 = st.top();
		st.pop();
		bool b1 = st.top();
		st.pop();
		if (temp == "\\/")
		{
			st.push(b1 || b2);
			continue;
		}
		if (temp == "/\\")
		{
			st.push(b1 && b2);
			continue;
		}
		if (temp == "<=>")
		{
			st.push(b1 == b2);
			continue;
		}
		if (temp == "->")
		{
			st.push(!b1 || b2);
			continue;
		}
		if (temp == "^")
		{
			st.push(b1 != b2);
			continue;
		}
		if (temp == "!")
		{
			st.push(!(b1 || b2));
			continue;
		}
		if (temp == "|")
		{
			st.push(!(b1 && b2));
			continue;
		}

	}
	bool b = st.top();
	st.pop();
	return b;
}
//string to_normal_code(string);

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);


	ifstream fi("input.txt");
	string s;
	getline(fi, s);
	fi.close();

	ofstream fo("output.txt");

	auto p = parse(s);
	string ps;
	int n;
	ps = p.first;
	n = p.second;

	vector<vector<bool>> truth_table(pow(2, n));
	for (int i = 0; i < pow(2, n); ++i)
		truth_table[i] = BIN(i, n);
	
	/*for (auto& it : truth_table)
	{
		for (int i = 0; i < n; ++i)
			cout << it[i]<<' ';
		cout << endl;
	}*/
	//fo << to_normal_code(ps) << endl;

	vector<bool>res(pow(2, n));
	for (int i = 0; i < pow(2, n); ++i)
	{
		res[i] = result(ps, truth_table[i]);
		fo << res[i];
	}
	fo << endl;

	fo.close();
	return 0;
}


/*
!   ¬		Отрицание(НЕ)
|	|		Штрих Шеффера(И - НЕ)
#	↓		Стрелка Пирса(ИЛИ - НЕ)
*   &		Конъюнкция(И)
+   v		Дизъюнкция(ИЛИ)
^   ⊕		Исключающее ИЛИ, сумма по модулю 2 (XOR)
@	→		Импликация(ЕСЛИ - ТО)
=  ≡(~, ↔)	Эквивалентность(РАВНО)
*/

/*
string normalize(string s)
{
	if (s == "\\/")
		return "+";
	if (s == "/\\")
		return "*";
	if (s == "!")
		return "#";
	if (s == "|")
		return "|";
	if (s == "~")
		return "!";
	if (s == "^")
		return "^";
	if (s == "<=>")
		return "=";
	if (s == "->")
		return "@";
	return "";
}
string to_normal_code(string s)
{
	string res = "";
	stringstream ss(s);
	string temp;

	while (getline(ss, temp, ' '))
	{
		if (temp[0] == 'x' || temp == "1" || temp == "0" || temp == "(" || temp == ")")
		{
			res += (temp + ' ');
			continue;
		}
		else
		{
			temp = normalize(temp);
			res += (temp + ' ');
		}
	}

	res[res.length() - 1] = '\n';
	return res;
}
*/