#include <iostream> //найти длину максимальной площадки
#include <string>
#include <algorithm>
#include <type_traits>
#include <limits>
#define MAX_INT  2147483647

using namespace std;

static unsigned long long MAX_U_LL = numeric_limits<unsigned long long>::max();

template <bool b, typename T>
struct KSelectValue;

template <typename T>
struct KSelectValue<true, T>
{
	static T GetValue(T v) { return v; }
};

template <typename T>
struct KSelectValue<false, T>
{
	static unsigned long long GetValue(T v) {
		/*auto maxx = numeric_limits<unsigned long long>::max();
		return  maxx;*/
		return MAX_U_LL;
	}
};

template <typename T1, typename T2>
int Func(int& length, int& max, T1 x1, T2 x2)
{
	if ((
		KSelectValue< is_integral<T1>::value, T1>::GetValue(x1) == KSelectValue< is_integral<T2>::value, T2>::GetValue(x2)
		) && (
			KSelectValue< is_integral<T1>::value, T1>::GetValue(x1) != MAX_U_LL) && (KSelectValue< is_integral<T2>::value, T2>::GetValue(x2) != MAX_U_LL
				)
		)
	{
		length++;
		if (length >= max)
			max = length;
	}
	return length;
}

template <typename T1, typename T2, typename ... Args>
int Func(int& length, int& max, T1 x1, T2 x2, Args...args)
{
	if (
		(
			KSelectValue< is_integral<T1>::value, T1>::GetValue(x1) == KSelectValue< is_integral<T2>::value, T2>::GetValue(x2)
			) && (
				KSelectValue< is_integral<T1>::value, T1>::GetValue(x1) != MAX_U_LL
				) && (
					KSelectValue< is_integral<T2>::value, T2>::GetValue(x2) != MAX_U_LL
					)
		)
	{
		length++;
		if (length >= max)
			max = length;
	}
	else
	{
		if (length >= max)
			max = length;
		length = 1;
	}
	auto x3 = x2;
	Func(length, max, x3, args...);
	return max;
}

int main()
{
	int length = 1;
	int max = 0;
	cout << Func(length, max, -2 , 3, 64, 'a', 32,4, 4, 4,(short)12, 3.5, 3.5, 3.5, 3.5, 3.5, 4, 4, string("abc"),4,4)<<endl;
	//cout << Func(length, max, 2, 2, 3.5);
	system("pause");
	return 0;
}