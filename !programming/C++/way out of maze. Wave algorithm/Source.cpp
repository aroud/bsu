#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct coord //2 координаты
{
	coord(int x, int y) : row(x), col(y), next(nullptr) {}
	coord() : row(-1), col(-1), next(nullptr) {}
	coord(int x, int y, coord *z) : row(x), col(y), next(z) {}
	int row;
	int col;

	coord* next;
};

class KQueue //очередь
{
public:
	KQueue(int _n) :n(_n + 1), end(0), beg(0)
	{
		q = new coord[n];
	}
	virtual ~KQueue() { delete[] q; }
	bool IsEmpty()
	{
		if (beg == end)
			return true;
		return false;
	}
	coord pop()
	{
		if (!IsEmpty())
		{
			coord x = q[beg];
			beg = (beg + 1) % n;
			return x;
		}
	}
	bool push(coord x)
	{
		if ((end + 1) % n == beg)
		{
			cout << "queue is full! ";
			return false;
		}
		q[end] = x;
		end = (end + 1) % n;
		return true;
	}
	int size_of() const
	{
		return (end + n - beg) % n;
	}
private:
	coord *q;
	int end;
	int n;
	int beg;
};

class MyStack
{
public:
	MyStack() { top = nullptr; }
	virtual ~MyStack() { Erase(); }
	void push(coord x)
	{
		coord * a = new coord(x.row, x.col, top);
		top = a;
	}
	coord ftop() { return *top; }
	bool IsEmpty()
	{
		if (top == nullptr)
			return true;
		else return false;
	}
	coord pop() 
	{
		if (!IsEmpty() && top->next != nullptr)
		{
			coord *p = top;
			coord a(*p);
			top = top->next;
			delete p;
			return a;
		}
		if(!IsEmpty() && top->next == nullptr)
		{
			coord *p = top;
			coord a(*p);
			top = 0;
			delete p;
			return a;
		}
	}
	coord* top;
private:
	void Erase() {
		coord *a = top, *b;
		while (a != nullptr) {
			b = a;
			a = a->next;
			delete b;
		}
	}
 };

coord FindExit(int **T,int n,int m,coord start)
{
	coord temp;
	KQueue Q(m*n);
	Q.push(start);
	int i,j;
	while (!Q.IsEmpty() )
	{                                  //вверх
		temp = Q.pop();
		i = temp.row;
		j = temp.col+1;
		if(T[i][j]==-2) //доступна но не исследована
		{
			if ((T[i][j] != -3 && (i == 0 || i == (n - 1) || j == 0 || j == (m - 1))))
		    {
			    T[i][j] = T[temp.row][temp.col] + 1;
				coord res(i, j);
			    return res;
		         
			}
		    else
		    {
			    T[i][j] = T[temp.row][temp.col] + 1;
				coord res(i, j);
			    Q.push(res);
		    }
		}
		i = temp.row+1; //вправо
		j = temp.col;
		if (T[i][j]==-2) //доступна но не исследована
		{
			if ((T[i][j] != -3 && (i == 0 || i == (n - 1) || j == 0 || j == (m - 1))))
			{
				T[i][j] = T[temp.row][temp.col] + 1;
				coord res(i, j);
				return res;

			}
			else
			{
				T[i][j] = T[temp.row][temp.col] + 1;
				coord res(i, j);
				Q.push(res);
			}
		}
		i = temp.row; //вниз
		j = temp.col-1;
		if (T[i][j] == -2) //доступна но не исследована
		{
			if ((T[i][j] != -3 && (i == 0 || i == (n - 1) || j == 0 || j == (m - 1))))
			{
				T[i][j] = T[temp.row][temp.col] + 1;
				coord res(i, j);
				return res;

			}
			else
			{
				T[i][j] = T[temp.row][temp.col] + 1;
				coord res(i, j);
				Q.push(res);
			}
		}
		i = temp.row - 1; //влево
		j = temp.col;
		if (T[i][j] == -2) //доступна но не исследована
		{
			if ((T[i][j] != -3 && (i == 0 || i == (n - 1) || j == 0 || j == (m - 1))))
			{
				T[i][j] = T[temp.row][temp.col] + 1;
				coord res(i, j);
				return res;

			}
			else
			{
				T[i][j] = T[temp.row][temp.col] + 1;
				coord res(i, j);
				Q.push(res);
			}
		}
	}
	
	coord res(-100, -100);
	return res;
}


int main()
{
	ifstream in("Input.txt");
	if (!in)
		cout << "Error of file reading";
	else
	{
		int n, m, stn,stm;
		in >> n >> m >>stn >>stm;
		coord a(stn,stm);
		
		int** T = new int*[n];//матрица
		for (int i = 0; i < n; i++)
			T[i] = new int[m];

		 //чтение
		char x[2];
		in.getline(x, 2, '\n');
		for (int i = 0; i < n; ++i)
		{
			char* c =new char [m+1];
		    in.getline(c, m+1,'\n');
			for (int j = 0; j < m; ++j)
			{
				if (c[j] == ' ')
					T[i][j] = -2;
				if (c[j] == '#')
					T[i][j] = -3;
			}
			delete[]c;
		}
		T[a.row][a.col] = 0;
		
		coord res = FindExit(T, n, m,a);
		
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
				cout << setw(3)<<T[i][j] << ' ';
			cout << endl;
		}
		cout <<endl<< res.row << ' ' << res.col<<endl;

		MyStack ST;
		ST.push(res);
		coord tmp(res.row,res.col);
		if (!(tmp.row==-100 && tmp.col==-100))
		{
			while (!((tmp.row == a.row) && (tmp.col == a.col)))
			{
				if (tmp.row != (n))
				{
					if (T[tmp.row + 1][tmp.col] == T[tmp.row][tmp.col] - 1)
					{
						tmp.row = tmp.row + 1;
						tmp.col = tmp.col;
						ST.push(tmp);
					}
				}
				if (tmp.row != -1)
				{
					if (T[tmp.row - 1][tmp.col] == T[tmp.row][tmp.col] - 1)
					{
						tmp.row = tmp.row - 1;
						tmp.col = tmp.col;
						ST.push(tmp);
					}
				}
				if (tmp.col != -1)
				{
					if (T[tmp.row][tmp.col + 1] == T[tmp.row][tmp.col] - 1)
					{
						tmp.row = tmp.row;
						tmp.col = tmp.col + 1;
						ST.push(tmp);
					}
				}
				if (tmp.col != (m))
				{
					if (T[tmp.row][tmp.col - 1] == T[tmp.row][tmp.col] - 1)
					{
						tmp.row = tmp.row;
						tmp.col = tmp.col - 1;
						ST.push(tmp);
					}
				}
			}

			ofstream fout("Output.txt");
			while (!ST.IsEmpty())
			{
				coord xy = ST.pop();
				T[xy.row][xy.col] = -4;
				fout << '(' << xy.row << ',' << xy.col << ')' << ' ';

			}
			fout << endl;
			T[a.row][a.col] = 0;
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < m; ++j)
				{
					switch (T[i][j])
					{
					case -3: 
					{fout << '#'; break; }
					case -2:
					{fout << ' '; break; }
					case 0:
					{fout << 'S'; break; }
					case -4:
					{fout << '-'; break; }
					default:
					{fout << ' '; break; }
					}
				}
				fout << endl;
			}
			fout.close();
		}
		else
			cout << "no exit";

		for (int i = 0; i < n; i++)
			delete[] T[i];//удаление матрицы и закрытие файлов
		delete[] T;
		in.close();
		
	}
	system("pause");
	return 0;
}