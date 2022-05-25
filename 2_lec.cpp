#include <iostream>
using std::cout;
using std::endl;
using std::string;

//2nd lection

/* ���������� ������:
*
* 1. LValue & RValue
* 2. Move Semantics 
* 3. RValue reference
* 4. ������������ Move Semantics
* 5. ��������� ��������
* 6. XValue
* 7. Move �����������
* 8. Move Semantics � ������������
* 9. Copy Elision
* 10. ������������� Move Semantics
* 11. ��������� ������� �� ���������
* 12. ������ �� �������������
* 13. Static members
* 14. Singleton
* 15. ����������
*
*/


void Topic1() { // LValue & RValue

	// ���������� ��������� ������������
	// LValue = RValue

	/*
	* LValue:
	* -������, ������� �����(���������� � const � ��� const)
	* -����� ����� �� ���������� �������� ���������� ���������
	* 
	* RValue:
	* -��, ��� �� LValue
	* -�� ������ ���������� ����� ���������� ���������
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
	* ���������� ������
	* ������� ����� ����� �
	* �� �������� ������ - �������� ������ � ������������ ������
	* �������� ������� - ��������� �������
	* ����������� ������� ������ ������� ����������� �������
	* 
	* ��������� ����������� ���� ������ � ������(�������� ������������)
	* ����������� �������� �������� ����������, ������ ����������� �����������
	* �������� � ���, ��� ��� �� ������ ����������
	* 
	* ��������, ���� ������ ����������� ����� ��������� ��������� "�����"
	* ��� ������ ��� ����������
	*/

	/*
	* ������������
    * -����������� ������ �� ��������� ����� 
    * -������� ���������� ������� ��������� �����
    * -������� ���������� ��������� �����
	*
	* ������������ � ������ � RValue
	* -RValue �� ���������� ����� ���������� ���������
	* -������ ����� ���� ���������� �� ������
	* -������� ������ �������, ���� ���������� ������������, ����� ���� ���������
	*/


}
void Topic3() { // RValue reference
	/*
	* 
	* ���� �������� "�����"
	* ����� ���������� ��� � ����� �����
	* � ���� �������� ������ �������� ��� RValue
	* (�� ������ ������� ��� ������� � �������� �����)
	* 
	*/

	A& A::operator = (<mystery type> rhs)
	{
		// [...]
		// swap this->m_pRes and rhs.m_pRes
		// [...]  
	}

	/*
	* �������� ������������ ������ ���� ����������
	* -� ������ LValue - ���������� ����������� �������
	* -� ������ RValue - ���������� ������� ��� <mystery type>
	* ��� <mystery type> = ������ �� RValue
	* (�������� ������ ������������ �� ������)
	*/

	// ����������� � compile-time ���������� � �����������
	// �� ���� ��������� - RValue ��� LValue

	void foo(X& x);  //LValue reference overload
	void foo(X&& x); //RValue reference overload

	A& A::operator = (A const& rhs); // ������� ���������� ��� LValue
	A& A::operator = (A&& rhs) // ���������� ��� RValue
	{
		// Move semantics: ������ ������ ����� this � rhs
		return *this;
	}

	// ������� ���������� | ����� �� LValue | ����� �� RValue |
	//      f(A &)        |        +        |        -        |
	//    f(A const &)    |        +        |        +        |
	//      f(A &&)       |        -        |        +        |
	// f(A&&) f(A const&) |        +        |        +        |
	//   f(A&&) f(A &)    |        +        |        +        |

	

}

void Topic4() { // ������������ Move Semantics

	//����������, ������� ��������� ������������ LValue, ��� RValue
	//std::move

	void swap(T & a, T & b) // ����� - ��� ��������� ������������
		                    // �������� ����� �����������
	{
		T tmp(a); 
		a = b;
		b = tmp;
	}

	T a, b;
	swap(a, b);

	void swap(T& a, T& b) // ������ ��� ��������� � ������������
		                  // �������� � RValue (�������� � T&&)
		                  // ��� ����, ���� ����������� ��������� ���
		                  // �� std::move ������� �������� ������������ (T const &)
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
	* �������� ���������:
	* -RValue reference ����� ���� ��� LValue, ��� � RValue
	* -�������� � ���� ���� ���, ������ lValue, ����� rValue
	* -x � ��� ����������, ������ anotherX ����� ������ � ������� X(X const &)
	* 
	* std::move(x):
	* -���������� lValue � rValue
	* -std::move(x) � �� ����� ������
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

void Topic6() { // ��������� ��������
	// ������:
	// ��� ������������ val?
	// ��� �������� SomeType&&?
	SomeType�&& Func() { ... }
	SomeType�&& val� = Func();
	SomeType�otherVal{ val };

	A���prvalue();
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
	* LValue - ���� ���, �����, ����� �����
	* PrValue - ������� ��� �����, ������ � ����� �� �����
	* XValue - ����� �����, �� ����� ������ ���������
	* GLValue - RValue, ������� ����� � ���, �������������� �������
	*/
}

void Topic7() { // XValue
	// XValue:
	// -��������� ������ �������, ������������ RValue ������
	// -�������������� LValue � RValue

	struct A {
		int m;
	};
	A&& operator+ (A, A);
	A&& f();

	A a;
	A&& ar  = static_cast<A&&>(a); // lValue
	f(); // xValue, �.�. �������� ��� ��� RValue reference
	a + a; // xValue
	f().m; // xValue. �.�. ��� ���� ����������, ����������� XValue (���� �����, ��� � � ���������� � ��� ���� ���������� ����� �����)


}

void Topic8() { // Move �����������

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
		String(String && rhs) { // ������ ����� �������
			data = rhs.data;
			rhs.data = nullptr;
		}
	};

}

