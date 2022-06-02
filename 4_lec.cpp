#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <list>
#include <map>

using std::cout;
using std::endl;
using std::string;

// 4th lection

/* ���������� ������:
*
* 1. ��������
* 2. Lambda �������
* 3. STL: Standart Template Library
* 4. ���������� STL
* 5. std::vector<T>
* 6. push_back vs emplace_back
* 7. std::vector<bool>
* 8. iterator
* 9. range for
* 10. std::list<T>
* 11. std::map<keyType, valueType>
* 12. reverse & const iterators
* 13. algorithms
* 14. ������ ��������������: �������
*
*/

void Topic1() { // ��������

	// �������� - �������, ������� ����, ��� �������
	
	// ������� - �����, ������� �������� ()
	// ��������� ������ ��������� � ����������� ������ �������
	// ������� ����� ������������� ������� ����������� ������/�������
	// ������� � ������� ����� ���������������� �������

	class Functor
	{
	public:
		float operator () (float); // ������� ������� ��������� this
	};

	float g(float);

	/*template <typename func_type>
	float f(float x, func_type func)
	{
		float y = x * sin(x);
		return func(y);
	}
	*/


}

void Topic2() { // Lambda �������

	// ������������ - ������������� �������

	auto func = [/*������� ���������� ������� ������*/](int a, float* p) {/*����������*/};

	/*
	* ������� ���������� ������� ������:
	* [=] - ��� �� ��������
	* [&] - ��� �� ������
	* [&, x] - ��� �� ������, � �� ��������
	* [=, &x] - ��� �� ��������, � �� ������
	*/

	// func ����� ���� ��������������� � ��������� �� �������,
	// ���� ��� �������� ���������� ������� ������

	// ������, ����������, ��� ��������� �������� ����

	std::vector<int> srcVec;
	for (int val = 0; val < 10; val++)
	{
		srcVec.push_back(val);
	}

	class MyLambda
	{
	public:
		void operator ()(int _x) const { cout << _x << " "; }
	};

	for_each(srcVec.begin(), srcVec.end(), MyLambda());


	// �� �� �����
	for_each(srcVec.begin(), srcVec.end(), [](int _n)
		{
			cout << _n << " ";
		}
	);

}

void Topic3() { // STL: Standart Template Library
	/*
	* 
	* C standart library
	* -<cmath>, <cstdio>, ��� � namespace std
	* 
	* Streams
	* -cin, cout , file streams, etc
	* 
	* ����������
	* -��������� ��������
	* -����������� ��� �������
	* -��������, ���������
	* 
	* ������, ����������, ����� ���������...
	*/
}

void Topic4() { // ���������� STL

	/*
	* ��������� �������� ������ ����
	* -��� - �������� template
	* 
	* ���������������� ���������� (Sequence containers)
	* -vector, array, deque, list
	* 
	* ������������� ����������
	* -set, multiset - ��������� ������
	* -map, multimap - ��������� ��� ����-��������
	* -���������� ���������� ���������� �� ������, ����� ������ �(log n)
	* 
	* ��������������� ������������� ����������
	* -unordered map, ...
	* -�������� �� hash, multi-���������� ��������� �������
	* ��������� �������� ��� ������ hash
	*/

}

void Topic5() { // std::vector<T>

	/*
	* ���������� ������������ ������
	* 
	* �������� �������� � �������� ������� ������ (������, �� ���������� �������� ������ ���������������)
	* 
	* ������ � ������������� �������� �� �(1)
	* 
	* ���������� �������� � ����� ������� - �(1)
	* 
	* ����������/�������� ��-�� �� �������� - �� �������� �����
	* 
	* size()/resize(newsize) - ���������� ������ �������
	* capacitty()/reserve(newsize) - ����������� ������ �������
	*/

	
	std::vector<unsigned int> myvector;//empty
	unsigned int capacity = myvector.capacity();
	for (unsigned int i = 0; i < 100000; ++i) {
		myvector.push_back(i);//size + 1
		if (capacity != myvector.capacity())
		{
			capacity = myvector.capacity();
			cout << myvector.capacity() << endl;
		}
	}
	/*
	output:
	1
    2
    4
	8
	16
	32
	64
	128
	256
	512
	1024
	2048
	4096
	8192
	16384
	32768
	65536
	131072
	*/
	//��� �����������, ���� ������������ ������ 
	std::vector<unsigned int> myvector;//empty
	unsigned int capacity = myvector.capacity();
	myvector.reserve(100000);
	for (unsigned int i = 0; i < 100000; ++i) {
		myvector.push_back(i); //size + 1
		if (capacity != myvector.capacity())
		{
			capacity = myvector.capacity();
			cout << myvector.capacity() << endl;
		}
	}
	/*
	output:
	100000
	*/
}

