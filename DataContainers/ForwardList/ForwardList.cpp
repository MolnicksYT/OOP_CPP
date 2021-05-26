#include"ForwardList.h"
template<typename T>unsigned int ForwardList<T>::get_size()const
{
	return size;
}
template<typename T>const Element<T>* ForwardList<T>::getHead()const
{
	return Head;
}
template<typename T>Iterator<T> ForwardList<T>::begin()
{
	return Head;
}
template<typename T>Iterator<T> ForwardList<T>::end()
{
	return nullptr;
}
// constructors:
template<typename T>ForwardList<T>::ForwardList()
{
	this->size = 0;
	this->Head = nullptr; // nullptr � Head ��������, ��� ������ ����
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(const std::initializer_list<T>& il) :ForwardList()
{
	cout << typeid(il.begin()).name() << endl;
	/*for (const int* it = il.begin(); it != il.end();it++)
	{
		push_back(*it);
	}*/
	for (T i : il)
	{
		push_back(i);
	}
	cout << "ILConstructor:\t" << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(const ForwardList<T>& other) :ForwardList()
{
	for (Element* Temp = other.Head; Temp;Temp = Temp->pNext)
		push_back(Temp->Data);
	cout << "LCopyConstructor:\t" << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(ForwardList<T>&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	other.Head = nullptr;
	cout << "LMoveConstructor:\t" << this << endl;

}
template<typename T>ForwardList<T>::~ForwardList()
{
	while (Head)pop_front();
	//popback - slow!!!
	cout << "LDestructor:\t" << this << endl;
}
// Operators:
template<typename T>ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
{
	//0) ���������, �� �������� �� ������ ����� �����:
	if (this == &other)return *this;
	// ������� ������ �� ������ ��������
	while (Head)pop_front();
	//2) �������� ������:
	for (Element* Temp = other.Head; Temp;Temp = Temp->pNext)
		push_back(Temp->Data);
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}
template<typename T>ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& other)
{
	while (Head)pop_front();
	this->size = other.size;
	this->Head = other.Head;
	other.Head = nullptr;
	cout << "LMoveAssignment:\t" << this << endl;
	return *this;

}
template<typename T>T& ForwardList<T>::operator[](T index)
{
	if (index >= size)throw std::exception("Out of Range");
	Element* Temp = Head;
	for (int i = 0; i < index; i++)
		Temp = Temp->pNext;
	return Temp->Data;
}
// adding elements:
template<typename T>void ForwardList<T>::push_front(T Data)
{
	/*Element* New = new Element(Data);
	New->pNext = Head;
	Head = New;
	size++;*/
	Head = new Element<T>(Data, Head);
	size++;
}
template<typename T>void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr)
	{
		push_front(Data);
		return;
	}
	Element<T>* New = new Element<T>(Data);
	Element<T>* Temp = Head;
	while (Temp->pNext != nullptr)
	{
		Temp = Temp->pNext;
	}
	Temp->pNext = New;
	size++;
}
template<typename T>void ForwardList<T>::insert(int Index, T Data)
{
	if (Index > Element::count)return;
	if (Index == 0)
	{
		push_front(Data);
		return;
	}
	Element* New = new Element(Data);
	Element* Temp = Head;
	for (int i = 0;i < Index - 1;i++)
		Temp = Temp->pNext;
	New->pNext = Temp->pNext;
	Temp->pNext = New;
	size++;
}
//removing elements:
template<typename T>void ForwardList<T>::pop_front()
{
	if (Head == nullptr)return;
	//1) ���������� ����� ���������� ��������
	Element<T>* erase_element = Head;
	Head = Head->pNext;
	//3) �������� ���������� �������� �� ������
	delete erase_element;
	size--;
}
template<typename T>void ForwardList<T>::pop_back()
{
	if (Head == nullptr)return;
	if (Head->pNext == nullptr)
	{
		pop_front();
		return;
	}
	//1) ���������� ����� ���������� ��������
	Element<T>* Temp = Head;
	//2) ������� �� ���������� ��������
	while (Temp->pNext->pNext != 0)
	{
		Temp = Temp->pNext;
	}
	//3) �������� ���������� �������� �� ������
	delete Temp->pNext;
	//4) ������� � ����� ������
	Temp->pNext = nullptr;
	size--;

}
template<typename T>void ForwardList<T>::erase(int index)
{
	if (index > Element::count)return;
	if (index == 0)
	{
		pop_front();
		return;
	}
	Element* Temp = Head;
	for (int i = 0; i < index - 1; i++)
		Temp = Temp->pNext;
	Element* element_erase = Temp->pNext;
	Temp->pNext = Temp->pNext->pNext;
	delete element_erase;
	size--;

}

//Methods:
template<typename T>void ForwardList<T>::print()const
{ // ����� ������ �� ������ �����:
	//1) ��������
	/*Element* Temp = Head; // Temp - ��� ��������. �������� - ��������� ��� ������ �������� �������� ������ � ��������� ��������� ������
	//2) ����:
	while (Temp != nullptr)
	{
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		Temp = Temp->pNext; // ������� �� ��������� �������
	}
	cout << "� ������ " << size << " ���������\n";
	cout << "����� ���-�� ���������: " << Element::count << endl;*//////////////////////////////////////////////////////////////////////
	for (Iterator Temp = Head; Temp != nullptr;Temp++)
		cout << *Temp << tab;
	//cout /*<< Temp << tab */<< Temp->Data << tab << Temp->pNext << endl;
	cout << "� ������ " << size << " ���������\n";
	cout << "����� ���-�� ���������: " << Element::count << endl;
}
template<typename T>
ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat = left;
	for (const Element* Temp = right.getHead(); Temp; Temp = Temp->getpNext())
		cat.push_back(Temp->getData());
	return cat;
}