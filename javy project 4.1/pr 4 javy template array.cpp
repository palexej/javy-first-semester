// pr 4 javy template array.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
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
#include <vector>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	unsigned int arraySize;
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
		vector<unsigned int> arrayToReverse;//создание вектора unsigned int
		unsigned int temp = 0;
		for (int i = 0; i < arraySize; i++)
		{
			cout << "Элемент с индексом " << i << ": ";
			cin >> temp;
			arrayToReverse.push_back(temp);
		}
		cout << "Введенный массив:" << endl;
		for (int i = 0; i < arraySize; i++)
		{
			cout << arrayToReverse[i] << " ";
		}
		cout << endl;

		for (int i = 0; i < arraySize / 2; i++)
		{
			temp = arrayToReverse[i];
			arrayToReverse[i] = arrayToReverse[arraySize - i - 1];
			arrayToReverse[arraySize - i - 1] = temp;

		}

		cout << "Массив в обратном порядке:" << endl;

		for (int i = 0; i < arraySize; i++)
		{
			cout << arrayToReverse[i] << " ";
		}
		break;
	}
	case '2':
	{

		vector<float> arrayToReverse;//создание вектора float
		float temp = 0;
		for (int i = 0; i < arraySize; i++)
		{
			cout << "Элемент с индексом " << i << ": ";
			cin >> temp;
			arrayToReverse.push_back(temp);
		}
		cout << "Введенный массив:" << endl;
		for (int i = 0; i < arraySize; i++)
		{
			cout << arrayToReverse[i] << " ";
		}
		cout << endl;

		for (int i = 0; i < arraySize / 2; i++)
		{
			temp = arrayToReverse[i];
			arrayToReverse[i] = arrayToReverse[arraySize - i - 1];
			arrayToReverse[arraySize - i - 1] = temp;

		}

		cout << "Массив в обратном порядке:" << endl;

		for (int i = 0; i < arraySize; i++)
		{
			cout << arrayToReverse[i] << " ";
		}
		break;
	}
	default:
		cout << "Пункта меню не существует, повторите попытку" << endl;
		break;
	}

	system("pause");

}
