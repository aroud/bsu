#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
using namespace std;

class Job
{
public:
	Job(int p, int s, int num) : p(p), s(s), number(num) {}
	bool operator< (Job& j)
	{
		if (p != j.p)
			return p > j.p;
		else
			return s > j.s;
	}
	int p; //-выполнение
	int s; //-загрузка
	int number;
};
long long PV(vector<Job>& v, int k)
{
	long long ll = 0;
	for (size_t i = 0; i < k; ++i)
	{
		ll += v[i].p;
	}
	return ll;
}
long long SV(vector<Job>& v, int k)
{
	long long ll = 0;
	for (size_t i = 0; i < k; ++i)
	{
		ll += v[i].s;
	}
	return ll;
}
int main()
{
	ifstream fi("input.txt");
	ofstream fo("output.txt");

	

	int n = 0, m = 0;
	fi >> m >> n;

	vector<Job> v_j;
	vector<long long>v(n);

	int p, s;
	for (int i = 0; i < n; ++i)
	{
		fi >> s >> p;
		v_j.emplace_back(p, s, i + 1);
	}
	sort(begin(v_j), end(v_j));

	if (n<=m) 
	{
		for (size_t i = 0; i < n; i++) {
			v[i] = v_j[i].p + SV(v_j, i+1);
		}
	}
	else 
	{
		for (int i = 0; i < n; i++) 
		{
			v[i] = v_j[i].p + SV(v_j, i + 1) + PV(v_j, i) / m;
		}
	}
	fo << *max_element(begin(v), end(v)) << '\n';
	
	for (int i = 1; i <= n; ++i)
	{
		int k = i % m ? i % m : m;
		fo << v_j[i - 1].number << ' '<< k;
		fo << "\n";
	}
	return 0;
}