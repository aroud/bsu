#include <fstream>
#include <cstdlib>
using namespace std;

int main()
{
	ifstream fi("input.txt");
	ofstream fo("output.txt");
	long long n;
	fi >> n;
	char ch[100];
	_i64toa_s(n, ch, 100, 2);
	int l = strlen(ch);
	for (int i = l - 1, j = 0; i >= 0; --i)
	{
		if (ch[i]-'0')
			fo << j << "\n";
		j++;
	}
	return 0;
}