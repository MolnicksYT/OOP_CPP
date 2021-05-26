#include"Element.h"

template<typename T>int Element<T>::count = 0; // инициализация статической переменной
template<typename T>
const Element<T>* Element<T>::getpNext()const
{
	return pNext;
}
template<typename T>
T Element<T>::getData()const
{
	return Data;
}
template<typename T>Element<T>::Element(T Data, Element* pNext) : Data(Data), pNext(pNext)
{
	count++;
#ifdef CONSTRUCTOR
	cout << "EConstructor:\t" << this << endl;

#endif // CONSTRUCTOR
}
template<typename T>Element<T>::~Element()
{
	count--;
#ifdef DESTRUCTOR
	cout << "EDestructor:\t" << this << endl;
#endif // DESTRUCTOR
}