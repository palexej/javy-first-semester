#pragma once
enum ObjectType
{
	CHAR_OBJECT = 1,
	ID_OBJECT,
	HEX_OBJECT
};
class MyObject//��������� ����� ��� �����������, � ������ �� ��� ������� ����������� ���������
{
public:
	MyObject();
	~MyObject();
	int getType();

protected:
	int objectType;//��� �������
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
