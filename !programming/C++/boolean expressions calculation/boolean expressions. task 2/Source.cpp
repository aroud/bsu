#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

int priority(char c)
{
	switch (c)
	{
	case '(':
		return -1;
		break;
	case '~':
		return 3;
		break;
	case '/':
		return 2;
		break;
	default:
		return 1;
		break;
	}
}

//для строки и вектора подсчитать результат
bool result(string& s, vector<bool>& truth_table)
{
	stringstream ss(s);
	stack<bool> st;
	string temp;
	/*string ts = "";*/
	int ti;
	bool t, b1,b2;
	while (ss>>temp)
	{
		char c = temp[0];
		switch (c) {
		case 'x':
			st.push(truth_table[stoi(temp.substr(1)) - 1]);
			break;
		case '1':
			st.push(true);
			break;
		case '0':
			st.push(false);
			break;
		case '~':
			t = st.top();
			st.pop();
			st.push(!t);
			break;
		case '\\':
			b2 = st.top();
			st.pop();
			b1 = st.top();
			st.pop();
			st.push(b1 || b2);
			break;
		case '/':
			b2 = st.top();
			st.pop();
			b1 = st.top();
			st.pop();
			st.push(b1 && b2);
			break;
		case '<':
			b2 = st.top();
			st.pop();
			b1 = st.top();
			st.pop();
			st.push(b1 == b2);
			break;
		case '-':
			b2 = st.top();
			st.pop();
			b1 = st.top();
			st.pop();
			st.push(!b1 || b2);
			break;
		case '^':
			b2 = st.top();
			st.pop();
			b1 = st.top();
			st.pop();
			st.push(b1 != b2);
			break;
		case '!':
			b2 = st.top();
			st.pop();
			b1 = st.top();
			st.pop();
			st.push(!(b1 || b2));
			break;
		case '|':
			b2 = st.top();
			st.pop();
			b1 = st.top();
			st.pop();
			st.push(!(b1 && b2));
			break;
		default:
			break;
		}

		
	}
	bool b = st.top();
	st.pop();
	return b;
}

int main()
{
	ifstream fi("input.txt");
	int n = 0;
	string res = "";
	string temp;
	stack<char> st;
	
	/*строку в постфиксное*/
	while (fi >> temp)
	{
		char c = temp[0];
		int ti;
		
		switch (c) {
		case 'x':
			res += (temp + ' ');
			ti = stoi(temp.substr(1));
			if (ti > n)
				n = ti;
			break;
		case '1': case '0':
			res += (temp + ' ');
			break;
		case '(':
			st.push(c);
			break;
		case ')':
			while (st.top() != '(')
			{
				res += st.top();
				res += ' ';
				st.pop();
			}
			st.pop();
			break;
		default:
			if (st.empty())   //операции
			{
				st.push(c);
				break;
			}
			while (priority(c) <= priority(st.top()))
			{
				res += (st.top() + ' ');
				st.pop();
			}
			st.push(c);
			break;
		}
	}
	if (!st.empty())
	{
		res += (st.top() + ' ');
		st.pop();
	}
	res[res.length() - 1] = ' ';
	/*-----------------------------------------------*/

	ofstream fo("output.txt");
	
	vector<bool> truth_table(n);
	for (int a = 0; a < pow(2, n); ++a)
	{
		for (int i = n - 1; i >= 0; i--)
		{
			truth_table[n - i - 1] = (a >> i) & 0x01; /*генерация вектора*/
		}
		fo << result(res, truth_table); /*подсчиатать результат*/
	}

	return 0;
}