#pragma once
#include <iostream>
using namespace std;
#include "myObject.h"
class CharString : public MyObject
{
protected:
	char *stringPtr;//��������� �� ���� ������������ ������
	int stringLenght;// ����� ������
	static int countCopyConstructor;//���������� ������ ������������� �����������

public:
	CharString();
	CharString(const CharString &);
	CharString(const char *strPtr);
	CharString(char);
	~CharString();

	friend ostream& operator<< (ostream &out, const CharString &str);
	//friend istream& operator>> (istream &in, CharString &str);//���������� ���������� ���������� �����-������

	CharString& operator=(const CharString &);//���������� ��������� ���������
	int getCharStringLenght();


};
//���������� ��������� ��������� ������
ostream& operator<< (ostream &out, const CharString &str)
{
	//������������ ���������� ������
	out << "����� ������: ";
	for (int i = 0; i < str.stringLenght; i++)
	{
		cout << str.stringPtr[i];
	}
	out << "\n����� ������: " << str.stringLenght << endl;

	return out;
}

//����������� �� ���������
CharString::CharString()
{
	objectType = CHAR_OBJECT;
	//std::cout << "charString construct\n";
	stringPtr = 0;
	stringLenght = 0;
}

//�����������, ����������� ��-������
CharString::CharString(const char *charStringPtr)
{
	objectType = CHAR_OBJECT;
	stringLenght = strlen(charStringPtr);
	stringPtr = new char[stringLenght + 1];
	for (int i = 0; i < stringLenght; i++)
	{
		stringPtr[i] = charStringPtr[i];
	}
	stringPtr[stringLenght] = '\0';

}
//�����������, ����������� 1 ������ ��-������	
CharString::CharString(char symbol)
{
	objectType = CHAR_OBJECT;
	//std::cout << symbol << " - CharString construct with char\n";
	//����� ������ = 2, ���� ��� ������ � ������ ��� ����� ������ \0
	stringLenght = 2;
	stringPtr = new char[stringLenght];
	stringPtr[0] = symbol;
	stringPtr[1] = '\0';
}

//����������� �����������
CharString::CharString(const CharString &copyStr)
{
	objectType = CHAR_OBJECT;
	stringPtr = copyStr.stringPtr;
	stringLenght = copyStr.stringLenght;
	countCopyConstructor++;
	cout << "���������� ������� ������������ �����������: " << countCopyConstructor << endl;

}


// ��������� ����������� �������� � ���������� ������� ������
CharString& CharString::operator=(const CharString &str)
{
	stringPtr = str.stringPtr;
	stringLenght = str.stringLenght;
	return *this;//����������� ��������� �� ������� ������
	str.~CharString();//�������� ������ �����
}

int CharString::getCharStringLenght()
{
	return stringLenght;
}


//����������
CharString::~CharString()
{
}

