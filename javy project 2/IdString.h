#pragma once

#include "CharString.h"
class IdString : public CharString
{
private:
	bool checkIdStringForCorrectSymbol(const char *);
public:
	IdString();
	IdString(const IdString &);
	IdString(const char *);
	IdString(char);
	~IdString();
	void upperCase();
	 IdString operator+(const IdString &);//���������� ��������� ���������
};


//������������ ������������� ������ �������
IdString::IdString() : CharString()
{
	objectType = ID_OBJECT;
}

//�����������, ����������� ��-������
IdString::IdString(const  char *charIdStringPtr) : CharString(charIdStringPtr)
{
	objectType = ID_OBJECT;
	if (!checkIdStringForCorrectSymbol(charIdStringPtr))
	{
		stringLenght = 0;
		stringPtr = 0;
	}
}

//�����������, ����������� 1 ������ ��-������	
IdString::IdString(char symbolIdString) :CharString(symbolIdString)
{
	objectType = ID_OBJECT;
}

//����������� �����������
IdString::IdString(const IdString &copyIdStr) : CharString(copyIdStr)
{
	objectType = ID_OBJECT;
}

//�������� ������ �� ������������ ��������������
bool IdString::checkIdStringForCorrectSymbol(const char *stringPtr)
{

	if (stringPtr[0] == '_' || (stringPtr[0] >= 'a' && stringPtr[0] <= 'z'))//������ ������ �������������� ������ �������� �� "_" ��� �������� �����
	{
		for (int i = 1; i < stringLenght; i++)
		{
			if (!(stringPtr[i] >= 'A' && (stringPtr[i] <= 'Z' || stringPtr[i] >= 'a') && stringPtr[i] <= 'z' && stringPtr[0] == 95 && (
				stringPtr[i] >= '0' && stringPtr[i] <= '9')))//��������� ����� - ��������� � �������� ����� "_", �����
			{
				break;
			}
		}
		return true;
	}

	return false;
}

IdString::~IdString()
{
}
//������� ���� � ������� �������
void IdString::upperCase()
{
	for (int i = 0; i < stringLenght; i++)
	{
		if (stringPtr[i] >= 'a'&&stringPtr[i] <= 'z')//���� ������� ������� �� � �� z
		{
			stringPtr[i] += 'A' - 'a';//������� �� ������� ����� ������� ���������
		}
	}
}

IdString IdString::operator+(const IdString &secondIdStr)//���������� ��������� ���������
{
	IdString resultIdStr;
	int i = 0;
	int summStringLenght = stringLenght + secondIdStr.stringLenght;
	char *bufferString = new char[stringLenght + secondIdStr.stringLenght];
	//�������� ���������, ������� �������� ����� ��� ����� ���� �����

	for (; i < stringLenght; i++)
	{
		bufferString[i] = stringPtr[i];//������������ ������ � �������� ������ ��� ������� �������
	}

	for (int j = 0; i < summStringLenght; i++, j++)
	{
		bufferString[i] = secondIdStr.stringPtr[j];//���������� ��� ������� � ������ �������� �� ������ ������ ������
	}

	resultIdStr.stringLenght = summStringLenght;
	resultIdStr.stringPtr = bufferString;
	

	return resultIdStr;//������������ ������ ������ � ��������� �� ����� ������ ������� ���������� � ������� ����� �������

}