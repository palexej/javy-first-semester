// pr 3 javy template.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
Написать шаблон функции, выполняющей указанные в вариа-тивной части задания действия.
Написать программу тестирования шаблонных функций, созданных на основе этого шаблона, с
аргументами указанных типов. Разработать шаблон класса, опи-сывающий указанный в вариативной
части задания абстрактный тип данных, и написать программу тестирования объектов двух59
шаблонных классов. Выбор тестируемого метода должен осу-ществляться с помощью меню. Это
задание может быть выполнено на трех уровнях сложности:
1) низкий. Указанный АТД можно реализовать любым удобным способом;
2) средний. Заданный АТД реализовать с помощью указанной структуры хранения;
3) повышенный. Создать требуемый АТД с помощью двух структур хранения: векторной и
списковой, реализацию оформить в виде шаблонов классов с единым интерфейсом*/

/*Вариант 13
Типы аргументов unsigned int и float.
1. Перестановка элементов массива в обратном порядке.
2. АТД Дек с ограниченным входом. Структура хранения – связанный список*/



#include "pch.h"
#include <iostream>
using namespace std;


template<typename T>
void reverseOrder(T* arrayToSort, int arraySize)
{

	for (int i = 0; i < arraySize / 2; i++)
	{
		T temp = arrayToSort[i];//временная переменная должна быть того же типа, что и параметры
		arrayToSort[i] = arrayToSort[arraySize - i - 1];
		arrayToSort[arraySize - i - 1] = temp;
	}

}
template<typename T>
void printArray(T &myArray, size_t arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		cout << myArray[i] << " ";
	}
}

template<typename T>
void inputArray(T &myArray, size_t arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		cout << "Элемент с индексом " << i << ": ";
		cin >> myArray[i];
	}

}

void showReverseOrderFunc()
{

	int arraySize;
	char selector;

	cout << "Введите число элементов массива:" << endl;
	cin >> arraySize;
	cout << "Выберите тип элементов массива:" << endl;
	cout << "1. unsigned int" << endl;
	cout << "2. float" << endl;
	cin >> selector;
	switch (selector)
	{
	case '1':
	{
		unsigned int *arrayToReverse = new unsigned int[arraySize];

		inputArray(arrayToReverse, arraySize);

		cout << "Введенный массив:" << endl;
		printArray(arrayToReverse, arraySize);

		reverseOrder(arrayToReverse, arraySize);

		cout << "\nМассив в обратном порядке:" << endl;
		printArray(arrayToReverse, arraySize);

		break;
	}

	case '2':
	{
		float *arrayToReverse = new float[arraySize];

		inputArray(arrayToReverse, arraySize);

		cout << "Введенный массив:" << endl;
		printArray(arrayToReverse, arraySize);

		reverseOrder(arrayToReverse, arraySize);

		cout << "Отсортированный массив:" << endl;
		printArray(arrayToReverse, arraySize);

		break;
	}

	default:
		cout << "Пункта меню не существует, повторите попытку" << endl;
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	
	showReverseOrderFunc();
	
	system("pause");
	return 0;
}
