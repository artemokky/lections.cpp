#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <list>
#include <map>
#include <functional>

using std::cout;
using std::endl;
using std::string;

// 5th lection

/* Содержание лекции:
*
* 1. Синоним типа: Using vs Typedef
* 2. Синонимы указателей на методы
* 3. Обобщенный синоним типа: Using vs Typedef
* 4. Исключения
* 5. Объекты-исключения
* 6. Обработка исключений
* 7. Исключения в конструкторах и деструкторах
* 8. Классы исключений в STL
* 9. Exception: what?
* 10. Exception safety
* 11. Работа с указателями в С++
* 12. Недостатки указателей
* 13. Умные указатели
* 14. Семантика исключительного владения
* 15. Virtual Constructor
* 16. Custom deleter
* 17. std::make_unique
* 18. std::shared_ptr
* 19. Constness: unique_ptr & shared_ptr
* 20. Передача указателей: raw pointer
* 21. Передача указателей: передача владения
* 22. Move + const ref
* 23. Передача указателей: разделение владения
* 24. Циклические ссылки
* 25. weak_ptr
* 26. Сильные и слабые ссылки
* 27. Захват shared_ptr в lambda
* 28. Умные указатели: заключение
*
*/

void Topic1() { // Синоним типа: Using vs Typedef


	// typedef создает синоним, не новый тип
	typedef std::vector<std::pair<std::string, int>> Pairlist_t;

	Pairlist_t pairlist;

	bool hasAttribute(Pairlist_t pairlist)
	{
		// do smth
	}

	// с С++11 - аналог typedef'у - using
	using Pairlist = std::vector<std::pair<std::string, int>>;


		//  create  an  alias  of  reference  to  int[4] 
		using IntArray4 = int(&)[4];
	//  or  with  typedef
	//  typedef  int(&IntArray4)[4] 
	 //  Use  the  array  reference  alias  as  parameter  type
	void foo(IntArray4 array) {
		//  range-based  loop  on  the  array
		for (int i : array)
			std::cout << i << "  ";
	}

	//  foo  can  be  called  on  a  int[4]  as:
	int arr[4] = { 6, 7, 8, 9 };
	foo(arr);//  logs    6  7  8  9


}

void Topic2() { // Синонимы указателей на методы


	// в отношении указателя на функции не все так просто:
	typedef void(*FP)(int);  // объявление типа указателя на функции с сигнатурами void от int 
	// vs
	using FP = void(*)(int); // FP может быть использован как указатель на функцию
	void foo(FP callback);


	class A {
	public:
		int f(int x, int y) { return x + y }
	};

	typedef int (A::* FuncTypeTypedef)(int, int);
	using FuncTypeUsing = int (A::*)(int, int);
	
	A a;
	FuncTypeUsing f1 = &A::f;
	FuncTypeTypedef f2 = &A::f;
	std::cout << (a.*f1) (5, 8) << std::endl;
	std::cout << (a.*f2) (6, 2) << std::endl;



}

void Topic3() {// Обобщенный синоним типа: Using vs Typedef
//a template or generic alias
	template<typename A>
	using UserAccounts_t = std::map<UserId, std::vector<A>>;
	using UserCheckingAccounts_t = UserAccounts_t<CheckingAccount>;
	using UserSavingsAccounts_t = UserAccounts_t<SavingsAccount>;
	//vs
	template<typename A>
	struct UserAccounts_t {
		typedef std::map<UserId, std::vector<A>> type
	};
	// and use it like:
	UserAccounts_t<CheckingAccounts>::type UserCheckingAccounts;
}

void Topic4() { // Исключения

	/*
	* Механизм исключений
	* -Регламентирует редко случающиеся ситуации,
	* влекущие радикальные изменения в текущем
	* поведении программы, либо прекращение её работы
	* 
	* Код, генерирующий исключения
	* -Помещается в блок try {}
	* -Исключения создаются вызовом throw [exception object] 
	* 
	* Код, обрабатывающий исключения
	* -Помещается в блок catch {}
	*/

}