void Topic6() { // push_back vs emplace_back
	/*
	* push_back()
	* -������ � ����� ������� ����� ������� ����� �����������
	* -���� lvalue - ������ ������� �����
	* -���� rvalue - ������� ����������� ����������� �� rvalue
	* 
	* emplace_back()
	* -������� � ����� ������� ����� �������
	* -����� ����������� � �������� �����������(��� ������� �����������/�����������
	* -����� �������� explicit ������������
	* -��������� ��������� ��������� ��������(������������ � ����� ������� ����� �������)
	*/


	std::vector<std::pair<std::string, std::string>> vec;

	vec.emplace_back(std::string("Hello"), std::string("world"));
	vec.push_back({ std::string("Hello2"), std::string("world2") });

	for_each(vec.cbegin(), vec.cend(), [](const auto& elem) {
		cout << "printout:�[" << elem.first << ",�" << elem.second << "]" << endl;
		});


	/*
	* ����������� ������ explicit �-���� �� �������� ����������,
	* �� �������� ���������� ���������� emplace_back ����� perfect forward
	*/

	std::vector<std::unique_ptr<int>> v; //�� ����� ��������� ��������, �� ����� ���� ����������
	int a;
	v.emplace_back(&a); //��������� ������� unique_ptr �� a, ���� ������� ptr, �� �� ������� ���������� ������ � unique_ptr
	//v.push_back(&a); //��� ���������, �� a ��� ������
}

void Topic7() { // std::vector<bool>

	/*
	* ��������� ������������� ��� ������������ �������� bool
	* 
	* operator [] ���������� �� ��������
	* 
	* std::vector<bool>::reference 
	* ���������� ��� ��� ������� � ��������� �����
	* 
	* std::vector<bool>::reference::operator bool
	* ������������ ��� ����������� ������������� � bool
	* 
	* ������������� ������ ���������� �������
	* � ������ ��������� �� ���������
	*/

}

void Topic8() { // iterator

	/*
	* ������ ��������� ����� ���� ���������
	* -vector<int>::iterator
	* 
	* �������� ~ ��������� �� ������� ������� ���������� + �������� �������� �� ���������
	* -operator * ������� ��������
	* ���������/��������� (������� �� ����. �������)
	* �����������
	* � = *it
	*/
	std::vector<int> vec;
	std::vector<int>::iterator it;
	for (it = vec.begin();it < vec.end(); it++) {
		cout << *it << endl;
	}
	// vec.end() - ������� �� ���������(�� ��������������)
	for (auto it = vec.begin(); it < vec.end(); it++) {
		cout << *it << endl;
	}


}

void Topic9() { // range for

	// for ( declaration : expression) { statements }

	std::vector<int> vec;

	for (auto const& value: vec) {
		cout << value << endl;
	}

	for (auto value: vec) {
		cout << value << endl;
	}

	std::string str("hello");
	for (auto c : str) {
		std::cout << c << std::endl;
	}

	std::vector<bool> v{ true, false, true, false };
	v[0] = false;

	for (auto& elt : v)
		elt = true;//�compilation�error!
	for (auto && elt:v) // ����� ���� rvalue � lvalue
		elt = true;

}

void Topic10() { // std::list<T>

	// ���������� ���������� ������

	// �������� ����������� ��������� � ������

	// �� ������������ random access

	// ����������� vector ��� ������� � ��������

	// ����������� � ��� �������

	// ���������� ���������� (���������� ����������� ����������, � �� ��������)

	auto PrintOut = [](int p) {cout << "�printout:�" << p << endl; };

	int a = 34, b = 3, c = 44;
	std::list<int> lst;
	lst.push_back(c);
	lst.push_back(a);
	lst.push_back(b);
	lst.sort();
	for_each(lst.begin(), lst.end(), &PrintOut);


}

