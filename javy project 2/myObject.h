#pragma once
enum ObjectType
{
	CHAR_OBJECT = 1,
	ID_OBJECT,
	HEX_OBJECT
};
class MyObject//объектный класс для определения, к какому из трёх классов принадлежит указатель
{
public:
	MyObject();
	~MyObject();
	int getType();

protected:
	int objectType;//тип объекта
};


MyObject::MyObject()
{
}

MyObject::~MyObject()
{
}

 int MyObject::getType()
{
	return objectType;
}
