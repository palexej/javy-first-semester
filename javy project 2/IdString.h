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
	 IdString operator+(const IdString &);//перегрузка оператора сравнения
};


//наследование конструкторов других классов
IdString::IdString() : CharString()
{
	objectType = ID_OBJECT;
}

//конструктор, принимающий Си-строку
IdString::IdString(const  char *charIdStringPtr) : CharString(charIdStringPtr)
{
	objectType = ID_OBJECT;
	if (!checkIdStringForCorrectSymbol(charIdStringPtr))
	{
		stringLenght = 0;
		stringPtr = 0;
	}
}

//конструктор, принимающий 1 символ Си-строки	
IdString::IdString(char symbolIdString) :CharString(symbolIdString)
{
	objectType = ID_OBJECT;
}

//конструктор копирования
IdString::IdString(const IdString &copyIdStr) : CharString(copyIdStr)
{
	objectType = ID_OBJECT;
}

//проверка строки на соответствие идентификатору
bool IdString::checkIdStringForCorrectSymbol(const char *stringPtr)
{

	if (stringPtr[0] == '_' || (stringPtr[0] >= 'a' && stringPtr[0] <= 'z'))//первый символ идентификатора должен состоять из "_" или строчкой буквы
	{
		for (int i = 1; i < stringLenght; i++)
		{
			if (!(stringPtr[i] >= 'A' && (stringPtr[i] <= 'Z' || stringPtr[i] >= 'a') && stringPtr[i] <= 'z' && stringPtr[0] == 95 && (
				stringPtr[i] >= '0' && stringPtr[i] <= '9')))//остальные буквы - заглавные и строчные буквы "_", цифры
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
//перевод букв в верхний регистр
void IdString::upperCase()
{
	for (int i = 0; i < stringLenght; i++)
	{
		if (stringPtr[i] >= 'a'&&stringPtr[i] <= 'z')//если находим символы от а до z
		{
			stringPtr[i] += 'A' - 'a';//смещаем на разницу между первыми символами
		}
	}
}

IdString IdString::operator+(const IdString &secondIdStr)//перегрузка оператора сравнения
{
	IdString resultIdStr;
	int i = 0;
	int summStringLenght = stringLenght + secondIdStr.stringLenght;
	char *bufferString = new char[stringLenght + secondIdStr.stringLenght];
	//создание указателя, который занимает место как сумма двух строк

	for (; i < stringLenght; i++)
	{
		bufferString[i] = stringPtr[i];//посимвольная запись в буферную строку для первого объекта
	}

	for (int j = 0; i < summStringLenght; i++, j++)
	{
		bufferString[i] = secondIdStr.stringPtr[j];//аналогично для второго с учётом смещения на длинну первой строки
	}

	resultIdStr.stringLenght = summStringLenght;
	resultIdStr.stringPtr = bufferString;
	

	return resultIdStr;//присваивание длинны строки и указатель на новую строку объекту результата и возврат этого объекта

}