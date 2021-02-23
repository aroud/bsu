#include <vector>
#include <set>
#include <queue>
#include <map>
#include <fstream>


using namespace std;


int main()
{
	ifstream fi("input.txt");
	int m;
	fi >> m;
	vector<int> v(7);
	vector<set<int>> vs(7);
	for (int i = 0; i < m; ++i)
	{
		int t1, t2;
		fi >> t1 >> t2;
		v[t1]++;
		v[t2]++;
		vs[t1].insert(t2);
		vs[t2].insert(t1);
	}
	fi.close();

	bool res = true;

	for (int i = 0; i < 7; ++i)
	{
		if (v[i] % 2 != 0)
			res = false;
	}

	vector<bool> used(7);
	int num;
	for(int i=0;i<7;++i)
		if (!vs[i].empty())
		{
			num = i;
			break;
		}
	queue<int> q;
	q.push(num);
	while (!q.empty())
	{
		int node = q.front();
		q.pop();
		used[node] = true;
		for (auto it = vs[node].begin(); it != vs[node].end(); ++it)
		{
			if (used[*it] == false && node != (*it))
				q.push(*it);
		}
	}
	for (int i = 0; i < 7; ++i)
		if (!used[i] && v[i]!=0)
			res = false;

	ofstream fo("output.txt");
	if (res)
		fo << "Yes";
	else
		fo << "No";
	fo.close();


	return 0;
}