#include <fstream>
#include <stack>
#include <string>
using namespace std;

int main() {

    ifstream fi("input.txt");
    ofstream fo("output.txt");

    string s;
    fi >> s;
    fi.close();

    stack <int> st;

	for (int i = 0; i < s.size(); ++i) {

		if (s[i] == '(' || s[i] == '[' || s[i] == '{') 
		{
			st.push(s[i]);
		}

		else 
		{
			if (st.empty())
			{
				fo << "NO" << "\n" << i << "\n";
				return 0;
			}
			else
			{
				if (s[i] == ')')
				{
					if (st.top() == '(')
					{
						st.pop();
					}
					else
					{
						fo << "NO" << "\n" << i << "\n";
						return 0;
					}
				}
				else
				{
					if (s[i] == ']')
					{
						if (st.top() == '[')
						{
							st.pop();
						}
						else
						{
							fo << "NO" << "\n" << i << "\n";
							return 0;
						}
					}
					else
					{
						if (s[i] == '}')
						{
							if (st.top() == '{')
							{
								st.pop();
							}
							else
							{
								fo << "NO" << "\n" << i << "\n";
								return 0;
							}
						}
					}
				}
			}
		}

		

	}
	if (st.empty())
		fo << "YES" << "\n";
	else
		fo << "NO" << " " << s.size();
	return 0;
}