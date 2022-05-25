#include <iostream>
using std::cout;
using std::endl;
using std::string;

//2nd lection

/* Содержание лекции:
*
* 1. LValue & RValue
* 2. Move Semantics 
* 3. RValue reference
* 4. Форсирование Move Semantics
* 5. Категории значений
* 6. XValue
* 7. Move конструктор
* 8. Move Semantics и наследование
* 9. Copy Elision
* 10. Использование Move Semantics
* 11. Операторы классов по умолчанию
* 12. Запрет на использование
* 13. Static members
* 14. Singleton
* 15. Заключение
*
*/


void Topic1() { // LValue & RValue

	// Рассмотрим выражение присваивания
	// LValue = RValue

	/*
	* LValue:
	* -Объект, имеющий адрес(переменная с const и без const)
	* -Время жизни не ограничено временем исполнения выражения
	* 
	* RValue:
	* -Всё, что не LValue
	* -Не обязан переживать время исполнения выражения
	*/

	// lvalues:

	int i = 42;
	41 = i; // error, 41 is an rvalue
	i = 43; // ok, i is an lvalue
	int* p = &i; // ok, i is an lvalue
	int& foo();
	foo() = 42; // ok, foo() is an lvalue
	int* p1 = &foo(); // ok, foo() is an lvalue

	// rvalues:
	//
	int foobar();
	int j = 0;
	j = foobar(); // ok, foobar() is an rvalue
	int* p2 = &foobar(); // error, cannot take the address of an rvalue
	j = 42; // ok, 42 is an rvalue

}

void Topic2() { // Move Semantics 
	/*
	* Постановка задачи
	* Имеется некий Класс А
	* Он содержит ресурс - закрытый объект в динамической памяти
	* Создание ресурса - затратный процесс
	* Копирование объекта класса требует копирование ресурса
	* 
	* Требуется скопировать один объект в другой(оператор присваивания)
	* Разделенное владение ресурсом невозможно, должно происходить копирование
	* Проблема в том, что это не всегда необходимо
	* 
	* Например, если объект уничтожится после окончания оператора "равно"
	* Нет смысла его копировать
	*/

	/*
	* Присваивание
    * -Скопировать ресурс из временной копии 
    * -Вызвать деструктор ресурса временной копии
    * -Вызвать деструктор временной копии
	*
	* Присваивание в случае с RValue
	* -RValue не существует после выполнения выражения
	* -Ресурс может быть скопирован по ссылке
	* -Прежний ресурс объекта, куда происходит присваивание, может быть уничтожен
	*/


}
void Topic3() { // RValue reference
	/*
	* 
	* Есть оператор "равно"
	* Хотим определить его с новым типом
	* И этот оператор должен работать для RValue
	* (Он должен забрать все ресурсы и оставить копию)
	* 
	*/

	A& A::operator = (<mystery type> rhs)
	{
		// [...]
		// swap this->m_pRes and rhs.m_pRes
		// [...]  
	}

	/*
	* Оператор присваивания должен быть перегружен
	* -В случае LValue - вызывается стандартный вариант
	* -В случае RValue - вызывается вариант для <mystery type>
	* Где <mystery type> = ссыока на RValue
	* (Аргумент должен передаваться по ссылке)
	*/

	// Определение в compile-time реализации в зависимости
	// от типа аргумента - RValue или LValue

	void foo(X& x);  //LValue reference overload
	void foo(X&& x); //RValue reference overload

	A& A::operator = (A const& rhs); // обычная реализация для LValue
	A& A::operator = (A&& rhs) // реализация для RValue
	{
		// Move semantics: меняем ресурс между this и rhs
		return *this;
	}

	// Наличие реализаций | Вызов от LValue | Вызов от RValue |
	//      f(A &)        |        +        |        -        |
	//    f(A const &)    |        +        |        +        |
	//      f(A &&)       |        -        |        +        |
	// f(A&&) f(A const&) |        +        |        +        |
	//   f(A&&) f(A &)    |        +        |        +        |

	

}

void Topic4() { // Форсирование Move Semantics

	//Инструмент, который позволяет воспринимать LValue, как RValue
	//std::move

	void swap(T & a, T & b) // плохо - все операторы присваивания
		                    // работают через копирование
	{
		T tmp(a); 
		a = b;
		b = tmp;
	}

	T a, b;
	swap(a, b);

	void swap(T& a, T& b) // Теперь все операторы и конструкторы
		                  // работают с RValue (оператор с T&&)
		                  // При этом, если подходящего оператора нет
		                  // То std::move вызовет оператор присваивания (T const &)
	{
		T tmp(std::move(a));
		a = std::move(b);
		b = std::move(tmp);
	}

	T a, b;
	swap(a, b);

}

