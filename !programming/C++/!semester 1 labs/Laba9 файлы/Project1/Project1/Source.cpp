#include "Convert.h"
#include "Part1.h"
#include "Part2.h"
int main()
{
	int kf = startfilm();  //kоличество fильмов)))
	int kc = strartcode();

	ifstream fif("Ischodniy.bin");   /*получение 2 массивов, состоящих из кодов и фильмов, дальше будем их сливать в итоговый класс Kfilm*/
	arrfilm* af = new arrfilm[kf];
	for (int i = 0; i < kf; ++i)
	{
		fif >> af[i].b;
	}
	fif.close();
	ifstream fib("ischodniy kody.bin");
	arrcode* ac = new arrcode[kc];
	for (int i = 0; i < kc; ++i)
	{
		fib >> ac[i].b;
	}
	fib.close();

	/*qsort(af, kf, sizeof(arrfilm), arrfcompare);
	qsort(ac, kc, sizeof(arrcode), arrccompare);*/
	Kfilm* f = new Kfilm[kf];            //слияние
	for (int i = 0; i < kf; ++i)
	{
		for (int j = 0; j < kc; ++j)
		{
			if (af[i].b.fcode == ac[j].b.fcode)
			{
				Kfilm fcopy(ac[j].t, af[i].t);
				f[i] = fcopy;
			}
		}
	}
	
	ofstream outb1("M1.bin");
	for (int i = 0; i < kf; ++i)
	{
		outb1 << f[i];
	}
	outb1.close();
	
	ofstream outt("Output.txt");
	
	ofstream outb2("M2.bin");
	menu(f, kf);
	
	for (int i = 0; i < kf; ++i)
	{
		outt >> f[i] << '\n';
		outb2 << f[i];
	}
	
	outb2.close();
	outt.close();
	
	delete[] f;
	delete[] af;
	delete[] ac;
	system("pause");
	return 0;
}