void Topic9() { // Move Semantics � ������������

	Base(Base const& rhs); // non-move semantics
	Base(Base && rhs); // move semantics

	Derived(Derived const& rhs) : Base(rhs) // �������� ��� LValue
	{
		// Derived-specific stuff
	}

	Derived(Derived&& rhs) // �� �������� ��� RValue
		: Base(rhs) // wrong: rhs is an lvalue
	{
		// Derived-specific stuff
	}

	Derived(Derived&& rhs) // ��� �������� ������ ����� ������� Base(Base && rhs), �������� � RValue
		: Base(std::move(rhs))
	{
		// Derived-specific stuff
	}


}

void Topic10() { // Copy Elision

	/*
	* Copy Elision - �����������, ����������� �����������
	* ���������� ������������ �����������/�����������
	* � ������ �������� � ����������� rvalue
	* 
	* Named Return Value Optimization
	* -������ ��������� �� ����� ������ �������,
	* ����� ����������� �����������/����������� ����:
	* 1. ������ � return �� volatile (���������� ������ ������� ������ �������� ����������)
	* 2. �� �������� �������
	* 3. ����� ��� �� ���, ��� � ������������ �������� �-�
	* 
	* Return Value Optimization
	* -�� ��, ��� � NRVO, ������ ��� ������������ prvalue
	* (���������� ��������� ���������)
	*/

	// �������

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
	Thing t1 = Thing(Thing(Thing())); //Thing() only - ������� ������ ���� �����������
	Thing t2 = f(); //Thing() only - ������� ������ ���� �����������
	foo(Thing()); //Thing() only


}

void Topic11() { // ������������� Move Semantics

	/*
	* -� �������������/���������� �����������
	* -� ��������, ��� 100% ��������, ��� ��� ������� ������� ����� ���� ����������(std::move)
	* -�� ����� ������������ ��� "�����������"(����� �������� � ���������� (N)RVO
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
		X x; //��������� ������
		// perhaps do something to x
		return x;
	}

	X bad()
	{
		X x; //��������� ������
		// perhaps do something to x
		return std::move(x); // ��������� � RValue � ����� ���������� ����������� ��� RValue
	}

	Thing&& t2 = f();

}

void Topic12() { // ��������� ������� �� ���������
	/*
	* (������������ �������������, ���� ��� ����������������� �������)
	*
	* A() - ����������� �� ��������� � �������� �-���� ��� ���������� � ������� � ����� � ������� ����������.
	* A(const& A) - ���������� �����������
	* A& operator= (A const&) - �������� �����������
	* ~A() - ����������, �� ��������� noexcept, ����������� � ������, ���� � ������� ������ ���������� ���������
	* 
	* A(A&&) - ����������� �����������
	* A& operator = (A&&) - �������������������
	* -������������ �� ��������� ������������, ����
	* 1. ��� ���������/������������ �����������
	* 2. ��� �����������
	* 3. ��� ��������� ��� ������������ �����������
	* 
	* ����� �������: ����������� default
	* ��� ����������� ��������� �������� ����
	*/
}

void Topic13() { // ������ �� �������������

	/*
	* =delete
	* 
	* -��������� ����� ��������������� ��������
	* -���� ����������� ������
	* -����� ��������� ����� ��������
	*/

	//��coding�standard:�disallow�when�not�used
	T(void) = delete;�//�default�ctor����(1)
	~T(void) = delete;�//�default�dtor����(2)
	T(T const&) = delete;�//�copy�ctor�������(3)
	T(T&&) = delete;�//�move�ctor�������(4)
	T& operator=�(T const&) = delete;�//�copy�assignment�(5)
	T& operator=�(T&&) = delete;�//�move�assignment�(6)
}

void Topic14() { // Static members

	/*
	* ����������� ���� � ������ ������ �� ��������� � ����������� ������
	* -��� �������� this � ����������� �������
	* 
	* ����������� ���� ���������������� � ������ ������� ������ ����������
	* 
	* Static ����������� ������������� �������
	* private/public/protected
	*/

	struct A {
		static void f(A* a); // �-� �� ����������� ��������� this
	private:
		int b = 0;
		static int c; // ����������
	};

	void A::f(A * a) {
		cout << a->b; //�����. ������� ������ ����� ������ �
		cout << a->c; //������ � �������, ���� ���� ��� private
	}
	int A::c = 10; //������������ � �� ����������� � ���� �� ���

	int main() {
		A a;
		A::f(&a); //�OK
		return 0;
	}

}

void Topic15() { // Singleton
	// �����, ������������ � ����� ����������

	/*
	* ���������� � ������������ ����������
	* -��������������� � ������� getInstance()
	* -���������� ������ ���� � ��� �� ���������
	* 
	* �������:
	* -Logger
	* -Thread pool
	* -Database connection
	* ...
	*/

	class Singleton{
private:
	Singleton(); //��������� ������� ������� ����� ��� ������,
	             // ������ ���� ���������
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

void Topic16() { // ����������
	/*
	* lValue � ����� ���/�����, rValue - ���
	* 
	* RValue reference
	* -���������� �������, �������������, ���������� �����
	* RValue reference ����� �������������� ��������� � �������� �� �������� �����������
	* -����� ���� ��� LValue, ��� � RValue � ����������� �� ������� �����
	* -�������������� LValue � RValue �������������� � ������� std::move
	* -��� ������������ ��� ������ ������������ �� Base&&
	* ���������� ������������ std::move
	* 
	* ���� �������������� default & delete
	* 
	* Singleton
	* -������� �������, ������������� � ������������ ����������
	* -������� ���������� �������� �� static
	* -static ���������� ��������� ����� ���������� main
	*/
}

