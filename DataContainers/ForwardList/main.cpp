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
	Element* pNext; // указатель на следующий элемент (pointer to next)
	static int count;
public:
	const Element* getpNext()const
	{
		return pNext;
	}
T getData()const
	{
		return Data;
	}
	Element(T Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
#ifdef CONSTRUCTOR
		cout << "EConstructor:\t" << this << endl;

#endif // CONSTRUCTOR
	}
	~Element()
	{
		count--;
#ifdef DESTRUCTOR
		cout << "EDestructor:\t" << this << endl;
#endif // DESTRUCTOR

	}
	friend class Iterator<T>;
	friend class ForwardList<T>;
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};
template<typename T>
int Element<T>::count = 0; // инициализация статической переменной
template<typename T>
class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) :Temp(Temp)
	{
		cout << "IConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "IDestructor:\t" << this << endl;
	}
	//operators
	Iterator<T>& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator<T> operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}
	const T& operator*()const
	{
		return Temp->Data;
	}
	T& operator*()
	{
		return Temp->Data;
	}
	const Element<T>* operator->()const
	{
		return Temp;
	}
	Element<T>* operator->()
	{
		return Temp;
	}
};
template<typename T>class ForwardList
{
	unsigned int size;
	Element<T>* Head; // указатель на начальный элемент списка
public:
	unsigned int get_size()const
	{
		return size;
	}
	const Element<T>* getHead()const
	{
		return Head;
	}
	Iterator<T> begin()
	{
		return Head;
	}
	Iterator<T> end()
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
	ForwardList(const std::initializer_list<T>& il):ForwardList()
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
	ForwardList(const ForwardList<T>& other) :ForwardList()
	{
		for (Element* Temp = other.Head; Temp;Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList<T>&& other)
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
	ForwardList<T>& operator=(const ForwardList<T>& other)
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
	ForwardList<T>& operator=(ForwardList<T>&& other)
	{
		while (Head)pop_front();
		this->size = other.size;
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "LMoveAssignment:\t" << this << endl;
		return *this;

	}
	T& operator[](T index)
	{
		if (index >= size)throw std::exception("Out of Range");
		Element* Temp = Head;
		for (int i=0; i< index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}
	// adding elements:
	void push_front(T Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;*/
		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
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
	void insert(int Index, T Data)
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
		Element<T>* erase_element = Head;
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
		Element<T>* Temp = Head;
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
template<typename T>
ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat = left;
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
	cout << sizeof(Element<int>) << endl;
	ForwardList<int> list = { 3,5,7,13,21 };
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
	ForwardList<double> dfl = { 2.5, 2.87, 3.14, 5.9, 8.5 };
	for (double i : dfl)cout << i << tab; cout << endl;
	ForwardList<std::string>stih = { "Хорошо", "живёт", "на", "свете", "Винни-Пух" };
	for (std::string i : stih)cout << i << tab; cout << endl;
#endif // HARDCORE
}
