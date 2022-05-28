#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;

// 3rd lection

/* Содержание лекции:
*
* 1. string
* 2. streams
* 3. i/o fstream
* 4. stringstream
* 5. Правила перегрузки функций
* 6. Статический полиморфизм
* 7. Вывод типа шаблона
* 8. Первичные шаблоны и специализации
* 9. Разрешение перегрузки шаблонных функций
* 10. Шаблоны классов
* 11. Частичная специализация классов
* 12. auto
* 13. Braced-init-list & initializer_list
* 14. Braced initialization
* 15. Template algorithm + Strategy
* 16. Strategy + Template Algorithm 
* 17. Принцип Единственной Обязанности
* 
*/

void Topic1() { // string
	// string - класс строки, де-факто - контейнер char

	string str1 = "Hello";
	string str2 = "World";
	string str3 = str1 + str2;
	std::cout << str1.at(2) << std::endl;
	cout << "str1 + str2 : " << str3 << endl;
	cout << "str3.size() :  " << str3.size() << endl;

	str1[2] == str1.at(2) == true; // at не позволяет выйти за пределы памяти
}

void Topic2() { // streams

	// operator >> для чтения
	// operator << для записи
	// существуют для базовых типов

	// flush необходим для контроля содержимого потока вывода
	// std::endl включает в себя перевод строки + flush


	// с flush 
	cout << "Line 1..." << std::flush;
	std::usleep(1000000);
	cout << "\nLine 2" << endl;
	cout << "Line 3" << endl;

	/*
	* output:
	* Line 1…
	* <пауза 1с>
	* Line 2
	* Line 3
	*/


	// без flush 
	cout << "Line 1...";
	std::usleep(1000000);
	cout << "\nLine 2" << endl;
	cout << "Line 3" << endl;

	/*
	* output:
	* <пауза 1с>
	* Line 1…
	* Line 2
	* Line 3
	*/

}

void Topic3() { // i/o fstream

	//Чтение файлов с помощью stream

	/*
	* Последовательность
	* Открыть- считать - закрыть
	*/

	fin.open("infile.txt");
	fout.open("outfile.txt");
	int num1, num2, num3;
	fin >> num1 >> num2 >> num3;
	fout << "The sum is " << num1 + num2 + num3 << endl;
	fin.close();
	fout.close();


	while (stream >> buffer) {
		// { . . . }
	}
}

void Topic4() { // stringstream

	// позволяет создать поток и взять его содержимое, как строчку

	int countWords(string const& str) {
		// breaking input into word using string stream
		std::stringstream s(str); // Used for breaking words
		string word; // to store individual words

		int count = 0;
		while (s >> word)
			count++;
		return count;
	}


	std::stringstream ss;
	int num = 12345;
	ss << num;
	
	string strNum;
	ss >> strNum;
	ss.str("dostup k zapisi v sstr");
	ss.clear() == ss.str("") == true; // reset содержимого
	

	string s = "geeks for geeks geeks "
		"contribution placements";
	cout << " Number of words are: " << countWords(s);


}

void Topic5() { // Правила перегрузки функций

	/*
	* Точное соответствие типов
	* Продвижение, "повышение в чине"
	* Bool->int, short->int, char->int, float->double (базовая конвертация)
	* Продвижение путем стандартного преобразования (double->float, double->int)
	* Путем пользовательских преобразований
	*/

	void func(char*);
	void func(std::string const&);
	void func(int);

	/*
	* Подходящая реализация функции ищется путем нахождения
	* минимального числа конверсий к требуемым параметрам
	*/

}

void Topic6() { // Статический полиморфизм

	/*
	* Постановка задачи:
	* Имеется код, который работает одинаково и выглядит одинаково
	* для разных типов данных
	* 
	* В С++ существует механизм, позволяющий объявить шаблон кода,
	* который будет инстанциироваться в завивисмости от переданных параметров
	* т.е. сделать код параметризованным
	* 
	* Template - дает возможность написать функцию, исполняющую одни и те же
	* действия для различных типов данных
	*/

	template <typename T>
	T sqr(T x)
	{
		return x * x;
	}

	/*
	* При вызове sqr компиллятор сделает 2 вещи:
	* 1. Определение поведения кода в процессе компиляции
	* 2. Простейший вариант = Определение типа данных в процессе компиляции
	*/
	std::cout << sqr(1.0); // double sqr(double)
	std::cout << sqr(1); // int sqr(int)
	std::cout << sqr(1.0f); // float sqr(float)

	sqr<double>(1); // double sqr(double)
	sqr<int>(1.0); // int sqr(int)
	sqr<float>(1.0f); // float sqr(float)
}

