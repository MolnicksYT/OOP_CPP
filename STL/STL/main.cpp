#include<iostream>
#include<array>
#include<vector>
using namespace std;
//#define STL_ARRAY
#define tab "\t"
#define delimetr "===================\n"
//#define	STL_VECTOR
//#define STL_VECTOR_INSERT
#define STL_VECTOR_ERASE
//#define STL_VECTOR_SWAP
template<typename T>void vector_properties(const vector<T>& vec);
template<typename T>void print_vector(const vector<T>& vec);
template<typename T>void reverse_print_vector(const vector<T>& vec);
void main()
{
	setlocale(LC_ALL, "");
#ifdef STL_ARRAY
//array - контейнер, хран€щий данные в виде статичного массива
	array<int, 5> arr = { 3,5,8,13,21 };
	for (int i = 0;i < arr.size();i++)
	{
		//cout << arr[i] << endl;
		cout << arr.at(i) << tab;
	}
	cout << endl;
	cout << arr.front() << endl;
	cout << arr.back() << endl;
	cout << *arr.data() << endl;

	arr.fill(123);
	for (int i : arr)
		cout << i << tab;
	cout << endl;
#endif
#ifdef STL_VECTOR
	//vector - контейнер, хран€щий данные в виде динамического массива
	vector<int> vec1 = { 0,1,1,2,3,5,8,13,21,34 };
	vec1.push_back(55);
	//cout << "Size: " << vec1.size() << endl;
	//cout << "Capacity: " << vec1.capacity() << endl;
	//cout << "Max size: " << vec1.max_size() << endl;
	vector_properties(vec1);
	try
	{
		for (int i = 0;i < vec1.capacity();i++)
		{
			//cout << vec1[i] << tab;
			cout << vec1.at(i) << tab;
		}
		cout << endl;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
	vec1.reserve(45);
	//vec1.shrink_to_fit();
	/*cout << "Size: " << vec1.size() << endl;
	cout << "Capacity: " << vec1.capacity() << endl;
	cout << "Max size: " << vec1.max_size() << endl;*/
	vector_properties(vec1);
	for(vector<int>::iterator it = vec1.begin();it!=vec1.end();it++)
	{
		cout << *it << tab;
	}
	cout << endl;
	cout << delimetr;
	vec1.assign({ 1024,2048,3072 });
	print_vector(vec1);
	reverse_print_vector(vec1);
	//vector_properties(vec1);
#endif // STL_VECTOR
#ifdef STL_VECTOR_INSERT
	int index;
	int count;
	int value;
	do
	{
		cout << "¬вести индекс добавл€емого элемента: ";cin >> index;
		if (index > vec1.size())cout << "необходимо значение меньше, иначе программа упадЄт\n";
	} while (index > vec1.size());
	cout << "¬вести кол-во добавл€емых элементов: ";cin >> count;
	cout << "¬вести значение добавл€емого элемента: ";cin >> value;
	vector<int>::iterator position = vec1.begin() + index;
	//vec1.insert(position, count, value);
	/*vec1.insert(vec1.begin()+index,count,value);
	for (int i : vec1)
		cout << i << tab;
	cout << endl;
	vector_properties(vec1);
	vec1.insert(vec1.begin() + 8, vec1.begin() + 2, vec1.begin() + 5);
	for (int i : vec1)cout << i << tab; cout << endl;
	vector_properties(vec1);*/
#endif // STL_VECTOR_INSERT
	/*cout << delimetr;
	vec1.insert(vec1.begin() + 5, { 1024,2048,3072,4096 });
	print_vector(vec1);
	vector_properties(vec1);
	cout << "этот вектор = " << sizeof(vec1) << " байт." << endl;
	cout << delimetr;
	vector<int>vec2;
	cout << "ѕустой вектор = " << sizeof(vec2) << " байт." << endl;*/
#ifdef STL_VECTOR_SWAP
	cout << delimetr;
	vector<int>vec2 = { 3,5,8,13,21 };
	vector<int>vec3 = { 34,55,89 };
	print_vector(vec2);
	print_vector(vec3);
	vec2.swap(vec3);
	print_vector(vec2);
	print_vector(vec3);
#endif // STL_VECTOR_SWAP
	vector<int>vec1 = { 3,5,8,13,21,34,55 };
	print_vector(vec1);
	reverse_print_vector(vec1);

	/*int index;
	cout << "¬вести индекс удал€емого элемента: ";cin >> index;
	vector<int>::iterator position = vec1.begin() + index;*/
	//vec1.erase(position);
	int index_start, index_end;
	cout << "¬вести начальный индекс удал€емого диапазона: ";cin >> index_start;
	cout << "¬вести начальный индекс удал€емого диапазона: ";cin >> index_end;
	vec1.erase(vec1.begin() + index_start, vec1.begin() + index_end);
	print_vector(vec1);
	vector_properties(vec1);

}
template<typename T>void vector_properties(const vector<T>& vec)
{
	cout << "Size: " << vec.size() << endl;
	cout << "Capacity: " << vec.capacity() << endl;
	cout << "Max size: " << vec.max_size() << endl;
}
template<typename T>void print_vector(const vector<T>& vec)
{
	//for (int i : vec)cout << i << tab;cout << endl;
	cout << typeid(vec.begin()).name() << endl;
	for (vector<int>::const_iterator it = vec.begin();it != vec.end();it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}
template<typename T>void reverse_print_vector(const vector<T>& vec)
{
	for (vector<int>::const_reverse_iterator it = vec.rbegin();it != vec.rend();it++)
		cout << *it << tab;
	cout << endl;
}