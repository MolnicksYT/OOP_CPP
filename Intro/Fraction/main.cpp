#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);
#define DEBUG
class Fraction
{
	int integer; // целая часть
	int numerator; // числитель
	int denominator; // знаменатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}
	//constructors
	Fraction() :integer (0), numerator (0), denominator(1)
	{
	/*	this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;*/
#ifdef DEBUG
		cout << "DefaultConstructor:\t" << this << endl;
#endif // DEBUG

	}
	explicit Fraction(int integer):integer(integer), numerator(0), denominator(1)
	{
	/*	this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;*/
#ifdef DEBUG
		cout << "SingleArumentConstructor:" << this << endl;
#endif // DEBUG

	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		this->set_denominator(denominator);
#ifdef DEBUG
		cout << "constructor:\t\t" << this << endl;
#endif // DEBUG

	}
	Fraction(int integer , int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator);
#ifdef DEBUG
		cout << "constructor:\t" << this << endl;
#endif // DEBUG

	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator= other.denominator;
#ifdef DEBUG
		cout << "Copyconstructor\t" << this << endl;
#endif // DEBUG

	}
	~Fraction()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG
	}
	Fraction(double decimal) //////////////////////////////////////
	{
		decimal += 1e-15;
		integer = decimal;
		decimal -= integer;
		denominator = 1e+9;
		numerator = decimal * denominator;
		reduce();
	}
	//operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
#ifdef DEBUG
		cout << "CopyAssignment\t" << this << endl;
#endif // DEBUG

		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}
	Fraction operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}
		/*Fraction operator*(const Fraction & other)const
		{
			Fraction left = *this;
			Fraction right = other;
			left.to_improper();
			right.to_improper();
			return Fraction
			(
				left.numerator * right.numerator,
				left.denominator * right.denominator
			);
		}*/
		//increment/decrement
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}
	//type cast operators:
	explicit operator int()const
	{
		return integer;
	}
	explicit operator double()const
	{
		return integer + (double)numerator / denominator;
	}
		//metods
	Fraction to_proper()
	{
		integer += numerator / denominator;
			numerator %= denominator;
			return *this;
	}
	Fraction to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
		/*Fraction copy = *this;
		copy.numerator += copy.integer * copy.denominator;
		copy.integer = 0;
		return copy;*/
	}
	Fraction& reduce()
	{
		if (numerator == 0)return *this;
		//1) определяем кто больше, числитель или знаменатель
		int more, less, rest;
		if (numerator > denominator)more = numerator, less = denominator;
		else less = numerator, more = denominator;
		//2) вычисляем наибольший общий делитель (НОД - GCD);
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; // greatest common divisor - наибольший общий делитель
		//3) сщкращаем дробь
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		swap(inverted.numerator, inverted.denominator);//функция swap меняет местами 2 переменные
		return inverted;
	}
	void print()const
	{
		cout << integer << "(" << numerator << "/" << denominator << ")" << endl;
	}
};
Fraction operator+(Fraction left, Fraction right)
{
	left.to_proper();
	right.to_proper();
	Fraction result;
	result.set_integer(left.get_integer() + right.get_integer());
	result.set_numerator(left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator());
	result.set_denominator(left.get_denominator() * right.get_denominator());
	result.to_proper();
	result.reduce();
	return result;
}
Fraction operator-(Fraction left, Fraction right)
{
	left.to_proper();
	right.to_proper();
	Fraction result
	(
		left.get_integer() - right.get_integer(),
		left.get_numerator() * right.get_denominator() - right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	);
	result.to_proper();
	result.reduce();
	return result;
}
Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator/(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();
	return Fraction
	{
		left.get_numerator() * right.get_denominator(),
		right.get_numerator() * left.get_denominator(),
	};*/
	return left * right.inverted();
}
/////	comparison operators	/////

bool operator==(Fraction left, Fraction right)
{

	left.reduce().to_improper();
	right.reduce().to_improper();
	return left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator();

}

bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);	
}
/////	stram operators	/////
ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}
//#define ARIFMETICAL_OPERATORS
//#define CONSTRUCTORS_CHECK
//#define COMPAUND_ASSIGNMENTS
//#define INCREMENT_CHECK
//#define COMPARISON_OPERATORS
//#define TYPE_CONVERSIONS
void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	Fraction A; //default constructor
	A.print();
	cout << A << endl;
	double b = 5;
	Fraction B = 5;
	B.print();
	cout << B << endl;
	Fraction C(1, 2);
	C.print();
	cout << C << endl;
	Fraction D(3, 4, 5);
	D.print();
	cout << D << endl;
#endif // CONSTRUCTORS_CHECK
#ifdef ARIFMETICAL_OPERATORS
	Fraction A(11, 4);
	Fraction B(5, 6, 7);
	cout << "-------------------" << endl;
	Fraction C = A * B;
	cout << "-------------------" << endl;
	cout << C << "\t+" << endl;
	cout << "-------------------" << endl;
	C = A - B;
	cout << "-------------------" << endl;
	cout << C << "\t-" << endl;
	cout << "-------------------" << endl;
	cout << A / B << endl;
#endif // ARIFMETICAL OPERATORS
#ifdef COMPAUND_ASSIGNMENTS
	double a = 2;
	double b = 3;
	a *= 3;
	Fraction A(11, 4);
	Fraction B(5, 6, 7);
	cout << A << endl;
	cout << B << endl;
	A *= B;
	cout << A << endl;
	A /= B;
	cout << A << endl;
	cout << A - A << endl;
#endif // COMPAUND
#ifdef INCREMENT_CHECK
	for (double i = .3;i < 10;i++)
		cout << i << "\t";
	cout << endl;
	for (Fraction i(3, 4); i.get_integer() < 10; ++i) //prefix
		cout << i << tab;
	cout << endl;
	for (Fraction i(3, 4); i.get_integer() < 10; i++) //postfix
		cout << i << tab;
	cout << endl;
#endif // INCREMENT_CHECK
#ifdef COMPARISON_OPERATORS
	Fraction A(1, 2);
	Fraction B(5, 10);
	cout << A << endl;
	cout << B << endl;
	cout << endl;
	cout << (A == B) << endl;
	cout << (A != B) << endl;
	//cout << (Fraction(1, 2) == Fraction(5, 10)) << endl;
	cout << A << endl;
	cout << B << endl;
#endif // COMPARISON_OPERATORS
#ifdef TYPE_CONVERSIONS
	//int a = 43;
	//явное преобразование
	//cout << (char)a << endl; //c-like style
	//cout << char(a) << endl; //functional style
	//неявное преобразование
	//double b = 3.5;
	//cout << typeid(a + b).name() << endl;
	int a = 2; //no conversion
	double b = 3; // от меньшего к большему
	int c = 5.0;//от большего к меньшему без потери данных
	int c = 5.2; //от большего к меньшему с потерей данных
#endif //TYPE_CONVERSIONS
	//Fraction A = (Fraction)5;
	Fraction A(5); //explicit constructor можно выхывать только так, и невозможно вызвать оператором =
	cout << A << endl;
	A = (Fraction)8; //copyassignment
	cout << A << endl;
	Fraction B(3, 4, 5);
	double b = (double)B;
	cout << b << endl;
	Fraction C = 2.5498136546543565;
	cout << C << endl;

}