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