void Topic5() { // Объекты-исключения

	/*
	* Семантика
	* -Данные об ошибке
	* 
	* std::exception
	* -Базовый класс исключения в стандартной библиотеке
	* -Все исключения стандартной библиоткеи наследованы от std::exception
	* 
	* Объекты-исключения
	* -В качестве объекта-исключения может выступать любой класс
	* -Классы исключений могут быть организованы в иерархию
	*/

	try
	{
		m_task_desc->memory.h_pinned_memmgr.reset(new mem_ops::memory_manager_pinned);
	}
	catch (const std::exception& e)
	{
		LOG_STREAM << "[ERROR] Pinned memory exception occured: ";
		LOG_STREAM << e.what();
		LOG_STREAM << "Pinned memory manager will be reset to NULL. \n";
		m_task_desc->memory.h_pinned_memmgr.reset();
	}

}

void Topic6() { // Обработка исключений

	/*
	* catch блоки обрабатываются в порядке объявления
	* 
	* catch (...) {}
	* -Ловит любое исключение
	* -Должен быть объявлен последним
	* 
	* catch (BaseClass &b)
	* -Должен быть объявлен после всех наследников
	*/

	/*
	* Обработка исключения = развертка стека вызовов
	* 
	* При возникновении исключения поиск обработчика 
	* заканчивается во внешнем блоке try ... catch,
	* в который "обернут" main (winmain)
	* -Попадание в этот блок ведет к вызову функции terminate()
	* 
	* Возникновение исключения во время развертки стека = вызов terminate()
	* 
	* Стандартное правило
	* -Throw by value, catch by reference
	*/

}

void Topic7() { // Исключения в конструкторах и деструкторах

	/*
	* Исключение в конструкторе
	* -Объект не является созданным, и тело деструктора не будет вызвано (зомби-объекты - существует, но не работает)
	* -Деструкторы предков и полей вызываются в стандартном порядке
	* 
	* Исключение в деструкторе
	* -При возникновении на этапе развертки стека вызовов приведет к вызову terminate()
	* 
	* Следует избегать ОБА ВАРИАНТА использования в исключениях
	*/

}

void Topic8() { // Классы исключений в STL

	/*
	* std::exception
	* -Базовый класс исключения
	* -Наследуем более специфичные исключения от базового класса
	* -Ставим базовый класс в самый конец блоков catch
	* 
	* std::runtime_error
	* -Содержит сообщение об ошибке
	* -Имеет конструктор от const char* (можно просто записывать сообщения)
	* -Может служить базовым классом для более специфичных
	*/

}

void Topic9() { // Exception: what?

	struct ooops : std::exception {
		const char* what() const noexcept { return "Ooops!\n"; }
	};

	
	try {
		throw ooops();
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}

	/*
	* output:
	* Ooops!
	* 
	*/

}

void Topic10() { // Exception safety
	
	/*
	* noexcept
	* -Функция гарантирует, что никогдане бросает
	* исключений - ключевое слово "noexcept"
	* -Пример: деструктор, move конструктор
	* 
	* Strong exception guarantee
	* -В случае исключения функция возвращает программу в состояние до вызова
	* Пример: vector::push_back
	* 
	* Basic exception guarantee
	* -При исключении нет утечек ресурсов, инварианты классов не нарушены
	* 
	* No exception guarantee
	* -Может произойти всё, что угодно
	*/

}

void Topic11() { // Работа с указателями в С++

	/*
	* Синтаксис
	* typename *variable 
	* 
	* Выделение памяти
	* -variable = new typename 
	* -variable = new typename[10] 
	* -variable = new (allocatedPtr) typename 
	* 
	* Удаление
	* -delete variable 
	* -delete [] variable 
	*/

	//Placement new

	// within any block scope...
	{
		alignas(T) unsigned char buf[sizeof(T)];
		// Выравнивание памяти на размер типа Т
		T* tptr = new(buf) T;  // Создаем объект класса Т 
		// Вызываем конструктор на начало выделенной уже памяти
		tptr->~T();  // Нужно вызывать деструктор вручную
	}   // Выходя за границы, буфер удалится.


}

void Topic12() { // Недостатки указателей

	/*
	* Объект это или массив?
	* 
	* Владеет ли указатель тем, на что указывает?
	* -Надо ли удалить объект по завершении работы?
	* 
	* Как именно удалить объект, если необходимо?
	* -delete, delete []
	* -Пользовательская ф-я удаления?
	* 
	* Как обеспечить удаление ровноодин раз на каждом пути исполнения кода?
	* -Утечка vs неопределенное поведение
	* 
	* Как определить, что указатель висячий?
	* -Объект удален, а указатель остался
	*/

}

