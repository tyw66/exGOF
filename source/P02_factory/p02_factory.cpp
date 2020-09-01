/******************************
 * 简单工厂模式
 ******************************/

#include <iostream>
using namespace std;

enum ShapeType
{
	CIRCLE,
	SQUARE,
	RECTANGLE
};

class Shape//产品抽象基类
{
public:
	virtual void draw() = 0;
};

class Circle : public Shape  //圆形类
{
public:
	void draw(){ cout<<"draw Circle"<<endl;}
};

class Square : public Shape //正方形类
{
public:
	void draw(){ cout<<"draw Square"<<endl;}
};

class Rectangle : public Shape //正方形类
{
public:
	void draw(){ cout<<"draw Rectangle"<<endl;}
};

class Factory//工厂类
{
public:
	Shape* CreateShape(ShapeType type)
	{
		switch (type)
		{
			case CIRCLE: return new Circle();
			case SQUARE: return new Square();
			case RECTANGLE: return new Rectangle();
			default: return NULL;
		}
	}
};

int main()
{
	Factory shapeFactory;
	Shape *shapeA=shapeFactory.CreateShape(CIRCLE);
	Shape *shapeB=shapeFactory.CreateShape(SQUARE);
	Shape *shapeC=shapeFactory.CreateShape(RECTANGLE);
	shapeA->draw();
	shapeB->draw();
	shapeC->draw();
	//....
}
