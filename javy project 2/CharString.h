#pragma once
#include <iostream>
using namespace std;
#include "myObject.h"
class CharString : public MyObject
{
protected:
	char *stringPtr;//указатель на блок динамической памяти
	int stringLenght;// длина строки
	static int countCopyConstructor;//количество вызово конструкторов копирования

public:
	CharString();
	CharString(const CharString &);
	CharString(const char *strPtr);
	CharString(char);
	~CharString();

	friend ostream& operator<< (ostream &out, const CharString &str);
	//friend istream& operator>> (istream &in, CharString &str);//перегрузка операторов потокового ввода-вывода

	CharString& operator=(const CharString &);//перегрузка оператора сравнения
	int getCharStringLenght();


};
//перегрузка оператора поточного вывода
ostream& operator<< (ostream &out, const CharString &str)
{
	//посимвольное считывание строки
	out << "Вывод строки: ";
	for (int i = 0; i < str.stringLenght; i++)
	{
		cout << str.stringPtr[i];
	}
	out << "\nДлина строки: " << str.stringLenght << endl;

	return out;
}

//конструктор по умолчанию
CharString::CharString()
{
	objectType = CHAR_OBJECT;
	//std::cout << "charString construct\n";
	stringPtr = 0;
	stringLenght = 0;
}

//конструктор, принимающий Си-строку
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
//конструктор, принимающий 1 символ Си-строки	
CharString::CharString(char symbol)
{
	objectType = CHAR_OBJECT;
	//std::cout << symbol << " - CharString construct with char\n";
	//длина строки = 2, один под символ и вторая под конец строки \0
	stringLenght = 2;
	stringPtr = new char[stringLenght];
	stringPtr[0] = symbol;
	stringPtr[1] = '\0';
}

//конструктор копирования
CharString::CharString(const CharString &copyStr)
{
	objectType = CHAR_OBJECT;
	stringPtr = copyStr.stringPtr;
	stringLenght = copyStr.stringLenght;
	countCopyConstructor++;
	cout << "Количество вызовов конструктора копирования: " << countCopyConstructor << endl;

}


// Выполняем копирование значений и возвращаем текущий объект
CharString& CharString::operator=(const CharString &str)
{
	stringPtr = str.stringPtr;
	stringLenght = str.stringLenght;
	return *this;//возвращение указателя на текущий объект
	str.~CharString();//удаление строки ввода
}

int CharString::getCharStringLenght()
{
	return stringLenght;
}


//деструктор
CharString::~CharString()
{
}