void Topic7() { // Вывод типа шаблона

	template<typename T>
	void f(ParamType param);

	f(expr);

	/*
	* Вывод производится для T и ParamType
	*/

	//Пример
	template<typename T>
	void f(T & param);

	int x = 27; // x is an int
	const int cx = x; // cx is a const int
	const int& rx = x; // rx is a reference to x as a const int

	f(x); // T is int, param's type is int&
	f(cx);// T is const int, param's type is const int&
	f(rx);// T is const int, param's type is const int&


}

void Topic8() { // Первичные шаблоны и специализации

	/*
	* -Функции могут специализированны только полностью
	* -Специализации являются независимыми функциями
	*/

	template <class T>
	void f(T ); // (a) шаблонная функция - первичный шаблон

	template <class T>
	void f(T*); // (b) перегружает (a), первичный шаблон

	template <>
	void f<int>(int *); // (c), спецификация (b)

	int * p;
	f(p); // (c)

}

void Topic9() { // Разрешение перегрузки шаблонных функций

	/*
	* -Привилегированные – функции, которые не являются шаблонами. 
	* При разрешении перегрузки обычная нешаблонная функция 
	* имеет приоритет при условии совпадения типов аргументов (сигнатуры)
	* 
    * -Если такой функции нет, то рассматриваются первичные шаблоны функций.
	* Выбирается наиболее подходящий первичный шаблон функции.
	* 
    * Если у выбранного первичного шаблона есть специализации,
	* то в дальнейшем рассматриваются они.
	*/

	// Специализации шаблонов функций не участвуют в разрешении перегрузки!

	template <class T>
	void f(T);          //(a), primary

	template <>
	void f<int*>(int*); //(b) spec of (a)

	template <class T>
	void f(T*);         //(c), primary, overload
	// …
	int * p;
	f(p);// the answer is (c)


}

void Topic10() { // Шаблоны классов


	//Шаблоны классов - некое объявление семейства классов
	 
	/*
	* Общие операции для некоторого множества внутренних типов
	* 
	* Общие операции для некоторого множества производных классов
	* -Наследование специализации предка. Шаблон базового класса
	* -Шаблон производного класса. Использовании специализации методов
	* для фиксированного множества типов данных
	*/

	template <class blob_footprint_policy>
	class vl_projector
	{
	private:
		blob_footprint_policy m_blob_fp;
	};



	//Пример

	template < typename base_t >
	struct base2D_t
	{
	public://fields    
		//! X-dimension
		union
		{
			base_t x;
			base_t u;
			base_t width;
			base_t min;
			base_t column;
		};
		//! Y-dimension
		union
		{
			base_t y;
			base_t v;
			base_t height;
			base_t max;
			base_t row;
		};
	public://methods
		base2D_t& operator = (const base2D_t& v)
		{
			if (&v == this)
				return *this;
			x = v.x;
			y = v.y;
			return *this;
		}
		base2D_t& operator += (const base2D_t& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}
		base2D_t operator + (const base2D_t& v)
		{
			base2D_t res;
			res.x = x + v.x;
			res.y = y + v.y;
			return res;
		}
	};



}

void Topic11() { // Частичная специализация классов

	template<class T1, class T2, int I>// Если передаем базовый тип,
	                                   // то такой тип должен быть
	                                   // инстанциирован prvalue
	                                   // (значение, известное на compile time)
	                                   // так как template создается на этапе компилляции
	class A {};//первичный шаблон

	template<class T, int I>
	class A<T, T*, I> {}; // #1: частичная специализация, где T2 указатель на T1

	template<class T, class T2, int I>
	class A<T*, T2, I> {};// #2: частичная специализация, где T1 указатель

	template<class T>
	class A<int, T*, 5> {}; // #3: частичная специализация, где T1 это int, I это 5,
							//     и T2 это указатель
	template<class X, class T, int I>
	class A<X, T*, I> {};   // #4: частичная специализация, где T2 указатель


}

