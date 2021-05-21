#include<iostream>
#include<exception>
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
#define delimetr "\n----------------------------------------\n"
//#define CONSTRUCTOR
//#define DESTRUCTOR

class ForwardList;

class Element
{
	int Data;		// значение элемента
	Element* pNext; // указатель на следующий элемент (pointer to next)
	static int count;
public:
	const Element* getpNext()const;
	int getData()const;
	Element(int Data, Element* pNext = nullptr);
	~Element();
	friend class Iterator;
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
int Element::count = 0; // инициализация статической переменной
const Element* Element::getpNext()const
{
	return pNext;
}
int Element::getData()const
{
	return Data;
}
Element::Element(int Data, Element* pNext) : Data(Data), pNext(pNext)
{
	count++;
#ifdef CONSTRUCTOR
	cout << "EConstructor:\t" << this << endl;

#endif // CONSTRUCTOR
}
Element::~Element()
{
	count--;
#ifdef DESTRUCTOR
	cout << "EDestructor:\t" << this << endl;
#endif // DESTRUCTOR
}
class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr);
	~Iterator();
	//operators
	Iterator& operator++();
	Iterator operator++(int);
	bool operator==(const Iterator& other)const;
	bool operator!=(const Iterator& other)const;
	const int& operator*()const;
	int& operator*();
	Element* operator->()const;
	Element* operator->();
};
Iterator::Iterator(Element* Temp):Temp(Temp)
{
	cout << "IConstructor:\t" << this << endl;
}
Iterator::~Iterator()
{
	cout << "IDestructor:\t" << this << endl;
}
//operators
Iterator& Iterator::operator++()
{
	Temp = Temp->pNext;
	return *this;
}
Iterator Iterator::operator++(int)
{
	Iterator old = *this;
	Temp = Temp->pNext;
	return old;
}
bool Iterator::operator==(const Iterator& other)const
{
	return this->Temp == other.Temp;
}
bool Iterator::operator!=(const Iterator& other)const
{
	return this->Temp != other.Temp;
}
const int& Iterator::operator*()const
{
	return Temp->Data;
}
int& Iterator::operator*()
{
	return Temp->Data;
}
Element* Iterator::operator->()const
{
	return Temp;
}
Element* Iterator::operator->()
{
	return Temp;
}
class ForwardList
{
	unsigned int size;
	Element* Head; // указатель на начальный элемент списка
public:
	unsigned int get_size()const
	{
		return size;
	}
	const Element* getHead()const
	{
		return Head;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	// constructors:

	ForwardList()
	{
		this->size = 0;
		this->Head = nullptr; // nullptr в Head означает, что список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>&il):ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		/*for (const int* it = il.begin(); it != il.end();it++)
		{
			push_back(*it);
		}*/
		for (int i : il)
		{
			push_back(i);
		}
		cout << "ILConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		for (Element* Temp = other.Head; Temp;Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other)
	{
		this->size = other.size;
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "LMoveConstructor:\t" << this << endl;

	}
	~ForwardList()
	{
		while (Head)pop_front();
		//popback - slow!!!
		cout << "LDestructor:\t" << this << endl;
	}
	// Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		//0) Проверяем, не является ли список самим собой:
		if (this == &other)return *this;
		// очищаем список от старых значений
		while (Head)pop_front();
		//2) копируем список:
		for (Element* Temp = other.Head; Temp;Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		while (Head)pop_front();
		this->size = other.size;
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "LMoveAssignment:\t" << this << endl;
		return *this;

	}
	int& operator[](int index)
	{
		if (index >= size)throw std::exception("Out of Range");
		Element* Temp = Head;
		for (int i=0; i< index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}
	// adding elements:
	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;*/
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;
		size++;
	}
	void insert(int Index, int Data)
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
			New->pNext= Temp->pNext;
		Temp->pNext = New;
		size++;
	}
	//removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		//1) запоминаем адрес удаляемого элемента
		Element* erase_element = Head;
		Head = Head->pNext;
		//3) удаление последнего элемента из списка
		delete erase_element;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
			if (Head->pNext == nullptr)
			{
				pop_front();
				return;
			}
		//1) запоминаем адрес удаляемого элемента
		Element* Temp = Head;
		//2) переход до последнего элемента
		while (Temp->pNext->pNext != 0 )
		{
			Temp = Temp->pNext; 
		}
		//3) удаление последнего элемента из памяти
		delete Temp->pNext;
		//4) Соощаем о конце списка
		Temp->pNext = nullptr;
		size--;
		
	}
	void erase(int index)
	{
		if (index > Element::count)return;
		if (index == 0)
		{
			pop_front();
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < index-1; i++)
	Temp = 	Temp->pNext;
		Element* element_erase = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete element_erase;
		size--;

	}