void Topic13() { // Умные указатели

	/*
	* std::auto_ptr<T>
	* -Пережиток прошлого
	* -Выродился в unique_ptr
	* 
	* std::unique_ptr<T>
	* -Указатель с исключительным владением
	* 
	* std::shared_ptr<T>
	* -Указатель с разделяемым владением
	* 
	* std::weak_ptr<T>
	* -Указатель для доступа к shared_ptr без права владения
	*/

}

void Topic14() { // Семантика исключительного владения

	/* std::unique_ptr<T>
	* 
	* Перемещение разрешено
	* -Передача владения
	* 
	* Копирование запрещено
	* -Исключительное владение
	* 
	* В контексте внешнего кода ведет себя, как обычный указатель
	* 
	* Идеален в качестве возвращаемого значения из фабрики
	*/

	void g(std::unique_ptr<int>&ptr) { // Принимает по ссылке
		cout << *ptr << endl;
	}
	void f(std::unique_ptr<int> ptr) { // Принимает по значению
		cout << *ptr << endl;
	}

	std::unique_ptr<int> ptr{ new int(5) };

	if (ptr) { //check pointer == convert to bool
		g(ptr);
	}
	f(std::move(ptr)); // удален оператор копирования, поэтому передаем владение внутрь f

	g(ptr); // теперь неопределенное поведение после передачи владения в f



}

void Topic15() { // Virtual Constructor

	/*
	* Полиморфизм этапа инициализации
	* -Антипод RAII
	* 
	* Виртуальный конструктор не может существовать
	* -Вызов виртуальной функции подразумевает необходимость частичного знания о типа
	* но, при создании нового объекта, нужно знать всю информацию о типе
	* -Конструктору нужен полный тип
	* 
	* Но может существовать метод create()/clone()
	*/

	struct animal {
		virtual ~animal() = default;
		virtual std::unique_ptr<animal> create() = 0;
		virtual std::unique_ptr<animal> clone() = 0;
	};
	struct dog : animal {
		std::unique_ptr<animal> create() { return std::make_unique<dog>(); }
		std::unique_ptr<animal> clone() { return std::make_unique<dog>(*this); }
	};
	void who_am_i(animal * who) {
		auto new_who = who->create(); // `create` the object of same type i.e. pointed by who ?
		auto duplicate_who = who->clone();  // `copy` object of same type i.e. pointed by who ?    
		delete who; // you can delete object pointed by who
	}


}

void Topic16() { // Custom deleter

	/*
	* Указатель на функцию специального способа удаления объекта
	* -std::function
	* Function pointer
	* Stateless functor
	* State - full functor
	* Lambda
	*/

	template<typename T>
	using deleted_unique_ptr = std::unique_ptr<T, std::function<void(T*)>>;

	deleted_unique_ptr<FILE> file(
		fopen("file.txt", "r"), // создаем тип FILE
		[](FILE* f) { // Определяем к нему функцию void(T*) (деструктор)
			fclose(f);
		});



}

void Topic17() { // std::make_unique

	/*
	* make_unique<T>(args...)
	* 
	* Ключевая идея - использовать new для создания и delete для удаления
	* 
	* Basic exception guarantee
	* 
	* void foo(unique_ptr<X>(new X), unique_ptr<Y>(new Y))
	* -Порядок вычисления параметров = создания объектов не указан
	* -В случае exception в ходе создания второго по порядку параметра - memory leak
	* 
	* Не работает с custom deleters
	*/
	class Vec3;

	std::unique_ptr<Vec3> v1 = std::make_unique<Vec3>();
	std::unique_ptr<Vec3> v2 = std::make_unique<Vec3>(0, 1, 2);
	std::unique_ptr<Vec3[]> v3 = std::make_unique<Vec3[]>(5);

	std::cout << "make_unique<Vec3>():      " << *v1 << '\n'
		<< "make_unique<Vec3>(0,1,2): " << *v2 << '\n'
		<< "make_unique<Vec3[]>(5):   ";
	for (int i = 0; i < 5; i++) {
		std::cout << std::setw(i ? 30 : 0) << v3[i] << '\n';
	}


}

