#include<iostream>
using namespace std;
class Animal
{
public:
	virtual ~Animal() {}
	virtual void sound()const = 0; //�����-����������� �����, ��������� �������� ����� ����������
};
class Cat : public Animal
{
	void sound()const
	{
		cout << "���" << endl;
	}
};
class Tiger :public Cat
{
	~Tiger()
	{

	}
	void sound()const
	{
		cout << "�����" << endl;
	}
};
class HomeCat :public Cat
{
	~HomeCat()
	{

	}
	void sound()const
	{
		cout << "���" << endl;
	}
};
class Dog : public Animal
{
	~Dog()
	{

	}
	void sound()const
	{
		cout << "���" << endl;
	}
};
void main()
{
	setlocale(LC_ALL, "");
	//Animal a;
	//Cat tom;
	//Dog job;
	//1) generalization
	Animal* zoo[] =
	{
		new HomeCat,
		new Dog,
		new Tiger,
		new Dog,
		new HomeCat
	};
	//2) specialisation
	for (int i = 0;i < sizeof(zoo) / sizeof(Animal*);i++)
	{
		zoo[i]->sound();
	}
}