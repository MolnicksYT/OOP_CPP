#include"string.h"
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
	//0))проверяем не явлеется ли другой объект нашим
	if (this == &other)return *this;
	//1) удаляем старое значение объекта
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
//конец опеределения класса

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);
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