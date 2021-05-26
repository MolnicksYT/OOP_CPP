#pragma once
#include "Iterator.h"
template<typename T>class ForwardList
{
	unsigned int size;
	Element<T>* Head; // указатель на начальный элемент списка
public:
	unsigned int get_size()const;
	const Element<T>* getHead()const;
	Iterator<T> begin();
	Iterator<T> end();
	// constructors:
	ForwardList();
	ForwardList(const std::initializer_list<T>& il);
	ForwardList(const ForwardList<T>& other);
	ForwardList(ForwardList<T>&& other);
	~ForwardList();
	// Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other);
	ForwardList<T>& operator=(ForwardList<T>&& other);
	T& operator[](T index);
	// adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(int Index, T Data);
	//removing elements:
	void pop_front();
	void pop_back();
	void erase(int index);
	//Methods:
	void print()const;
};