void Topic11() { // std::map<keyType, valueType>

	/*
	* ������������� ��������� (������-������ ������)
	* 
	* �����������
	* -���������� �����(��� ������������� ���� multimap)
	* -����������� ����� (�(log n)), � ������� (�(log n))
	* -������ ����� operator []
	* -�������� �������� ������ <key, value>
	* -��� ����� ������ ����� operator <
	*/
	auto PrintOut = [](const std::pair<string, int>& p) {
		cout << "printout:�[" << p.first << ",�" << p.second << "]" << endl;
	};

	std::map<string, int> table;
	std::map<string, int>::iterator it;
	table.insert(std::pair<string, int>("a", 5));
	table.insert({ "c",35 });
	table["e"] = 454;
	cout << "table[e]:" << table["e"] << endl;
	it = table.find("c");
	cout << "PrintOut(*it),�where�it�=�table.find(c)" << endl;
	PrintOut(*it);
	cout << "iterating:" << endl;
	for_each(table.begin(), table.end(), &PrintOut);

}

void Topic12() { // reverse & const iterators

	auto PrintOut = [](const std::pair<string, int>& p) {
		cout << "printout:�[" << p.first << ",�" << p.second << "]" << endl;
	};

	std::map<string, int> table;
	std::map<string, int>::iterator it;
	table.insert(std::pair<string, int>("a", 5));
	table.insert({ "c",35 });
	table["e"] = 454;
	cout << "table[e]:" << table["e"] << endl;
	it = table.find("c");
	cout << "PrintOut(*it),�where�it�=�table.find(c)" << endl;
	PrintOut(*it);
	cout << "iterating:" << endl;
	for_each(table.begin(), table.end(), &PrintOut);
	for_each(table.rbegin(), table.rend(), &PrintOut);//reverse
	for_each(table.cbegin(), table.cend(), &PrintOut);//const


}

void Topic13() { // algorithms

	/*
	* ��������� ������� ��� ���������� ���������
	* -��������� = ����������� ������������������ (�������, ����������)
	* 
	* ��������� ��������� ��� ����������, � �� ��� ������������ ������������
	* -����� ��������� ������� ��������: copy ctor, =, ==, !=, <
	* 
	* ��������� �� �������� �������� ���������
	* -find, count, for_each, min_element, binary_search
	* 
	* � ��������� ��������
	* -sort, transform, copy, swap
	*/

	void operator << (std::ostream & os, std::initializer_list<int> const& list) {
		os << "{";
		std::for_each(list.begin(), std::prev(list.end()), [&](int val) {
			os << val << ", ";
			});
		os << *std::prev(list.end()) << "}";
	}

	auto a = { 1, 2, 3, 4 };
	std::cout << a;

	std::string s("hello");
	std::transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c)->unsigned char {
			return std::toupper(c);
		});

	int num_items3 = std::count_if(v.begin(), v.end(), [](int i) {
		return i % 3 == 0;
		});

	std::vector < std::pair<int, string>> v = {
	{108, "John"},
	{32, "Arthur"},
	{108, "Ford"}, };
    std::stable_sort(v.begin(), v.end());

}

void Topic14() { // ������ ��������������: �������

	/*
	* ��������� �������� ������������ ������������� 
	* ���������������� ��� ������������� �����������
	* 
	* ���������� - ������������� ������ �� ������ ���������� � �������
	* 
	* ������:
	* -������� ������������� � ���������� ����� ��� ��������� ���������,
	* ���������� �������������� ����� � ��������� [0, 1]
	* -���������� �������� ����� ��� ��������� ����� � ��������� [0, 100]
	*/

	class ValueGenerator
	{
	public:
		virtual float getNormalizedValue() const = 0;
	};

	class ValueGeneratorStupid : public ValueGenerator
	{
	public:
		float getNormalizedValue() const override
		{
			return static_cast<float> (rand() % 10000) * 0.0001f;
		}
	};

	class ValueGeneratorUniform : public ValueGenerator
	{
	public:
		float getNormalizedValue() const override
		{
			//! C++11 stuff
			std::random_device device;
			std::mt19937 generator(device());
			std::uniform_real_distribution<float> distr(0.0f, 1.0f);
			return distr(generator);
		}
	};

}