void Topic18() { // std::shared_ptr

	/*
	* Управление ресурсом с совместным владением
	* -Счетчик ссылок == 0 -> удалить ресурс
	* -При копировании shared_ptr счетчик инкрементируется
	* -При уничтожении shared_ptr счетчик декрементируется
	* 
	* Control block
	* -Счетчик сильных ссылок (ref counter)
	* -Счетчик слабых ссылок(weak counter)
	* -Deleter
	* 
	* Создание shared_ptr от готового указателя = аллокация доп. контрольного блока
	* 
	* std::make_shared
	* -Выделяет control block + ptr единым блоком в памяти
	*/

	auto loggingDeleter = [](int* p) {
		std::cout << "delete ptr " << p << std::endl;
		delete p;
	};
	int* p = new int{ 5 };
	// Тип удалителя НЕ является частью типа указателя
	std::shared_ptr<int> ptr1(p, loggingDeleter);
	std::shared_ptr<int> ptr2(p, loggingDeleter); // !!!

	// Совет: создавать shared_ptr вместе с созданием ресурса

	/*
	* output:
	* delete ptr 0x20eb400 
    * delete ptr 0x20eb400
	*/

}

void Topic19() { // Constness: unique_ptr & shared_ptr
	
	/*
	* Pointer                         Raw pointer          Description
	* 
	* shared_ptr<T> p                    T* p             Ни значение,
	*                                                    ни указатель не const
	* 
	* const shared_ptr<T> p            T* const p        Значение изменимо,
	*                                                    указатель - нет
	* 
	* shared_ptr<const T> p            T const* p        Значение константно,
	*                                                    указатель можно менять
	* 
	* const shared_ptr<const T> p    T const * const p   И значение, и указатель
	*                                                    константно
	*/
}

void Topic20() { // Передача указателей: raw pointer

	/*
	* Стоит передавать в случае:
	* 
	* Если указатель живет дольше, чем происходит вызов функции
	* 
	* Если функции не требуется передавать/разделять владение объектом
	*/

	/*
	* Тип использования        Изменяемые    Неизменяемые
	* 
	*     Nullable              Object*      Object const*
	* 
	* Обычный доступ/вызов      Object&      Object const&
	*/

}

void Topic21() { // Передача указателей: передача владения

	// Если указатель живет НЕ дольше, чем происходит вызов функции 

	/*
	*   Тип использования                   Пояснение
	* 
	*   unique_ptr<T> p                 Передача владения.
	*  unique_ptr<T>&& p                    
	* 
	* const unique_ptr<T> p         const(вероятнее всего) не
	*                                     вносит смысла
	* 
	*   unique_ptr<T>& p        Передача владения может произойти.
	*                             unique_ptr может быть изменен/
	*                           перемещен. Не работает для rvalue
	* 
	* unique_ptr<T> const& p       Не может передать владение.
	*                               Передаем просто доступ
 	* 
	*/

}

void Topic22() { // Move + const ref

	// std::move НЕ перемещает ничего сам по себе
	// Перемещение из const невозможно, т.к. объект теряет ресурс = меняется
	// move делает cast

	class Annotation {
	public:
		explicit Annotation(const std::string text) :value(std::move(text)) {}
		//мы хотим за-move-ить const string text, 
		//вызываем конструктор string(string&&) - а он не существует, 
		//поэтому не будет move, переменная будет просто скопирована,
		//так как teхt объявлен, как const,
		//это значит что std::move(text) вернет const std::string&&
		//поэтому будет вызван string(const string&)
		//это баг, решение которого очень сложно найти
	private:
		std::string value;
	};

	class A {
	public:
		A() { cout << "A" << endl; }
		A(A const&) { cout << "A->A" << endl; }
		A(A&&) { cout << "move A" << endl; }
	};

	class B {
		A _a;
	public:
		B(A const& a) : _a(std::move(a)) { cout << "move A to B" << endl; }
	}; // из за const - вызовется не A(A&&), а A(A const&)

	A a;
	B b1(a);

	/*
	* output:
	* A
	* A->A
	* move A to B
	*/


}