void Topic12() { // auto

	/*
	* auto - автоматически выводимый тип в С++11
	* -Объявление переменныхи параметров
	* -Правила выведения типа - такие же, как и для шаблонов
	* -Переменная должнаиметь начальное значение
	*/

	auto x  = 1;         //x : int
	float* p;
	auto x = p;          //x : float*
	auto* y = p;         //y : float*
	double f();
	auto x = f();        //x : double
	const auto& y = f(); //y : const double&
	class R;
	R* h();
	auto* x = h();       //x : R*
	auto y = h();        //y : R*
	int& g();
	auto x = g();        //x : int
	const auto& y = g(); //y : const int&
	auto* z = g();       //error, g() does not return a pointer type 


	/*
	* Рекомендации по auto:
	* -Отдавать предпочтение при определении типа 
	* -Производить итерации по контейнеру с помощью auto
	* -При длинных строчках с template'ами
	*/
}

void Topic13() { //Braced-init-list & initializer_list

	/*
	* std::initializer_list
	* -Шаблон списка параметров одного типа
	* -Конструктор с intitializer_list всегда приоритетнее остальных
	*/

	class A {
	public:
		A(int a, int b) { cout << "A()" << endl; }
		A(std::initializer_list<int> args) { cout << "A{ }" << endl; }
	};

	auto x = {1, 2}; // x - initializer_list
	A a1(x);     // A{ }
	A a2 {1, 2}; // A{ } (braced initialization)
	A a3 (1, 2); // A()
}

void Topic14() { // Braced initialization

	/*
	* -Инициализируется с помощью {}
	* -Нет неявного сужающего преобразования
	* -Нет Most vexing parse(Объявление переменной = объявление функции) (TimeKeeper time_keeper(Timer());)
	* -Детерминизм в отношении конструкторов
    */

	// create a vector of two elements initialized to [1, 1]
	std::vector<int> v(2, 1); 

	// create a vector containing two elements: [2, 1]
	std::vector<int> v{2, 1};
	// same
	std::vector<int> v = {2, 1};

	// initializer_list
	auto x = { 1 };

	// int!!!
	auto y { 2 };


}

void Topic15() { // Template algorithm + Strategy

	/*
	* 
	* Абстрагирование поведения высокого уровня от отдельных этапов алгоритма
	* 
	* Функция "алгоритма"
	* -Оперирует методами классов помощников
	* -Реализует логику верхнего уровня
	* 
	* Функции в рамках "алгоритма"
	* -Реализует логику отдельных этапов
	* -Могут быть реализованы как иерархии
	* -Либо как классы, специализирующие шаблон "алгоритма"
	* 
	*/

	template <class MemoryPolicy,
		class VoxelUpdatePolicy>
		class TargetFunc {
		public:
			ExecutionStatus
				runProcessing(VoxelGrid const& vgrid,
					MemoryPolicy const& memPolicy = MEMORY::heapMemPolicy) {
				VoxelUpdatePolicy voxUpdate(memPolicy);
				float* convResult = memPolicy.alloc(vgrid.getSliceSize() * sizeof(float));
				auto logger = Logger::getInstance();
				logger << "Update voxel values: " << Logger::KeepLine << vgrid.getSliceCount();
				for (auto i = 0; i < vgrid.getSliceCount(); ++i) {
					voxUpdate.calcSliceDenominator(convResult);
					voxUpdate.updateSlice();
				}
			}
	};


}

void Topic16() { // Strategy + Template Algorithm 

	//Strategy: Динамический полиморфизм
	class Compression
	{
	  public:
		virtual ~Compression() = default;
		virtual void compress(const string & file) = 0;
	};

	class ZIP_Compression : public Compression
	{
	public:
		void compress(const string& file) override final {
			cout << "ZIP compression" << endl;
		}
	};



	//Template Algorithm: Динамический полиморфизм
	class Compressor
	{
	public:
		Compressor(Compression* comp) : p(comp) {}
		~Compressor() { delete p; }
		void compress(string const& file) {
			p->compress(file);
		}
	private:
		Compression* p;
	};


	//Template Algorithm: Статический полиморфизм
	template <class CompressionPolicy>
		class CompressorTemplate {
		  public:
			void compress(string const  & file ) {
			  p.compress(file);
			}
		  private:
			CompressionPolicy p;
	};

	CompressorTemplate<RAR_Compression> CompAlg;
	CompAlg.compress("str");


}

void Topic17() { // Принцип Единственной Обязанности

	// Каждый класс должен реализовывать одну конкретную обязанность

	/*
	* АТД - абстрактный тип данных
	* -Замкнутое множество данных + методы
	* 
	* Single Responsibility Principle (SRP)
	* -Класс должен иметь лишь одну причину для изменения
	* 
	* Обязанность = ось изменения
	* -Атомарный набор: методы + данные = АТД
	* -Принцип SRP: каждый класс реализует 1 АТД
	*/

}