	//Methods:
	void print()const
	{ // чтобы ходить по списку нужны:
		//1) Итератор
		/*Element* Temp = Head; // Temp - это итератор. Итератор - указатель при помощи которого получают доступ к элементам структуры данных
		//2) Цикл:
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; // переход на следуюший элемент
		}
		cout << "В списке " << size << " элементов\n";
		cout << "Общее кол-во элементов: " << Element::count << endl;*//////////////////////////////////////////////////////////////////////
		for (Iterator Temp = Head; Temp != nullptr;Temp++)
			cout << *Temp << tab;
			//cout /*<< Temp << tab */<< Temp->Data << tab << Temp->pNext << endl;
		cout << "В списке " << size << " элементов\n";
		cout << "Общее кол-во элементов: " << Element::count << endl;
	}
};
ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	for (const Element* Temp = right.getHead(); Temp; Temp = Temp->getpNext())
		cat.push_back(Temp->getData());
	return cat;
}
//#define COPY_METHODS_CHECK
#define HARDCORE
//#define BASE_CHECK
//#define ADDING_ELEMENTS_CHAR
//#define REMOVING_CHECK
//#define OPERATOR_PLUS_CHECK
#define FACTORIAL
void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Ввести размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0;i < n;i++)
	{
		list.push_back(rand() % 100);
	}
	list = list;
	list.print();
	cout << delimetr << endl;
	ForwardList	list2; // copyconstractor
	list2 = list;
	list2.print();
#endif // BASE_CHECK

#ifdef COPY_METHODS_CHECK

		cout << "List ready" << endl;
	list.~ForwardList();
	list.print();
	list.pop_front();
	list.pop_back();
	list.print();
	int value;
	int index;
	cout << "Ввести индек добаляемого элемента: "; cin >> index;
	cout << "Ввести добавяемое значение: "; cin >> value;
	list.push_back(value);
	list.insert(index, value);
	list.print();
	ForwardList list2;
	cout << "Ввести размер списка: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		list2.push_back(rand() % 100);
	}
	list2.print();
#endif // COPY_METHODS_CHECK
#ifdef OPERATOR_PLUS_CHECK

	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	cout << delimetr << endl;
	ForwardList list2;
	list1.push_back(34);
	list1.push_back(55);
	list1.push_back(89);
	list1.push_back(144);
	//////////////////////////////
	cout << delimetr << endl;
	ForwardList list3;
	list3 = list1 + list2;
	list3.print();
	cout << delimetr << endl;
	/////////////////////////////
#endif  //OPERATOR_PLUS_CHECK
#ifdef HARDCORE
	int arr[] = { 3,5,7,13,21,32,55 };
	cout << sizeof(Element) << endl;
	ForwardList list = { 3,5,7,13,21 };
	//range-based for (Диапазонный фор, фор для контейнера, для структуры данных)
	for (int i : list)
	{
		cout << i << tab;
}
	cout << endl;
	//try
	//{ 
	//for (int i = 0;i <list.get_size();i++)
	//{
	//	list[i] = rand() % 100;
	//}
	//for (int i = 0;i < 10;i++)
	//{
	//	cout << list[i] << tab;
	//}
	//}
	//catch (std::exception& e)
	//{
	//	std::cerr << e.what() << endl; // метод what() - возвращает сообщение об ошибке
	//}
	/*int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr)/ sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}

	for (int i = 0;i < list.get_size();i++)
	{
		cout << list[i] << tab;
	}*/
#endif // HARDCORE
}
