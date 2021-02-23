//Рудь Андрей, 7 группа
//unordered_map
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class student             //пользовательский тип: конструкторы, операторы equality_comparing
{
public:
	student() :mark(4),name(""){}
	student(string name_, int mark) : mark(mark),name(name_){}
	student(const student& st2):mark(st2.mark),name(st2.name){}
	string name;
	int mark;
	friend bool operator== (const student& st1,const student& st2);
	friend bool operator!= (const student& st1, const student& st2);

};

bool operator== (const student& st1, const student& st2)
{
	return st1.name==st2.name;
}

bool operator!= (const student& st1, const student& st2)
{
	return st1.name != st2.name;
}

namespace std {         // хеш-функция для student      
	template <> struct hash<student>
	{
		size_t operator()(const student & x) const
		{
			return hash<int>()(x.mark);
		}
	};
}

unordered_map<student, string> function(unordered_map<student, string> a)
{
	return a;
}

int main()
{
	setlocale(LC_ALL, "rus");
	/*3. Все возможные конструкторы*/

	unordered_map<int, string> umap1; /*-умолчанию*/
	// конструкторы с новыми аллокаторами, хеш функциями, equality-comparator-ами -- пропускаю
	unordered_map<int, string> umap1_2(umap1); /*-копирующий*/
	unordered_map<int, string> umap2(50); /*-количество бакетов*/
	umap2[1] = "Иванов";
	umap2[10] = "Petrov";
	umap2[30] = "Sokolov";
	vector<pair<int, string>>v = { make_pair(1,"abc1"),make_pair(2,"abc2"),make_pair(3,"abc3"),make_pair(4,"abc4") };
	unordered_map<int, string> umap2_2(v.begin(),v.end());  /*-по итераторам*/
	for (auto &it : umap2_2)
		cout << it.first << ' ' << it.second << endl;
	unordered_map<int, string> umap2_3(v.begin(), v.end(),50); /*-итераторы и количество бакетов*/
	/*перемещающие конструкторы -- пропускаю*/
	cout << endl;
	unordered_map<int, string> umap3 = { make_pair(1,"xyz1"),make_pair(2,"xyz2"),make_pair(3,"xyz3"),make_pair(4,"xyz4") }; /*-initializer_list*/
	for (auto &it : umap3)
		cout << it.first << ' ' << it.second << endl;
	/*--------------------------------*/

	/*Тестирование для пользовательских типов
	4)7)8)*/
	unordered_map<student, string> umap;
	string n4 = "Kuznetsov";
	string n5 = "Orlov";
	student a("Ivanov", 5);
	student b("Petrov", 10);
	student c("Popov", 4);

	umap.insert(make_pair(a,"удовлетворительно"));             //insert()
	umap[b] = "отлично";                                       //oprator[]
	umap[c] = "удовлетворительно";
	if (!umap.empty())                                         //empty()
		cout << "size: " << umap.size() << endl;               //size()
	cout << "max_size: " << umap.max_size() << endl;           //max_size()
	unordered_map<student, string> unmap; 
	unordered_map<student, string> unmap2;

	unmap2 = unmap = umap;                                     //operator=

	for (auto it = unmap.cbegin(); it != unmap.cend(); ++it)   //cbegin(),cend() по map
		cout << (*it).first.name<<' ';   
	cout << endl;
    unmap.clear();                                             //clear()

	for (auto & it : umap)                                     //erase()
		cout << it.first.name << ' ';
	cout << endl;
	umap.erase(umap.begin(),--umap.end());
	for (auto & it : umap)
		cout << it.first.name << ' ';
	cout << endl;

	swap(umap, unmap2);                                        //swap()
	for (auto & it : umap)
		cout << it.first.name << ' ';
	cout << endl;
	
	umap.emplace(student(n4, 10), string("хорошо"));//emplace()
	
	umap.emplace_hint(umap.begin(),make_pair(student(n5, 7), string("хорошо")));
	for (auto & it : umap)
		cout << it.first.name << ' ';
	cout << endl;
	                                                          //emplace_hint()
	
	auto it = umap.find(b);                                   //find
	if (it != umap.end())
	{
		cout << (*it).first.name << endl;
		cout << "Value for student b: " << umap.at(b) << endl;           //at
	}
	for (auto & it : umap)
		cout << it.first.name<<' ';
	cout << endl;
	cout << "bucket_count: " << umap.bucket_count() << endl;
	cout << "max_bucket_count: " << umap.max_bucket_count() << endl;
	cout << "load_factor: " << umap.load_factor() << endl;
	double d = 0.7;
	umap.max_load_factor(d);
	cout << "max_load_factor " << umap.max_load_factor() << endl;
	cout << "size: " << umap.size() << endl;

	cout << umap.bucket(b) << endl;                         //номер бакета по ключу
	for (auto it = umap.begin(7); it != umap.end(7); ++it)  //итераторы по бакету
		cout << (*it).first.name << ' ';
	cout << endl;
	/* -----------------------------*/
	/*6)*/
	unordered_map<student, string> mapA(function(umap));
	unordered_map<student, string> map = function(mapA);
	for (auto & it : map)
		cout << it.first.name << ' ';
	cout << endl;
	/*---------------------*/
	/* 11)
	примеры использования хеш-таблиц (А.Бхаргава "Грокаем алгоритмы", СПб.: Питер, 2017. - 288 с.: ил.) 
	-создание связь, отображающую один объект на другой
	-нахождение значения в списке
	-исключение дубликатов
	-Кэширование/запоминание данных вместо выполнения работы на сервере
	*/
	system("pause");
	return 0;
}