#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;

// 3rd lection

/* ���������� ������:
*
* 1. string
* 2. streams
* 3. i/o fstream
* 4. stringstream
* 5. ������� ���������� �������
* 6. ����������� �����������
* 7. ����� ���� �������
* 8. ��������� ������� � �������������
* 9. ���������� ���������� ��������� �������
* 10. ������� �������
* 11. ��������� ������������� �������
* 12. auto
* 13. Braced-init-list & initializer_list
* 14. Braced initialization
* 15. Template algorithm + Strategy
* 16. Strategy + Template Algorithm 
* 17. ������� ������������ �����������
* 
*/

void Topic1() { // string
	// string - ����� ������, ��-����� - ��������� char

	string str1 = "Hello";
	string str2 = "World";
	string str3 = str1 + str2;
	std::cout << str1.at(2) << std::endl;
	cout << "str1�+�str2�:�" << str3 << endl;
	cout << "str3.size()�:��" << str3.size() << endl;

	str1[2] == str1.at(2) == true; // at �� ��������� ����� �� ������� ������
}

void Topic2() { // streams

	// operator >> ��� ������
	// operator << ��� ������
	// ���������� ��� ������� �����

	// flush ��������� ��� �������� ����������� ������ ������
	// std::endl �������� � ���� ������� ������ + flush


	// � flush 
	cout << "Line�1..." << std::flush;
	std::usleep(1000000);
	cout << "\nLine�2" << endl;
	cout << "Line�3" << endl;

	/*
	* output:
	* Line 1�
	* <����� 1�>
	* Line 2
	* Line 3
	*/


	// ��� flush 
	cout << "Line�1...";
	std::usleep(1000000);
	cout << "\nLine�2" << endl;
	cout << "Line�3" << endl;

	/*
	* output:
	* <����� 1�>
	* Line 1�
	* Line 2
	* Line 3
	*/

}

void Topic3() { // i/o fstream

	//������ ������ � ������� stream

	/*
	* ������������������
	* �������- ������� - �������
	*/

	fin.open("infile.txt");
	fout.open("outfile.txt");
	int num1, num2, num3;
	fin >> num1 >> num2 >> num3;
	fout << "The�sum�is�" << num1 + num2 + num3 << endl;
	fin.close();
	fout.close();


	while (stream >> buffer) {
		// { . . . }
	}
}

