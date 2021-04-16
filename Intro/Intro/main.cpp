#include<iostream>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
class Point
{ 
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}
	//Constructors:
	/*Point()
	{
		x = y = 0;
		cout << "DefConstructor:\t" << this << endl;
	}
	Point(double x)
	{
		this->x = x;
		this->y = 0;
		cout << "singleargumentconstructor:\t" << this << endl;
	}*/
	Point(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
		cout << "constructor:\t" << this << endl;
	}
	Point(const Point& other)
	{
		//
		//
		this->x = other.x;
		this->y = other.y;
		cout << "copyconstructor:" << this << endl;
	
	}
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}
	// Operators
	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "copyassignment:\t" << this << endl;
		return *this;
	}
	Point& operator+=(const Point& other)
	{
		this->x += other.x;
		this->y += other.y;
		cout << "operator+=" << this << endl;
		return *this;
	}
	
	/*Point operator+(const Point& other)
	{
		Point result;
		result.x = this->x + other.x;
		result.y = this->y + other.y;
		cout << "Operator +" << this << endl;
		return result;
	}*/
	//Increment/Decrement
	Point& operator++() // prefix increment
	{
		this->x++;
		this->y++;
		return *this;
	}
	Point& operator++(int) // postfix increment
	{
		Point old = *this;
		this -> x++;
		this -> y++;
		return old;
	}
	// Methods
	void print()const
	{
		cout << "x = " << x << tab << "y = " << y << endl;
	}
};
// создава€ структуру или класс мы создаЄм новый тип данных
// class - тип данных
// struct - тип данных
// объекты класса или структуры €вл€ютс€ переменными соответвствующего типа
Point operator+(const Point& left,const Point& right)
{
	Point result;
	result.set_x(left.get_x() + right.get_x());
	result.set_y(left.get_y() + right.get_y());
	cout << "============" << endl;
	cout << "global plus" << endl;
	cout << "============" << endl;
	return result;
}
Point operator-(const Point& left, const Point& right)
{
	Point result(left.get_x() + right.get_x(), left.get_y() + right.get_y());
	cout << "============" << endl;
	cout << "global minus" << endl;
	cout << "============" << endl;
	return result;
}
Point operator*(const Point& left, const Point& right)
{
	cout << "============" << endl;
	cout << "global multiply" << endl;
	cout << "============" << endl;
	return Point
	(
		left.get_x() * right.get_x(),
		left.get_y() * right.get_y()
	);
}
Point operator/(const Point& left, const Point& right)
{
	cout << "============" << endl;
	cout << "global devision" << endl;
	cout << "============" << endl;
	return Point
	(
		left.get_x() / right.get_x(),
		left.get_y() / right.get_y()
	);
}
ostream& operator<<(ostream& os, const Point& obj)
{
	return os << "X = " << obj.get_x() << tab << "Y = " << obj.get_y();
}
void function(Point* pA)
{
	cout << pA->get_x() << tab << pA->get_y() << endl;
}
//#define INTRO
//#define CONSTRUCTORS_CHECK
//#define ASSIGNMENT_CHECK
//#define ARIFMETICAL_OPERATORS
void main()
{
#ifdef INTRO
	setlocale(LC_ALL, "");
	int a; // объ€вление переменной 'a' типа int
	Point A; // объ€вление переменной 'A' типа point
	// создание объекта
	A.set_x(2);
	A.set_y(3);
	cout << A.get_x() << tab << A.get_y() << endl;

	Point* pA = &A; // pA - pointer to 'A'
	cout << pA->get_x() << tab << pA->get_y() << endl;
	//cout << pA->x << tab << *pA-> y << endl;
	cout << sizeof(A) << endl;
	cout << sizeof(pA) << endl;
#endif // INTRO
#ifdef CONSTRUCTORS_CHECK

	Point A;//default
	A.print();
	Point B(2, 3);//single argument constructor
	B.print();


	Point C = 5;//single argument constructor
	C.print();
	Point D(8); // single argument constructor
	D.print();
	int b(3); // €кобы дл€ типа int вызываетс€ конструктор с 1 параметром
	cout << int() << endl; // €кобы вызываетс€ конструктор по умолчанию дл€ типа int и возвращает значени€ по умолчанию дл€ типа int
	// так можно получить значение по умолчанию дл€ любого типа
	Point E{ 13 }; // single argument constructor
	E.print();
	int c{ 5 };
	cout << c << endl;
	cout << int{} << endl; // значение по умолчанию дл€ int

	Point F = B; //copy constructor
	F.print();
	Point G; ///default constructor
	G = F; // copyassignment  
#endif // CONSTRUCTORS_CHECK
#ifdef ASSIGNMENT_CHECK
	int a, b, c;
	a = b = c = 0;
	Point A, B, C;
	A = B = C = Point();
#endif // ASSIGNMENT_CHECK
#ifdef ARIFMETICAL_OPERATORS
	int a = 2;
	int b = 3;
	int c = a + b;

	Point A(2, 3);
	Point B(3, 4);
	A.print();
	B.print();
	Point C = A + B;
	C.print();
	(A - B).print();
	(A * B).print();
	(A / B).print();
	A.print();
	B.print();
#endif // ARIFMETICAL_OPERATORS
	Point A(2, 3);
	Point B(3, 4);
	A += B; // не€вный вызов оператора
	A.print();
	A.operator+=(B); // €вный вызов оператора
	A.print();
	operator/(A, B).print(); // €вный вызов глобального оператора
	cout << "prefix" << endl;
	++A;
	A.print();
	cout << "postfix" << endl;
	A++;
	A.print();
	cout << A << endl;
}