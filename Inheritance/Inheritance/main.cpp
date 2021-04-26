#include<iostream>
#include<string>
using namespace std;
class Box
{
		double width;
		double height;
		double length;
		string material;
public:
	double get_width()const
	{
		return width;
	}
	double get_height()const
	{
		return height;
	}
	double get_length()const
	{
		return length;
	}
	const string& get_material()const
	{
		return this->material;
	}
	//constructors
	Box(double width, double height, double length, const string& material):
	width(width), height(height), length(length), material(material)
	{
		cout << "BoxConstructor:\t\t" << this << endl;
	}
	~Box()
	{
		cout << "BoxDestructor:\t\t" << this << endl;
	}
	//methods
	void info()const
	{
		cout << "dimensions: " << width << "x" << height << "x" << length << endl;
		cout << "Материал: " << material << endl;
	}
};
class GiftBox :public Box
{
	string cover;
public:
const string& get_cover()const
{
	return cover;
}
GiftBox(double width, double height, double length, const string& material, const string& cover) :Box(width, height, length, material)
{
	this->cover = cover;
	cout << "GiftBoxConstructor:\t" << this << endl;
}
~GiftBox()
{
	cout << "GiftBoxDestructor:\t" << this << endl;
}
//methods
void info()const
{
	Box::info();
	cout << "обложка:\t" << cover << endl;
}
};
void main()
{
	setlocale(LC_ALL, "");
	//Box box(2, 5, 8, "картон");
	//box.info();
	GiftBox giftbox(2, 5, 8, "картон", "с котами и мышами");
	giftbox.info();
}