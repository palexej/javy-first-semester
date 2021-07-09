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
	friend HexString operator+(const HexString &, const HexString &);//перегрузка оператора сравнени€
	int HexStrToInteger();
	char IntegerToHexStr(int intToConvert);
private:
	bool checkStringForHex(const char *stringPtr);

};

HexString::HexString()
{
	objectType = HEX_OBJECT;
	
}


//конструктор, принимающий —и-строку
HexString::HexString(const  char *charHextStringPtr) : CharString(charHextStringPtr)
{
	objectType = HEX_OBJECT;
	if (!checkStringForHex(charHextStringPtr))
	{
		stringLenght = 0;
		stringPtr = 0;
	}
}

//конструктор, принимающий 1 символ —и-строки	
HexString::HexString(char symbolHexString) :CharString(symbolHexString)
{
	objectType = HEX_OBJECT;
}


//конструктор копировани€
HexString::HexString(const HexString &copyIdStr) : CharString(copyIdStr)
{
	objectType = HEX_OBJECT;
}
HexString::~HexString()
{
}

//проверка строки на соответствие hex-формату
bool HexString::checkStringForHex(const char *stringPtr)
{

	if (stringPtr[0] == '+' || stringPtr[0] == '-')//первый символ hex должен состо€ть из "+" или "-" или " "- плюс по умолчанию
	{
		for (int i = 1; i < stringLenght; i++)
		{
			if (!(stringPtr[i] >= '0' &&stringPtr[i] <= '9') || (stringPtr[i] >= 'A' &&stringPtr[i] <= 'F') ||
				(stringPtr[i] >= 'a' &&stringPtr[i] <= 'f'))//цифры или буквы от ј до F в верхнем и нижнем регистре
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
			stringPtr[i] -= 55;//¬ычитаем из значени€ символа по коду јски фиксированное значение 55 дл€ получени€ значени€ ј...F в виде числа
			convertationIntResult += stringPtr[i] * pow(16, stringLenght - i);
		}
		else if (stringPtr[i] >= 'а' && stringPtr[i] <= 'f')
		{
			stringPtr[i] -= 87;//аналогично при использовании букв в нижнем регистре
			convertationIntResult += stringPtr[i] * pow(16, stringLenght - i);
		}

	}
	convertationIntResult /= 16;//избавл€емс€ от лишнего разр€да
	if (stringPtr[0] == '-')//если у числа знак минус
	{
		convertationIntResult = -convertationIntResult;
	}
	return convertationIntResult;
}


//перевод из инта в хекс
char HexString::IntegerToHexStr(int intToConvert)
{
	int thisLetter = 1, tempNumber, bufferForLenght = 1, intForLenght;//с учЄтом одного символа под знак

	intForLenght = intToConvert;
	while (abs(intForLenght) > 0)//считаем длину будущей строки по модулю без учета знака
	{
		intForLenght /= 16;
		bufferForLenght++;
	}

	stringPtr = new char[bufferForLenght];//создание указател€ на строку исход€ из размеров количества символов, подсчитанных ранее в цикле
	stringLenght = bufferForLenght;

	if (intToConvert < 0)
	{
		stringPtr[0] = '-';
	}
	else
	{
		stringPtr[0] = '+';
	}

	intToConvert = abs(intToConvert);//берем по модулю, чтобы число было без знака
	while (intToConvert > 0)
	{
		tempNumber = intToConvert;//присваиваем буферу конвертируемое число 
		tempNumber %= 16;//и берем остаток от делени€ на 16
		/*
		 если остаток принадлежит от 10 до 15( то есть буквы от ј до ≈), то преобразуем эти числа в соответствующие лексемы
		*/
		if (tempNumber >= 10 && tempNumber <= 15)
		{
			stringPtr[bufferForLenght - thisLetter] = tempNumber + 55;
			//так как мы берем цифры с конца, то эти символы надо записывать в начало строки в обратном пор€дке
		}
		else//иначе приводит к цифрам от 0 до 9
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
	HexString firstTempHexString(firstHexStr), secondTempHexSttring(secondHexStr), resultTempHexStr;//использование конструктора копировани€ дл€ получени€ значений
	int resultInt, tempInt1, tempInt2;

	tempInt1 = firstTempHexString.HexStrToInteger();//переводим строку в число
	tempInt2 = secondTempHexSttring.HexStrToInteger();

	resultInt = tempInt1 + tempInt2;//складываем, а затем переводим всЄ обратно

	resultTempHexStr.IntegerToHexStr(resultInt);

	return resultTempHexStr;//возвращаем третий объект класса - результат, который переводитс€ обратно в строку
}