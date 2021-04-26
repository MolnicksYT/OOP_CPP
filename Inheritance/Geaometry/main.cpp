#include<iostream>
using namespace std;
class Shape
{
	string color;
public:
	Shape(const std::string color)
	{
		this->color = color;
	}
	virtual double area()const = 0;
	virtual double perimeter()const = 0;
	virtual void draw()const = 0;
};
class Square :public Shape/////////////////////
{
	double side;
public:
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		if (side > 0)this->side = side;
		else this->side = 1;
	}
	explicit Square(double side, const std::string& color = "white") :Shape(color)
	{
		set_side(side);
	}
	~Square()
	{

	}
	double area()const
	{
		return side * side;
	}
	double perimeter()const
	{
		return side * 4;
	}
	void draw()const
	{
		for (int i = 0;i < side;i++)
		{
			for (int j = 0;j < side;j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}

};
class Rectangle :public Shape
{
	double width;
	double side;
public:
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		if (side > 0)this->side = side;
		else this->side = 1;
	}/////
	double get_width()const
	{
		return width;
	}
	void set_width(double width)
	{
		if (width > 0)this->width = width;
		else this->width = 1;
	}
	explicit Rectangle(double width, double side, const std::string& color = "white") :Shape(color)
	{
		set_side(side);
		set_width(width);
	}
	~Rectangle()
	{

	}
	double area()const
	{
		return side * width;
	}
	double perimeter()const
	{
		return (side+width)*2;
	}
	void draw()const
	{
		for (int i = 0;i < side;i++)
		{
			for (int j = 0;j < width;j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
};
void main()
{
	setlocale(LC_ALL, "");
	Square square(5);
	cout << "Площать: " << square.area() << endl;
	cout << "Периметр: " << square.perimeter() << endl;
	square.draw();

	Rectangle rect(6, 5);
	cout << "Площать: " << rect.area() << endl;
	cout << "Периметр: " << rect.perimeter() << endl;
	rect.draw();
}