void Topic23() { // Передача указателей: разделение владения

	/*
	* Если указатель не обязательно живет дольше, чем происходит
	* вызов функции - разделение владения
	* 
	* Передача по & может дать возможность неявного копирования shared_ptr
	* -Эффективнее может быть raw pointer
	* 
	*   Тип использования                    Пояснение
	* 
	*    shared_ptr<T> p               Разделение владения
	* 
	* const shared_ptr<T> p          const может быть лишним,
	*                             разделение владения происходит
	* 
	*   shared_ptr<T>& p         Передача владения не происходит,
	*                            но ptr может быть изменен (reset?)
	*                              Доступ к объекту сохраняется
	* 
	* shared_ptr<T> const& p     Предоставление доступа (raw ptr?)
	*/

}

void Topic24() { // Циклические ссылки

	class A {};
	class B {};

	auto ap = std::make_shared<A>();
	auto bp = std::make_shared<B>();

	ap->bptr_ = bp;
	bp->aptr_ = ap;

	// Объекты должны удалиться, но на самом деле нет
	// Утечка памяти, так как счетчики на объекты хранятся друг у друга


	// Решение

	struct B;

	struct A {
		std::shared_ptr<B> bptr_;
	};

	struct B {
		std::weak_ptr<A> aptr_;
	};
}

void Topic25() { // weak_ptr

	/*
	* Разделение владения не всегда требуется для доступа
	* -Повсеместное использование shared_ptr для доступа
	* может приводить к перекрестным ссылкам = висячие указатели
	* 
	* weak_ptr - слабый указатель
	* -Создается из shared_ptr
	* -Не участвует в разделении владения
	* -Имеет возможность проверить, существует ли ещё объект
	* -Контрольный блок shared_ptr включает счетчик не только сильных,
	* но и "слабых" ссылок
	* 
	*/

	class SomeClass {
	public:
		void sayHello() { std::cout << "Hello!" << std::endl; }
		~SomeClass() { std::cout << "~SomeClass" << std::endl; }
	};

	/*std::weak_ptr<SomeClass> wptr;
	{ // local scope
		auto ptr = std::make_shared<SomeClass>();
		wptr = ptr;
		if (auto tptr = wptr.lock()) {
			tptr->sayHello();
		}
		else
		{
			std::cout << "lock() failed" << std::endl;
		}
	}
	if (auto tptr = wptr.lock())
	{
		tptr->sayHello();
	}
	else
	{
		std::cout << "lock() failed" << std::endl;
	}*/

}

void Topic26() { // Сильные и слабые ссылки

	/*
	* share_ptr хранит указатель на ресурс и контрольный блок
	* 
	* Если счетчик сильных ссылок стал 0
	* -Удаляем ресурс
	* 
	* Если счетчики слабых и сильных ссылок = 0
	* -Удаляем и контрольный блок
	*/

}

void Topic27() { // Захват shared_ptr в lambda

	/*
	* Lambda ~ класс
	* -Захват shared_ptr РАЗДЕЛЯЕТ владение
	* -Может приводить к утечкам памяти
	* -Вне зависимости от использования лямбды - разделение происходит
	*
	* Общаея рекомендация - никогда не захватывать shared_ptr в lambda
	* -Вместо этого - захватывать weak_ptr
	*/

	class A {
	public:
		using CallBack = std::function<void()>;
			void on_complete(CallBack cb) { complete_callback = cb; }
	private:
		CallBack complete_callback;
	};

	// ...
	std::shared_ptr<A> obj = std::make_shared<A>();

	obj->on_complete([obj]() {
		obj->clean_something_up();
		});
	executor->submit(obj);

}

void Topic28() { // Умные указатели: заключение

	/*
	* unique_ptr
	* -Исключительное владение
	* -Не привносит доп. расходов
	* -Кастоумный удалитель - часть специализации типа
	* 
	* shared_ptr - реализация "сборщика мусора"
	* -Занимает больше памяти, чем unique/raw
	* -Создание ресурса для shared_ptr должно быть включено в
	* создание shared_ptr
	* -Кастомный удалитель не является частью типа
	* 
	* weak_ptr
	* -Доступ к разделяемому ресурсу без разделения владения
	* -lock() - для получения оригинального shared_ptr = доступа к ресурсу
	* 
	*/

}
