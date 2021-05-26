#pragma once
#include"Element.h"
template<typename T>
class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr);
	~Iterator();
	//operators
	Iterator<T>& operator++();
	Iterator<T> operator++(int);
	bool operator==(const Iterator<T>& other)const;
	bool operator!=(const Iterator<T>& other)const;
	const T& operator*()const;
	T& operator*();
	const Element<T>* operator->()const;
	Element<T>* operator->();
};