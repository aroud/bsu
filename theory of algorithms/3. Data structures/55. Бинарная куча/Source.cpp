#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

int main()
{
	ifstream fi("input.txt");
	ofstream fo("output.txt");

	int n;
	fi >> n;
	vector<int> v;
	v.push_back(INT_MIN);
	copy(istream_iterator<int>(fi), istream_iterator<int>(), back_inserter(v));
	bool res = true;
	int t;
	for (int i = n ; i > 1; --i)
	{
		
		t = i / 2;
		if (v[t] > v[i])
		{
			res = false;
			break;
		}
	}
	res ? fo << "Yes" : fo << "No";
	fo << "\n";
	return 0;
}