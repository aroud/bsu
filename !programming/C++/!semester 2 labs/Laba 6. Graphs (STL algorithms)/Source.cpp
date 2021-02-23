#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

struct KVertex
{
	KVertex() : Num(-1) { }
	explicit KVertex(int aNum) : Num(aNum) { }
	friend istream& operator >> (istream& is, KVertex& vx)
	{
		return is >> vx.Num;
	}
	friend ostream& operator << (ostream& os, KVertex const& vx)
	{
		return os << "(" << vx.Num  << ")";
	}

	int Num;
};

struct KEdge
{
	KEdge() : b(-1), e(-1) { }
	KEdge(int aNumBeg, int aNumEnd) : b(aNumBeg), e(aNumEnd) { }

	bool operator == (KEdge const& e2) const { return b == e2.b && e == e2.e; }

	friend istream& operator >> (istream& is, KEdge& ed)
	{
		return is >> ed.b >> ed.e;
	}
	friend ostream& operator << (ostream& os, KEdge const& ed)
	{
		return os << "(" << ed.b << "," << ed.e << ")";
	}
	int b;
	int e;
};

int main()
{
	setlocale(LC_ALL, "rus");

	vector<KVertex> vv;
	vector<KEdge>   ve;

	typedef istream_iterator<KVertex> is_iterVert;
	typedef istream_iterator<KEdge>   is_iterKEdge;
	typedef vector<KEdge>::iterator iterator;

	ifstream fi("inv.txt");
	ofstream fo("outv.txt");

	if (fi)
	{
		copy(is_iterVert(fi), is_iterVert(), back_inserter(vv));
		fo << "List of vertexes: ";
		copy(vv.begin(), vv.end(), ostream_iterator<KVertex>(fo, " "));
	}
	else
	{
		cout << "File inv.txt is not open"; return 0;
	}
	fo << endl;
	for (auto& x : vv) cout << x << ' ';
	cout << endl;
	fi.close();

	fi.open("ine.txt");
	if (fi)
	{
		copy(is_iterKEdge(fi), is_iterKEdge(), back_inserter(ve));
		fo << "List of edges: ";
		copy(ve.begin(), ve.end(), ostream_iterator<KEdge>(fo, " "));
	}
	else
	{
		cout << "File ine.txt is not open"; return 0;
	}
	fo << endl;
	for (auto& x : ve) cout << x << ' ';
	cout << endl;
	fi.close();
	fo.close();

	auto itM = max_element(vv.begin(), vv.end(), [](KVertex const& x, KVertex const& y) { return x.Num < y.Num; });
	vector<pair<KVertex, int>> vi(itM->Num + 1, make_pair(KVertex(), 0));
	for_each(vv.begin(), vv.end(), [&vi](KVertex const& x) {vi[x.Num].first = x; });
	for_each(ve.begin(), ve.end(), [&vi](KEdge const& y) {vi[y.b].second++; });
	for (auto i = vi.begin(); i != vi.end(); i++)
		cout << '(' << (*i).first.Num << ',' << (*i).second << ')' << ' ';
	cout << endl;

	//remove_copy_if(vi.begin(), vi.end(), ostream_iterator<pair<KVertex, int>>(cout, " "), [](const pair<KVertex, int> &p) {return p.second == 1; }));

	for (auto it = vi.begin(); it != vi.end(); ++it)
		if (!(((*it).second == 1) || ((*it).first.Num == -1)))
			cout << '(' << (*it).first.Num << ')' << ' ';
	cout << endl;
	system("pause");
	return 0;
}