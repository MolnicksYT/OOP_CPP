#include"Element.h"
#include"Iterator.h"
#include"Element.cpp"
#include"Iterator.cpp"
#include"ForwardList.h"
#include"ForwardList.cpp"

using std::cin;
using std::cout;
using std::endl;

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
	cout << "¬вести размер списка: "; cin >> n;
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
	cout << "¬вести индек добал€емого элемента: "; cin >> index;
	cout << "¬вести добав€емое значение: "; cin >> value;
	list.push_back(value);
	list.insert(index, value);
	list.print();
	ForwardList list2;
	cout << "¬вести размер списка: "; cin >> n;
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
	//range-based for (ƒиапазонный фор, фор дл€ контейнера, дл€ структуры данных)
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
	ForwardList<std::string>stih = { "’орошо", "живЄт", "на", "свете", "¬инни-ѕух" };
	for (std::string i : stih)cout << i << tab; cout << endl;

#endif // HARDCORE
}