void Topic5() { // RValue reference == RValue ?

	void f(X && x)
	{
		X anotherX = x;
		// ...?
	}

	/*
	* Согласно стандарту:
	* -RValue reference может быть как LValue, так и RValue
	* -Критерий – если есть имя, значит lValue, иначе rValue
	* -x – имя переменной, значит anotherX будет создан с помощью X(X const &)
	* 
	* std::move(x):
	* -Превращает lValue в rValue
	* -std::move(x) – не имеет «имени»
	* 
	*/

	void f(X&& x)
	{
		X anotherX = x;
		// X(X const &)
	}

	X&& g();
	X x = g(); // X(X&&)

}

void Topic6() { // Категории значений
	// Задача:
	// Как инициировать val?
	// Что означает SomeType&&?
	SomeType && Func() { ... }
	SomeType && val  = Func();
	SomeType otherVal{ val };

	A   prvalue();
	A&  lvalue();
	A&& xvalue();

	//                               expression
	//                                /      \
	//           Generalized LValue  /        \
	//                              /          \
	//                         GLValue       RValue
	//                            / \          / \
	//                           /   \        /   \
	//                          /     \      /     \ Pure RValue
	//                      LValue     XValue      PrValue
	//                                eXpiring
	//                                  Value

	/*
	* LValue - есть имя, адрес, долго живут
	* PrValue - никогда нет имени, адреса и долго не живут
	* XValue - имеют адрес, не живут дольше выражения
	* GLValue - RValue, имеющие адрес и имя, самостоятельно живущие
	*/
}

void Topic7() { // XValue
	// XValue:
	// -Результат вызова функции, возвращающей RValue ссылку
	// -Преобразование LValue к RValue

	struct A {
		int m;
	};
	A&& operator+ (A, A);
	A&& f();

	A a;
	A&& ar  = static_cast<A&&>(a); // lValue
	f(); // xValue, т.к. объявили это как RValue reference
	a + a; // xValue
	f().m; // xValue. т.к. это поле экземпляра, являющегося XValue (есть адрес, как и у экземпляра и при этом ограничено время жизни)


}

void Topic8() { // Move конструктор

	class String
	{
	private:
		char* data;
	public:
	// default c-tor, etc
		~String() {
			delete[] data;
		}
		String(String const & lhs) {
			size_t size = std::strlen(lhs.data) + 1;
			data = new char[size];
			std::memcpy(data, lhs.data, size);
		}
		String(String && rhs) { // Меняем адрес местами
			data = rhs.data;
			rhs.data = nullptr;
		}
	};

}

void Topic9() { // Move Semantics и наследование

	Base(Base const& rhs); // non-move semantics
	Base(Base && rhs); // move semantics

	Derived(Derived const& rhs) : Base(rhs) // работает для LValue
	{
		// Derived-specific stuff
	}

	Derived(Derived&& rhs) // не работает для RValue
		: Base(rhs) // wrong: rhs is an lvalue
	{
		// Derived-specific stuff
	}

	Derived(Derived&& rhs) // для базового класса будет вызыван Base(Base && rhs), работает с RValue
		: Base(std::move(rhs))
	{
		// Derived-specific stuff
	}


}

void Topic10() { // Copy Elision

	/*
	* Copy Elision - оптимизация, позволяющая компилятору
	* пропускать конструкторы копирования/перемещения
	* в случае передачи в конструктор rvalue
	* 
	* Named Return Value Optimization
	* -Объект создается по месту вызова функции,
	* минуя конструктор копирования/перемещения если:
	* 1. Объект в return не volatile (разрешение другим потокам менять значение переменной)
	* 2. Не параметр функции
	* 3. Имеет тот же тип, что и возвращаемое значение ф-и
	* 
	* Return Value Optimization
	* -То же, что и NRVO, только для возвращаемых prvalue
	* (безымянных временных выражений)
	*/

	// Примеры

	class Thing {
	public:
		Thing();
		~Thing();
		Thing(Thing const&);
	};

	Thing f() {
		return Thing();
	}
	void foo(Thing t);
	//...
	Thing t1 = Thing(Thing(Thing())); //Thing() only - вызовет только один конструктор
	Thing t2 = f(); //Thing() only - вызовет только один конструктор
	foo(Thing()); //Thing() only


}

