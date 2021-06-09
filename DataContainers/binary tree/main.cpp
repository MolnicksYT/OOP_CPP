#include<iostream>
using namespace std;
#define tab "\t"
#define delimetr "***********************"
#define DEBUG
class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
		{
			this->Data = Data;
			this->pLeft = pLeft;
			this->pRight = pRight;
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
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
	}*Root;//указатель на корневой элемент
public:
	const Element* getRoot()const
	{
		return Root;
	}
	Element* getRoot()
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
#ifdef DEBUG
		cout << "TConstructor:\t" << this << endl;
#endif // DEBUG

	}
	Tree(const initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin();it != il.end();it++)
		{
			insert(*it);
		}
	}
	Tree(const Tree& other) :Tree()
	{
		copy(other.Root);
		cout << "CopyConstructor:" << this << endl;
	}
	Tree& operator=(const Tree& other)
	{
		if (this == &other)return *this;
		clear();
		copy(other.Root);
		cout << "CopyAssignment: \t" << this << endl;
		return *this;
	}
	~Tree()
	{
		clear(Root);
#ifdef DEBUG
		cout << "TDestructor:\t" << this << endl;
#endif // DEBUG
		
	}
	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	void print()
	{
		print(Root);
		cout << endl;
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()
	{
		return minValue(Root);
	}
	int maxValue()
	{
		return maxValue(Root);
	}
	int size()
	{
		return size(Root);
	}
	int sum()
	{
		return sum(Root);
	}
	double avg()
	{
		return avg(Root);
	}
	void clear()
	{
		return clear(Root);
	}
	private:
		void copy(Element* Root)
		{
			if (Root == nullptr)return;
			insert(Root->Data);
			copy(Root->pLeft);
			copy(Root->pRight);
		}
	void insert(int Data, Element* Root)//здесь Element* Root - указатель на ветку (поддерево)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
		}
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)//если текущий элемент (Root) не имеет левого потомка
			{
				Root->pLeft = new Element(Data);//создаЄм его 
			}
			else//в противном случае идЄм дальше
			{
				insert(Data, Root->pLeft);
			}
		}
		if (Data > Root->Data)
		{
			//if (Root->pRight == nullptr)//если текущий элемент (Root) не имеет правого потомка
			//{
			//	Root->pRight = new Element(Data);
			//}
			//else
			//{
			//	insert(Data, Root->pRight);
			//}
			if (Root->pRight)insert(Data, Root->pRight);
			else Root->pRight = new Element(Data);
		}
	}
	void print(Element* Root)
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		print(Root->pRight);
		cout << Root->Data << tab;
	}
	void clear(Element*& Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
			if(Data==Root->Data)
			{
if(Root->is_leaf())
		{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Root->pLeft)
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		return Root->pRight ? maxValue(Root->pRight) :Root->Data;
	}
	int size(Element* Root)
	{
	//кол-во элементов дерева
		/*if (Root == nullptr)return 0;
		else return size(Root->pLeft) + size(Root->pRight) + 1;*/
		return Root == nullptr ? 0 : size(Root->pLeft) + size(Root->pRight) + 1;
	}
	int sum(Element* Root)
	{
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	double avg(Element* Root)
	{
		//return Root == nullptr ? 0 : (sum(Root->pLeft) + sum(Root->pRight) + Root->Data)/size(Root);
		return (double)sum(Root) / size(Root);
	}
};
void main()
{
	setlocale(LC_ALL, "");
	int n;  //кол-во элементов дерева
	cout << "¬вести кол-во элементов дерева: ";cin >> n;
	Tree tree = { 50,25,16,32,64,55,77 };
	tree.print();
	//Tree tree2 = tree; //copyconstructor
	Tree tree2;
	tree2 = tree;
	tree2.print();
	/*for (int i = 0;i < n;i++)
	{
		tree.insert(rand()% 100);
	}*/
	/*tree.insert(50);

	tree.insert(25);
	tree.insert(16);
	tree.insert(32);
	tree.insert(11);
	tree.insert(18);
	tree.insert(30);
	tree.insert(36);

	tree.insert(64);
	tree.insert(55);
	tree.insert(80);
	tree.insert(54);
	tree.insert(58);
	tree.insert(77);
	tree.insert(85);*/

	tree.print();
	cout << endl;
	cout << delimetr << endl;
	cout << "мин. значение в дереве: " << tree.minValue() << endl;
	cout << delimetr << endl;
	cout << "макс. значение в дереве: " << tree.maxValue() << endl;
	cout << delimetr << endl;
	cout << "размер дерева: " << tree.size() << endl;
	cout << delimetr << endl;
	cout << "сумма значений в дереве: " << tree.sum() << endl;
	cout << delimetr << endl;
	cout << "среднее значение в дереве: " << tree.avg() << endl;
	cout << delimetr << endl;
	int value;
	cout << "¬вести удал€емое значение: "; cin >> value;
	tree.erase(value);
	tree.print();
	tree.clear();
	tree.print();

}