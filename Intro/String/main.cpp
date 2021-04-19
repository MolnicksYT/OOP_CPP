#include"String.h"
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
	String str3 = str1 + str2;//оператор + будет выполнять конкатенцацию (слияние) строк
	cout << str3 << endl;
#endif // ASSIGNMENT_CHECK
	String str1; //default constructor
	String str2(); //объявляется ф-ция str2, которая ничего не принимает и возвращает значение типа string
	String str3{};//default constructor
	String str4(5);//size constructor
	String str5{ 8 };
	String str6("Hi");
	String str7{"Hello"};
	cout << str7 << endl;
	//String str8 = 16; //неявное преобразование int в string
}