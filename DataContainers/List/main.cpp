#include<iostream>
#define tab "\t"
#define delimetr "======="
using namespace std;
class List
{
	class Element
	{
		int Data;
		Element* pPrev;
		Element* pNext;
	public:
		friend class List;
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			this->pPrev = pPrev;
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}

		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}

		friend class List;
		friend List operator+(const List& left, const List& right);
	};
	Element* Head;
	Element* Tail;
	unsigned int size;
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG
		}

		~Iterator()
		{
#ifdef DEBUG
			cout << "ITDestructor:\t" << this << endl;
#endif // DEBUG
		}
		
		// operator:
		Iterator& operator++()
		{
#ifdef DEBUG
			cout << "PrefixIncrement" << this << endl;
#endif // DEBUG

			Temp = Temp->pNext;
			return *this;
		}
		Iterator& operator++(int)
		{
#ifdef DEBUG
			cout << "PostfixIncrement" << this << endl;
#endif // DEBUG

			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	Iterator begin()const
	{
		return Head;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()const
	{
		return nullptr;
	}
	Iterator end()
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const initializer_list<int>& il) :List()
	{
		for (const int* it = il.begin();it != il.end();it++)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		for (Element* Temp = other.Head;Temp;Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyConstructor:" << this << endl;
	}
	List(List&& other)
	{
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = other.Tail = nullptr;
		cout << "MoveConstructor:" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//operators
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head;Temp;Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	List& operator=(List&& other)
	{
		while (Head)pop_front();
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = other.Tail = nullptr;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	//adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		//Head = new Element(Data, Head);
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;*/
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);

		size++;
	}
	// removing elements:
	void pop_front()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void insert(int Index, int Data)
	{
		if (Index >= size)return;
		if (Index == size)
		{
			push_back(Data);
			return;
		}
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0;i < Index;i++)
				Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0;i < size - Index - 1;i++)
				Temp = Temp->pPrev;
		}
		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;*/
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}
	void erase(int Index)
	{
		if (Index == 0)
		{
			pop_front();
			return;
		}
		if (Index == size - 1)
		{
			pop_back();
			return;
		}
		if (Index >= size)return;
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0;i < Index;i++)
				Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0;i < size - Index - 1;i++)
				Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}
	//methods:
	void print()
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << endl << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "???-?? ????????? ??????:\t" << size << endl;
	}
	void print_reverse()
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp << endl << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "???-?? ????????? ??????:\t" << size << endl;
	}
	friend List operator+(const List& left, const List& right);

};
List operator+(const List& left, const List& right)
{
	List cat = left; //copyconstructor
	/*for (List::Iterator it = right.begin();it != right.end();it++)
	{
		cat.push_back(*it);
	}*/
	for (int i : right)cat.push_back(i);
	return cat;
}
//#define BASE_CHECK
//#define COPY_METHODS_CHECK
#define OPERATOR_PLUS_CHECK
//#define ITERATOR_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "?????? ?????? ??????: ";cin >> n;
	List list;
	for (int i = 0;i < n;i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	cout << delimetr << "\n";
	list.print_reverse();
	//list.pop_front();
	//list.print();
	//list.print_reverse();
	list.pop_back();
	list.print();
	list.print_reverse();
	int index;
	int value;
	cout << "?????? ?????? ???????????? ????????: ";cin >> index;
	cout << "?????? ???????? ???????????? ????????: ";cin >> value;
	list.insert(index, value);
	list.print();
	list.print_reverse();
	cout << "?????? ?????? ?????????? ????????: ";cin >> index;
	list.erase(index);
	list.print();
	list.print_reverse();

#endif // BASE_CHECK
#ifdef COPY_METHODS_CHECK
	List list;
	list.push_back(3);
	list.push_back(5);
	list.push_back(8);
	list.push_back(13);
	list.push_back(21);
	list = list;
	List list2 = list; //copyconstructor
	list2.print();
	list2.print_reverse();
	List list3;
	list3 = list2;
	list3.print();
	list3.print_reverse();
#endif // COPY_METHODS_CHECK
#ifdef OPERATOR_PLUS_CHECK
	List list = { 3,5,7,13,21 };
	//list.print();
	//list.print_reverse();
	List list2 = { 34,55,89 };
	cout << delimetr;
	List list3 = list + list2; //moveassignment
	cout << delimetr;
	list3.print();
#endif // OPERATOR_PLUS_CHECK
#ifdef OPERATOR_CHECK
	List list = { 3,5,7,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	for (List::Iterator it = list.begin(); it != list.end();it++)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // OPERATOR_CHECK

}