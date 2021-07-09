#pragma once
#include "cmath"
#include "CharString.h"
class HexString : public CharString
{
public:
	HexString();
	~HexString();
	HexString(const HexString &);
	HexString(const char *);
	HexString(char);
	friend HexString operator+(const HexString &, const HexString &);//���������� ��������� ���������
	int HexStrToInteger();
	char IntegerToHexStr(int intToConvert);
private:
	bool checkStringForHex(const char *stringPtr);

};

HexString::HexString()
{
	objectType = HEX_OBJECT;
	
}


//�����������, ����������� ��-������
HexString::HexString(const  char *charHextStringPtr) : CharString(charHextStringPtr)
{
	objectType = HEX_OBJECT;
	if (!checkStringForHex(charHextStringPtr))
	{
		stringLenght = 0;
		stringPtr = 0;
	}
}

//�����������, ����������� 1 ������ ��-������	
HexString::HexString(char symbolHexString) :CharString(symbolHexString)
{
	objectType = HEX_OBJECT;
}


//����������� �����������
HexString::HexString(const HexString &copyIdStr) : CharString(copyIdStr)
{
	objectType = HEX_OBJECT;
}
HexString::~HexString()
{
}

//�������� ������ �� ������������ hex-�������
bool HexString::checkStringForHex(const char *stringPtr)
{

	if (stringPtr[0] == '+' || stringPtr[0] == '-')//������ ������ hex ������ �������� �� "+" ��� "-" ��� " "- ���� �� ���������
	{
		for (int i = 1; i < stringLenght; i++)
		{
			if (!(stringPtr[i] >= '0' &&stringPtr[i] <= '9') || (stringPtr[i] >= 'A' &&stringPtr[i] <= 'F') ||
				(stringPtr[i] >= 'a' &&stringPtr[i] <= 'f'))//����� ��� ����� �� � �� F � ������� � ������ ��������
			{
				return false;
			}

		}
		return true;
	}
	return false;
	
}

int HexString::HexStrToInteger()
{
	int convertationIntResult = 0;

	for (int i = 1; i < stringLenght; i++)
	{
		if (stringPtr[i] >= '0' && stringPtr[i] <= '9')
		{
			stringPtr[i] -= 48;
			convertationIntResult += stringPtr[i] * pow(16, stringLenght - i);
		}
		else if (stringPtr[i] >= 'A' && stringPtr[i] <= 'F')
		{
			stringPtr[i] -= 55;//�������� �� �������� ������� �� ���� ���� ������������� �������� 55 ��� ��������� �������� �...F � ���� �����
			convertationIntResult += stringPtr[i] * pow(16, stringLenght - i);
		}
		else if (stringPtr[i] >= '�' && stringPtr[i] <= 'f')
		{
			stringPtr[i] -= 87;//���������� ��� ������������� ���� � ������ ��������
			convertationIntResult += stringPtr[i] * pow(16, stringLenght - i);
		}

	}
	convertationIntResult /= 16;//����������� �� ������� �������
	if (stringPtr[0] == '-')//���� � ����� ���� �����
	{
		convertationIntResult = -convertationIntResult;
	}
	return convertationIntResult;
}


//������� �� ���� � ����
char HexString::IntegerToHexStr(int intToConvert)
{
	int thisLetter = 1, tempNumber, bufferForLenght = 1, intForLenght;//� ������ ������ ������� ��� ����

	intForLenght = intToConvert;
	while (abs(intForLenght) > 0)//������� ����� ������� ������ �� ������ ��� ����� �����
	{
		intForLenght /= 16;
		bufferForLenght++;
	}

	stringPtr = new char[bufferForLenght];//�������� ��������� �� ������ ������ �� �������� ���������� ��������, ������������ ����� � �����
	stringLenght = bufferForLenght;

	if (intToConvert < 0)
	{
		stringPtr[0] = '-';
	}
	else
	{
		stringPtr[0] = '+';
	}

	intToConvert = abs(intToConvert);//����� �� ������, ����� ����� ���� ��� �����
	while (intToConvert > 0)
	{
		tempNumber = intToConvert;//����������� ������ �������������� ����� 
		tempNumber %= 16;//� ����� ������� �� ������� �� 16
		/*
		 ���� ������� ����������� �� 10 �� 15( �� ���� ����� �� � �� �), �� ����������� ��� ����� � ��������������� �������
		*/
		if (tempNumber >= 10 && tempNumber <= 15)
		{
			stringPtr[bufferForLenght - thisLetter] = tempNumber + 55;
			//��� ��� �� ����� ����� � �����, �� ��� ������� ���� ���������� � ������ ������ � �������� �������
		}
		else//����� �������� � ������ �� 0 �� 9
		{
			stringPtr[bufferForLenght - thisLetter] = tempNumber + 48;
		}

		intToConvert /= 16;
		thisLetter++;
	}
	return *stringPtr;

}

HexString operator+(const HexString &firstHexStr, const HexString &secondHexStr)
{
	HexString firstTempHexString(firstHexStr), secondTempHexSttring(secondHexStr), resultTempHexStr;//������������� ������������ ����������� ��� ��������� ��������
	int resultInt, tempInt1, tempInt2;

	tempInt1 = firstTempHexString.HexStrToInteger();//��������� ������ � �����
	tempInt2 = secondTempHexSttring.HexStrToInteger();

	resultInt = tempInt1 + tempInt2;//����������, � ����� ��������� �� �������

	resultTempHexStr.IntegerToHexStr(resultInt);

	return resultTempHexStr;//���������� ������ ������ ������ - ���������, ������� ����������� ������� � ������
}