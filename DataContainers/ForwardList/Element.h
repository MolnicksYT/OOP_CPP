#pragma once
#include<iostream>
#include<string>
#include<exception>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimetr "\n----------------------------------------\n"

template<typename T>class Iterator;
template<typename T>class ForwardList;
//#define CONSTRUCTOR
//#define DESTRUCTOR
template<typename T>class Element
{
	T Data;		// значение элемента
	Element<T>* pNext; // указатель на следующий элемент (pointer to next)
	static int count;
public:
	const Element<T>* getpNext()const;
	T getData()const;
	Element(T Data, Element* pNext = nullptr);
	~Element();
	friend class Iterator<T>;
	friend class ForwardList<T>;
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};