void Topic11() { // Использование Move Semantics

	/*
	* -В конструкторах/операторах перемещения
	* -В функциях, где 100% гарантия, что все ресурсы объекта могут быть перемещены(std::move)
	* -Не стоит использовать для "оптимизации"(может привести к отключению (N)RVO
	*/

	class X
	{
	public:
		X() { cout << "X::X()\n"; }
		X(const X&) { cout << "X::X(const X&)"; }
		X(X&&) { cout << "X::X(X&&)\n"; }
	};


	X good()
	{
		X x; //создается объект
		// perhaps do something to x
		return x;
	}

	X bad()
	{
		X x; //создается объект
		// perhaps do something to x
		return std::move(x); // кастуется к RValue и затем вызывается конструктор для RValue
	}

	Thing&& t2 = f();

}

void Topic12() { // Операторы классов по умолчанию
	/*
	* (Генерируются автоматически, если нет пользовательского аналога)
	*
	* A() - Конструктор по умолчанию – вызывает к-торы без параметров у предков и полей в порядке объявления.
	* A(const& A) - Копирующий конструктор
	* A& operator= (A const&) - Оператор копирования
	* ~A() - Деструктор, по умолчанию noexcept, виртуальный в случае, если в базовом классе деструктор виртуален
	* 
	* A(A&&) - конструктор перемещения
	* A& operator = (A&&) - операторперемещения
	* -Генерируются по умолчанию компилятором, если
	* 1. Нет оператора/конструктора копирования
	* 2. Нет деструктора
	* 3. Нет оператора или конструктора перемещения
	* 
	* Общее правило: используйте default
	* для определения доступных операций явно
	*/
}

void Topic13() { // Запрет на использование

	/*
	* =delete
	* 
	* -Запрещает вызов соответствующей операции
	* -Явно декларирует запрет
	* -Можно запретить любую операцию
	*/

	//  coding standard: disallow when not used
	T(void) = delete; // default ctor    (1)
	~T(void) = delete; // default dtor    (2)
	T(T const&) = delete; // copy ctor       (3)
	T(T&&) = delete; // move ctor       (4)
	T& operator= (T const&) = delete; // copy assignment (5)
	T& operator= (T&&) = delete; // move assignment (6)
}

void Topic14() { // Static members

	/*
	* Статические поля и методы класса не привязаны к экземплярам класса
	* -Нет неявного this в статических методах
	* 
	* Статические поля инициализируются в рамках некоего модуля трансляции
	* 
	* Static подчиняются модификаторам доступа
	* private/public/protected
	*/

	struct A {
		static void f(A* a); // ф-я не приниматель указатель this
	private:
		int b = 0;
		static int c; // объявление
	};

	void A::f(A * a) {
		cout << a->b; // стат. функция класса имеет доступ к
		cout << a->c; // полям и методам, даже если они private
	}
	int A::c = 10; // определение – НЕ обязательно в этом же срр

	int main() {
		A a;
		A::f(&a); // OK
		return 0;
	}

}

void Topic15() { // Singleton
	// Класс, существующий в одном экземпляре

	/*
	* Существует в единственном экземпляре
	* -Инстанциируется с помощью getInstance()
	* -Возвращает всегда один и тот же экземпляр
	* 
	* Примеры:
	* -Logger
	* -Thread pool
	* -Database connection
	* ...
	*/

	class Singleton{
private:
	Singleton(); // Операции которые создают копии вне класса,
	             // должны быть выключены
public:
	Singleton(Singleton const&) = delete;
	Singleton& operator = (Singleton const&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator = (Singleton&&) = delete;

	static Singleton& getInstance() {
		static Singleton test;
		return test;
	}
	};

}

void Topic16() { // Заключение
	/*
	* lValue – имеет имя/адрес, rValue - нет
	* 
	* RValue reference
	* -Перегрузка функций, конструкторов, операторов через
	* RValue reference может оптимизировать программу и избавить от ненужных копирований
	* -Может быть как LValue, так и RValue в зависимости от наличии имени
	* -Преобразование LValue в RValue осуществляется с помощью std::move
	* -При наследовании для вызова конструктора от Base&&
	* необходимо использовать std::move
	* 
	* Явно специфицируйте default & delete
	* 
	* Singleton
	* -Паттерн объекта, существующего в единственном экземпляре
	* -Базовая реализация основана на static
	* -static переменные удаляются после выполнения main
	*/
}

