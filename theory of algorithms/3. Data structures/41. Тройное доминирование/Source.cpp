#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

template <typename T>
class Crew {
public:
    Crew() :x(0), y(0), z(0) {};
    Crew(T x, T y, T z) : x(x), y(y), z(z) {};

    bool operator< (const Crew& rhs) const {
        return z < rhs.z;
    }

    friend istream& operator>>(istream& in, Crew& cr)
    {
        in >> cr.x >> cr.y >> cr.z;
        return in;
    }

    T x;
    T y;
    T z;
};

template <typename U>
class FenwickTreeMin {
public:
    FenwickTreeMin(int n) {
        this->n = n;
        v.resize(n, numeric_limits<U>::max());
    }

    U getMin(int r) const {
        U ret = numeric_limits<U>::max();
        while (r >= 0)
        {
            ret = min(ret, v[r]);
            int f = (r + 1) & r;
            r = f - 1;
        }
        return ret;
    }

    void modify(int i, U val) {
        while (i < n)
        {
            v[i] = min(v[i], val);
            i |= (i + 1);
        }
    }
    U& operator[] (int i) {
        return v[i];
    }
    int getSize() const {
        return n;
    }
private:
    int n;
    vector<U> v;
};

int main()
{
    ifstream fi("input.txt");
    
    int n;
    fi >> n;
    Crew<int> t;
    vector<Crew<int>> v(n);
    for (auto& el: v) {
        fi >> el;
    }
    fi.close();

    sort(begin(v), end(v));
    
    FenwickTreeMin<int> tree(n * 3);

    int res = 0;
    for (auto el : v) {
        int min = tree.getMin(el.y - 1);
        if (el.x < min) {
            tree.modify(el.y - 1, el.x);
            res++;
        }
    }

    ofstream fo("output.txt");
    fo << res << "\n";
    fo.close();

    return 0;
}