void Topic4() { // stringstream

	// ��������� ������� ����� � ����� ��� ����������, ��� �������

	int countWords(string const& str) {
		//�breaking�input�into�word�using�string�stream
		std::stringstream s(str); //�Used�for�breaking�words
		string word; //�to�store�individual�words

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
	ss.clear() == ss.str("") == true; // reset �����������
	

	string s = "geeks�for�geeks�geeks�"
		"contribution�placements";
	cout << "�Number�of�words�are:�" << countWords(s);


}

void Topic5() { // ������� ���������� �������

	/*
	* ������ ������������ �����
	* �����������, "��������� � ����"
	* Bool->int, short->int, char->int, float->double (������� �����������)
	* ����������� ����� ������������ �������������� (double->float, double->int)
	* ����� ���������������� ��������������
	*/

	void�func(char*);
	void�func(std::string�const&);
	void�func(int);

	/*
	* ���������� ���������� ������� ������ ����� ����������
	* ������������ ����� ��������� � ��������� ����������
	*/

}

void Topic6() { // ����������� �����������

	/*
	* ���������� ������:
	* ������� ���, ������� �������� ��������� � �������� ���������
	* ��� ������ ����� ������
	* 
	* � �++ ���������� ��������, ����������� �������� ������ ����,
	* ������� ����� ����������������� � ������������ �� ���������� ����������
	* �.�. ������� ��� �����������������
	* 
	* Template - ���� ����������� �������� �������, ����������� ���� � �� ��
	* �������� ��� ��������� ����� ������
	*/

	template <typename T>
	T sqr(T x)
	{
		return x * x;
	}

	/*
	* ��� ������ sqr ����������� ������� 2 ����:
	* 1. ����������� ��������� ���� � �������� ����������
	* 2. ���������� ������� = ����������� ���� ������ � �������� ����������
	*/
	std::cout << sqr(1.0); // double sqr(double)
	std::cout << sqr(1); // int sqr(int)
	std::cout << sqr(1.0f); // float sqr(float)

	sqr<double>(1); // double sqr(double)
	sqr<int>(1.0); // int sqr(int)
	sqr<float>(1.0f); // float sqr(float)
}

void Topic7() { // ����� ���� �������

	template<typename T>
	void f(ParamType param);

	f(expr);

	/*
	* ����� ������������ ��� T � ParamType
	*/

	//������
	template<typename T>
	void f(T & param);

	int x = 27; //�x�is�an�int
	const int cx = x; //�cx�is�a�const�int
	const int& rx = x; //�rx�is�a�reference�to�x�as�a�const�int

	f(x); //�T�is�int,�param's�type�is�int&
	f(cx);//�T�is�const�int,�param's�type�is�const�int&
	f(rx);//�T�is�const�int,�param's�type�is�const�int&


}

void Topic8() { // ��������� ������� � �������������

	/*
	* -������� ����� ����������������� ������ ���������
	* -������������� �������� ������������ ���������
	*/

	template <class T>
	void f(T ); //�(a)���������� ������� - ��������� ������

	template <class T>
	void f(T*); //�(b) ����������� (a), ��������� ������

	template <>
	void f<int>(int *); //�(c), ������������ (b)

	int * p;
	f(p); // (c)

}

void Topic9() { // ���������� ���������� ��������� �������

	/*
	* -����������������� � �������, ������� �� �������� ���������. 
	* ��� ���������� ���������� ������� ����������� ������� 
	* ����� ��������� ��� ������� ���������� ����� ���������� (���������)
	* 
    * -���� ����� ������� ���, �� ��������������� ��������� ������� �������.
	* ���������� �������� ���������� ��������� ������ �������.
	* 
    * ���� � ���������� ���������� ������� ���� �������������,
	* �� � ���������� ��������������� ���.
	*/

	// ������������� �������� ������� �� ��������� � ���������� ����������!

	template <class T>
	void f(T);          //(a),�primary

	template <>
	void f<int*>(int*); //(b)�spec�of�(a)

	template <class T>
	void f(T*);         //(c),�primary,�overload
	//��
	int * p;
	f(p);//�the�answer�is�(c)


}

void Topic10() { // ������� �������


	//������� ������� - ����� ���������� ��������� �������
	 
	/*
	* ����� �������� ��� ���������� ��������� ���������� �����
	* 
	* ����� �������� ��� ���������� ��������� ����������� �������
	* -������������ ������������� ������. ������ �������� ������
	* -������ ������������ ������. ������������� ������������� �������
	* ��� �������������� ��������� ����� ������
	*/

	template <class blob_footprint_policy>
	class vl_projector
	{
	private:
		blob_footprint_policy m_blob_fp;
	};



	//������

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

void Topic11() { // ��������� ������������� �������

	template<class T1, class T2, int I>// ���� �������� ������� ���,
	                                   // �� ����� ��� ������ ����
	                                   // �������������� prvalue
	                                   // (��������, ��������� �� compile time)
	                                   // ��� ��� template ��������� �� ����� �����������
	class A {};//��������� ������

	template<class T, int I>
	class A<T, T*, I> {}; //�#1:���������� �������������, ���T2���������� ��T1

	template<class T, class T2, int I>
	class A<T*, T2, I> {};//�#2:���������� �������������, ���T1����������

	template<class T>
	class A<int, T*, 5> {}; //�#3:���������� �������������, ���T1����int,�I����5,
							//������T2���� ���������
	template<class X, class T, int I>
	class A<X, T*, I> {};   //�#4:���������� �������������, ���T2����������


}

void Topic12() { // auto

	/*
	* auto - ������������� ��������� ��� � �++11
	* -���������� ����������� ����������
	* -������� ��������� ���� - ����� ��, ��� � ��� ��������
	* -���������� ����������� ��������� ��������
	*/

	auto x  = 1;         //x�:�int
	float* p;
	auto x = p;          //x�:�float*
	auto* y = p;         //y�:�float*
	double f();
	auto x = f();        //x�:�double
	const auto& y = f(); //y�:�const�double&
	class R;
	R* h();
	auto* x = h();       //x�:�R*
	auto y = h();        //y�:�R*
	int& g();
	auto x = g();        //x�:�int
	const auto& y = g(); //y�:�const�int&
	auto* z = g();       //error,�g()�does�not�return�a�pointer�type�


	/*
	* ������������ �� auto:
	* -�������� ������������ ��� ����������� ���� 
	* -����������� �������� �� ���������� � ������� auto
	* -��� ������� �������� � template'���
	*/
}

void Topic13() { //Braced-init-list & initializer_list

	/*
	* std::initializer_list
	* -������ ������ ���������� ������ ����
	* -����������� � intitializer_list ������ ������������ ���������
	*/

	class A {
	public:
		A(int a, int b) { cout << "A()" << endl; }
		A(std::initializer_list<int> args) { cout << "A{�}" << endl; }
	};

	auto x = {1, 2}; // x - initializer_list
	A a1(x);     // A{ }
	A a2 {1, 2}; // A{ } (braced initialization)
	A a3 (1, 2); // A()
}

void Topic14() { // Braced initialization

	/*
	* -���������������� � ������� {}
	* -��� �������� ��������� ��������������
	* -��� Most vexing parse(���������� ���������� = ���������� �������) (TimeKeeper�time_keeper(Timer());)
	* -����������� � ��������� �������������
    */

	//�create�a�vector�of�two�elements�initialized�to [1,�1]
	std::vector<int> v(2, 1); 

	//�create�a�vector�containing�two�elements:�[2,�1]
	std::vector<int> v{2, 1};
	//�same
	std::vector<int> v = {2, 1};

	//�initializer_list
	auto x = { 1 };

	// int!!!
	auto y { 2 };


}

void Topic15() { // Template algorithm + Strategy

	/*
	* 
	* ��������������� ��������� �������� ������ �� ��������� ������ ���������
	* 
	* ������� "���������"
	* -��������� �������� ������� ����������
	* -��������� ������ �������� ������
	* 
	* ������� � ������ "���������"
	* -��������� ������ ��������� ������
	* -����� ���� ����������� ��� ��������
	* -���� ��� ������, ���������������� ������ "���������"
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
				logger << "Update�voxel�values:�" << Logger::KeepLine << vgrid.getSliceCount();
				for (auto i = 0; i < vgrid.getSliceCount(); ++i) {
					voxUpdate.calcSliceDenominator(convResult);
					voxUpdate.updateSlice();
				}
			}
	};


}

void Topic16() { // Strategy + Template Algorithm 

	//Strategy: ������������ �����������
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
			cout << "ZIP�compression" << endl;
		}
	};



	//Template Algorithm: ������������ �����������
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


	//Template Algorithm: ����������� �����������
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

void Topic17() { // ������� ������������ �����������

	// ������ ����� ������ ������������� ���� ���������� �����������

	/*
	* ��� - ����������� ��� ������
	* -��������� ��������� ������ + ������
	* 
	* Single Responsibility Principle (SRP)
	* -����� ������ ����� ���� ���� ������� ��� ���������
	* 
	* ����������� = ��� ���������
	* -��������� �����: ������ + ������ = ���
	* -������� SRP: ������ ����� ��������� 1 ���
	*/

}