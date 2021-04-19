#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
using std::endl;
using std::cout;
using std::cin;
class String;
String operator+(const String& left, const String& right);
//объ€вление класса - class declaration
class String
{
	char* str;
	int size;

public:
	const char* get_str()const;
	char* get_str();
	int get_size()const;
	//constructors
String(int size = 80);
	String(const char* str);
	String(const String& other);
	String(String&& other);
	~String();
	//Operators:
	String& operator=(const String& other);
	String& operator+=(const String& other);
	const char& operator[](int index)const;
	char& operator[](int index);
	String& operator=(String&& other);
	//Methods:
	void Print()const;
};
//конец объ€влени€ класса - class declaration end
//определение класса
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}
int String::get_size()const
{
	return size;
}
//constructors
String::String(int size) :size(size), str(new char[size] {})
{
	//this->size = size;
	//this->str = new char[size] {};
	cout << "DefaultConstructor:\t" << this << endl;
}
String::String(const char* str) :String(strlen(str) + 1)
{
	//this->size = strlen(str) + 1;
	//this->str = new char[size] {};
	strcpy(this->str, str);
	cout << (size == 80 ? "Default" : "Size") << "constructor:\t\t" << this << endl;
}
String::String(const String& other) :String(other.str)
{
	//this->size = other.size;
	//this->str = new char[size] {};
	//strcpy(this->str, other.str);
	cout << "CopyConstructor:\t" << this << endl;
}
String::String(String&& other) :size(other.size), str(other.str)
{
	//this->size = other.size;
	//this -> str = other.str;
	other.str = nullptr;
	cout << "Moveconstructor:\t" << this << endl;
}
String::~String()
{
	delete[] this->str;
	cout << "Destructor:\t\t" << this << endl;
}
//Operators:
String& String::operator=(const String& other)
{
	//0))провер€ем не €влеетс€ ли другой объект нашим
	if (this == &other)return *this;
	//1) удал€ем старое значение объекта
	delete[] this->str;
	//2) присваеваем новое значение объекту
	this->size = other.size;
	this->str = new char[size] {};
	strcpy(this->str, other.str);
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}
String& String::operator+=(const String& other)
{
	return *this = *this + other;
}
const char& String::operator[](int index)const
{
	return this->str[index];
}
char& String::operator[](int index)
{
	return this->str[index];
}
String& String::operator=(String&& other)
{
	delete[] this->str;
	this->size = other.size;
	this->str = other.str;
	other.str = nullptr;
	cout << "Moveassignment:\t\t" << this << endl;
	return *this;
}
//Methods:
void String::Print()const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}
//конец опеределени€ класса
String operator+(const String& left, const String& right)
{
	String result (left.get_size() + right.get_size() - 1);
	for (int i = 0;i < left.get_size();i++)
		//result.get_str()[i] = left.get_str()[i];
		result[i] = left[i];
	for (int i = 0;i < right.get_size();i++)
		result[i + left.get_size() - 1] = right[i];
	return result;
}
ostream& operator<<(ostream& os, const String& obj)
{
	return os << obj.get_str();
}
//#define CONSTRUCTORS_CHECK
//#define ASSIGNMENT_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	String str;
	str.Print();
	String str2 = "Hello";
	str2.Print();
	cout << "Hello" << endl;
	String str3 = str2;
	cout << "Str3:\t" << str3 << endl;
	String str4;
	str4 = str3;
	cout << "Str4:\t" << str << endl;
	int a = 2;
	int b = 3;
	a = b;
	cout << a << endl;
#endif // CONSTRUCTORS_CHECK
#ifdef ASSIGNMENT_CHECK
	String str1 = "Hello";
	String str2 = "World";
	//str1 += str2;
	//cout << str1 << endl;
	String str3 = str1 + str2;//оператор + будет выполн€ть конкатенцацию (сли€ние) строк
	cout << str3 << endl;
#endif // ASSIGNMENT_CHECK
	String str1; //default constructor
	String str2(); //объ€вл€етс€ ф-ци€ str2, котора€ ничего не принимает и возвращает значение типа string
	String str3{};//default constructor
	String str4(5);//size constructor
	String str5{ 8 };
	String str6("Hi");
	String str7{"Hello"};
	cout << str7 << endl;
	//String str8 = 16; //не€вное преобразование int в string
}