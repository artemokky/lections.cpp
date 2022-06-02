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

/* Содержание лекции:
*
* 1. Функторы
* 2. Lambda функции
* 3. STL: Standart Template Library
* 4. Контейнеры STL
* 5. std::vector<T>
* 6. push_back vs emplace_back
* 7. std::vector<bool>
* 8. iterator
* 9. range for
* 10. std::list<T>
* 11. std::map<keyType, valueType>
* 12. reverse & const iterators
* 13. algorithms
* 14. Шаблон проектирования: Адаптер
*
*/

void Topic1() { // Функторы

	// Функторы - объекты, ведущие себя, как функции
	
	// Функтор - класс, имеющий оператор ()
	// Синтаксис вызова совпадает с синтаксисом вызова функции
	// Функтор может дополнительно хранить необходимые данные/объекты
	// Функтор и функция могут специализировать шаблоны

	class Functor
	{
	public:
		float operator () (float); // имеется неявный указатель this
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

void Topic2() { // Lambda функции

	// Семантически - неименованные функции

	auto func = [/*видимые переменные области вызова*/](int a, float* p) {/*реализация*/};

	/*
	* Видимые переменные области вызова:
	* [=] - все по значению
	* [&] - все по ссылке
	* [&, x] - все по ссылке, х по значению
	* [=, &x] - все по значению, х по ссылке
	*/

	// func может быть сконвертировано в указатель на функцию,
	// если нет передачи переменных области вызова

	// лямбда, фактически, это экземпляр функтора выше

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


	// то же самое
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
	* -<cmath>, <cstdio>, все в namespace std
	* 
	* Streams
	* -cin, cout , file streams, etc
	* 
	* Контейнеры
	* -Коллекции объектов
	* -Реализованы как шаблоны
	* -Итератор, алгоритмы
	* 
	* Строки, исключения, умные указатели...
	*/
}

void Topic4() { // Контейнеры STL

	/*
	* Коллекции объектов одного типа
	* -Тип - параметр template
	* 
	* Последовательные контейнеры (Sequence containers)
	* -vector, array, deque, list
	* 
	* Ассоциативные контейнеры
	* -set, multiset - коллекции ключей
	* -map, multimap - коллекции пар ключ-значение
	* -Контейнеры производят сортировку по ключам, время поиска О(log n)
	* 
	* Неупорядоченные ассоциативные контейнеры
	* -unordered map, ...
	* -Хранение по hash, multi-контейнеры позволяют хранить
	* несколько значений для одного hash
	*/

}

void Topic5() { // std::vector<T>

	/*
	* Обобщенный динамический массив
	* 
	* Элементы хранятся в линейном участке памяти (память, на выделенные элементы растет экспоненциально)
	* 
	* Доступ к произвольному элементу за О(1)
	* 
	* Добавление элемента в конец вектора - О(1)
	* 
	* Добавление/удаление эл-та из середины - за линейное время
	* 
	* size()/resize(newsize) - логический размер вектора
	* capacitty()/reserve(newsize) - фактический размер вектора
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
	//Для оптимизации, зная максимальный размер 
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
	* -Кладет в конец вектора новый элемент через копирование
	* -Если lvalue - просто создаст копию
	* -Если rvalue - вызовет конструктор перемещения от rvalue
	* 
	* emplace_back()
	* -Создает в конце вектора новый элемент
	* -Может применяться в качестве оптимизации(нет лишнего копирования/перемещения
	* -Может вызывать explicit конструкторы
	* -Реализует концепцию идеальной передачи(конструирует в конце вектора новый элемент)
	*/


	std::vector<std::pair<std::string, std::string>> vec;

	vec.emplace_back(std::string("Hello"), std::string("world"));
	vec.push_back({ std::string("Hello2"), std::string("world2") });

	for_each(vec.cbegin(), vec.cend(), [](const auto& elem) {
		cout << "printout: [" << elem.first << ", " << elem.second << "]" << endl;
		});


	/*
	* Возможность вызова explicit к-тора не является безопасной,
	* но является следствием реализации emplace_back через perfect forward
	*/

	std::vector<std::unique_ptr<int>> v; //не может разделять владение, не может быть скопирован
	int a;
	v.emplace_back(&a); // пытается создать unique_ptr на a, если удалить ptr, то он вызовет деструктор данных в unique_ptr
	//v.push_back(&a); // не сработает, тк a был удален
}

void Topic7() { // std::vector<bool>

	/*
	* Отдельная специализация для эффективного хранения bool
	* 
	* operator [] возвращает по значению
	* 
	* std::vector<bool>::reference 
	* внутренний тип для доступа к отдельным битам
	* 
	* std::vector<bool>::reference::operator bool
	* конвертирует бит внутреннего представления в bool
	* 
	* Одновременный доступ нескольких потоков
	* к разным элементам не безопасен
	*/

}

void Topic8() { // iterator

	/*
	* Каждый контейнер имеет типа итератора
	* -vector<int>::iterator
	* 
	* Итератор ~ указатель на текущий элемент контейнера + операции итерации по коллекции
	* -operator * достает значение
	* инкремент/декремент (переход на след. элемент)
	* копирование
	* х = *it
	*/
	std::vector<int> vec;
	std::vector<int>::iterator it;
	for (it = vec.begin();it < vec.end(); it++) {
		cout << *it << endl;
	}
	// vec.end() - элемент за последним(не разыменовывать)
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
		elt = true;// compilation error!
	for (auto && elt:v) // может быть rvalue и lvalue
		elt = true;

}

void Topic10() { // std::list<T>

	// Обобщенный двусвязный список

	// Элементы расположены нелинейно в памяти

	// Не поддерживает random access

	// Эффективнее vector при вставке и удалении

	// Итерируется в обе стороны

	// Встроенная сортировка (производит копирование указателей, а не значений)

	auto PrintOut = [](int p) {cout << " printout: " << p << endl; };

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
	* Ассоциативный контейнер (красно-черное дерево)
	* 
	* Особенности
	* -Уникальные ключи(для дублирующихся есть multimap)
	* -Эффективный поиск (О(log n)), и вставка (О(log n))
	* -Доступ через operator []
	* -Элементы хранятся парами <key, value>
	* -Тип ключа должен иметь operator <
	*/
	auto PrintOut = [](const std::pair<string, int>& p) {
		cout << "printout: [" << p.first << ", " << p.second << "]" << endl;
	};

	std::map<string, int> table;
	std::map<string, int>::iterator it;
	table.insert(std::pair<string, int>("a", 5));
	table.insert({ "c",35 });
	table["e"] = 454;
	cout << "table[e]:" << table["e"] << endl;
	it = table.find("c");
	cout << "PrintOut(*it), where it = table.find(c)" << endl;
	PrintOut(*it);
	cout << "iterating:" << endl;
	for_each(table.begin(), table.end(), &PrintOut);

}

void Topic12() { // reverse & const iterators

	auto PrintOut = [](const std::pair<string, int>& p) {
		cout << "printout: [" << p.first << ", " << p.second << "]" << endl;
	};

	std::map<string, int> table;
	std::map<string, int>::iterator it;
	table.insert(std::pair<string, int>("a", 5));
	table.insert({ "c",35 });
	table["e"] = 454;
	cout << "table[e]:" << table["e"] << endl;
	it = table.find("c");
	cout << "PrintOut(*it), where it = table.find(c)" << endl;
	PrintOut(*it);
	cout << "iterating:" << endl;
	for_each(table.begin(), table.end(), &PrintOut);
	for_each(table.rbegin(), table.rend(), &PrintOut);//reverse
	for_each(table.cbegin(), table.cend(), &PrintOut);//const


}

void Topic13() { // algorithms

	/*
	* Множество функций над коллекцией элементов
	* -Коллекция = итерируемая последовательность (массивы, контейнеры)
	* 
	* Алгоритмы оперируют над элементами, а не над управляющими контейнерами
	* -Могут требовать наличие операций: copy ctor, =, ==, !=, <
	* 
	* Некоторые не изменяют значения элементов
	* -find, count, for_each, min_element, binary_search
	* 
	* А некоторые изменяют
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

void Topic14() { // Шаблон проектирования: Адаптер

	/*
	* Позволяет повторно использовать реализованную 
	* функциональность при несовместимых интерфейсах
	* 
	* Технически - переадресация вызова от одного интерфейса к другому
	* 
	* Пример:
	* -Имеется реализованный в библиотеке класс для генерации случайных,
	* равномерно распределенных чисел в интервале [0, 1]
	* -Необходимо написать класс для генерации чисел в интервале [0, 100]
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