// pr 2 javy var 13 nasledovanie.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*Описать три класса: базовый класс «Строка» и производные от него класс «Строкаидентификатор» и класс, заданный индивидуальным вариантом. Обязательные для всех классов
методы: конструктор без параметров, конструктор, принимающий в качестве параметра Систроку, конструктор копирования, деструктор, перегрузка операции присваивания «=». Во всех
методах всех классов предусмотреть печать сообщения, содержащего имя метода. Для конструкторов копирования каждого класса дополнительно предусмотреть диагностическую печать количества его вызовов, рекомендуется использовать статические члены класса.

Поля класса «Строка»: указатель на блок динамически выделенной памяти для размещения
символов строки, длина строки в байтах. Обязательные методы, помимо вышеуказанных: конструктор, принимающий в качестве параметра символ (char), функция получения длины строки.
Строки класса «Строка-идентификатор» строятся по правилам записи идентификаторов в Си,
и могут включать в себя только те символы, которые могут входить в состав Си-идентификаторов.
Если исходные данные противоречат правилам записи идентификатора, то создается пустая
«Строка-идентификатор».
Помимо обязательных компонентов классов, указанных в общей постановке задачи и в вариативной его части, при необходимости можно добавить дополнительные поля и методы.
Написать тестовую программу, которая должна:
? динамически выделить память под массив указателей на базовый класс (4-6 шт.);
? в режиме диалога заполнить этот массив указателями на производные классы, при этом экземпляры производных классов должны создаваться динамически с заданием начальных значений;
? для созданных экземпляров производных классов выполнить проверку всех разработанных
методов с выводом исходных данных и результатов на дисплей.
Режим диалога должен обеспечиваться с помощью иерархического меню. Основные пункты:
1. «Инициализация». Подпункты:
1.1. «Число элементов». Задает число элементов в массиве указателей на базовый класс. После ввода числа элементов пользоваться этим пунктом меню запрещается.
1.2. «Начальное значение». С помощью этого пункта меню можно задать номер элемента,
его тип и начальное значение. Задавать начальные значения и работать с другими пунктами меню
запрещается до тех пор, пока не будет задано число элементов. Допускается задать новое начальное значение несколько раз.
2. «Тестирование». Подпункты:
2.1. «Строка».
2.2. «Строка-идентификатор».
2.3. Класс, соответствующий варианту задания.
2.4. «Задать операнды».
После выбора одного из этих пунктов меню предлагается выбрать один из методов из списка
всех обязательных методов (кроме конструкторов и деструкторов), связанных с выбранным подпунктом.
3. Выход



Дополнительные методы для класса «Строка-идентификатор»: перевод всех символов строки
(кроме цифр) в верхний регистр, переопределение операции сложения «+» для конкатенации
строк.
Производный от «Строки» класс «Шестнадцатеричная строка».
Строки данного класса могут содержать только символы шестнадцатеричных цифр (как в
верхнем, так и в нижнем регистре) и символы «-» и «+», задающие знак числа, которые могут находиться только в первой позиции числа, при отсутствии знака число считается положительным.
Если в составе инициализирующей строки будут встречены любые символы, отличные от допустимых, «Шестнадцатеричная строка» принимает нулевое значение. Содержимое данных строк
рассматривается как шестнадцатеричное число.
Обязательные методы: определение, можно ли представить данное число в формате int, перегрузка операции сложения «+» двух шестнадцатеричных чисел.


*/


#include <iostream>

//подключение файлов с пользовательскими классами и методами
#include "IdString.h"
#include "HexString.h"
#include "CharString.h"
using namespace std;

enum Menu
{
	PREVIOUS_OBJECT = '1',
	NEXT_OBJECT = '2',
	TEST_CURRENT_OBJECT = '3',
	EXIT = 'q'

};
enum ObjectClass
{
	CHAR_STRING = '1',
	ID_STRING,
	HEX_STRING,
};

int CharString::countCopyConstructor = 0;//определение статического счётчика
int main()
{
	setlocale(LC_ALL, "Russian");

	char menuSelector, classObjectSelector, inputStringToClass[255], classMethodSelector;
	int countOfArrayPointers = 0, countOfObject = 0, currentObjectNumber = 0;
	CharString** charStringPtrArray = nullptr;
	CharString tempCharStr;


	while (countOfArrayPointers <= 0)
	{
		cout << "Введите число указателей на класс CharString" << endl;
		cin >> countOfArrayPointers;

	}
	charStringPtrArray = new CharString*[countOfArrayPointers];//динамическое создание массива указателей


	while (countOfObject < countOfArrayPointers)//вводим все значения в массив
	{
		cout << "Выберите создаваемый объекта класса из списка: " << endl;
		cout << "1. CharString" << endl;
		cout << "2. IdString" << endl;
		cout << "3. HexString" << endl;
		cin >> classObjectSelector;

		cout << "Введите значение строки:" << endl;
		cin >> inputStringToClass;
		switch (classObjectSelector)//в зависимости от пункта меню  создаём новый объект класса
		{
		case '1':
		{
			charStringPtrArray[countOfObject] = new CharString(inputStringToClass);//динамическое создание объектов класса
			break;
		}
		case '2':
		{
			charStringPtrArray[countOfObject] = new IdString(inputStringToClass);
			break;
		}
		case '3':
		{
			charStringPtrArray[countOfObject] = new HexString(inputStringToClass);
			break;
		}
		default:
			cout << "Введенный объект класса отсутствует в списке. Повторите попытку" << endl;
			break;

		}
		countOfObject++;
	}
	do
	{
		system("cls");

		cout << "Число элементов в массиве указателей на базовый класс:" << countOfArrayPointers << endl;
		cout << "Текущий указатель на объект класса: " << currentObjectNumber << endl;
		cout << "Выберите пункт меню из перечисленных:" << endl;
		cout << "1. Перейти к предыдущему указателю <-" << endl;
		cout << "2. Перейти к следующему указателю ->" << endl;
		cout << "3. Тестирование текущего объекта класса" << endl;
		cout << "q. Выход" << endl;
		cin >> menuSelector;
		switch (menuSelector)
		{
		case PREVIOUS_OBJECT:
		{
			currentObjectNumber--;
			if (currentObjectNumber < 0)
			{
				currentObjectNumber = countOfArrayPointers - 1;//если мы выходим за рамки массива, присваиваем последнее значение, дабы не выйти за рамки массива
			}

			break;
		}
		case NEXT_OBJECT: // если мы выходим за рамки массива, присваиваем 0, дабы не выйти за рамки массива.

		{
			currentObjectNumber++;
			if (currentObjectNumber >= countOfArrayPointers)
			{
				currentObjectNumber = 0;
			}
			break;
		}
		case TEST_CURRENT_OBJECT:
			system("cls");
			switch (charStringPtrArray[currentObjectNumber]->getType())//определяем тип объекта и демонстрируем методы класса 
			{
			case 1:
			{
				cout << "Демонстрация методов класса CharString:" << endl;
				CharString* charStr = charStringPtrArray[currentObjectNumber];
				cout << *charStr << endl;
				do
				{
					cout << "1. Задать новое значение для CharString " << endl;
					cout << "q. Выйти" << endl;

					cin >> classMethodSelector;
					switch (classMethodSelector)
					{
					case '1':
						cout << "Введите новое значение строки:" << endl;
						cin >> inputStringToClass;
						*charStr = inputStringToClass;
						break;
					case 'q':
						break;
					default:
						cout << "Данный пункт меню отсутствует в списке, повторите попытку" << endl;
						break;
					}
				} while (classMethodSelector != 'q');

				break;
			}
			case 2:
			{
				do
				{
					system("cls");
					cout << "Демонстрация методов класса IDString" << endl;
					IdString *idString = static_cast<IdString*>(charStringPtrArray[currentObjectNumber]);//приводим указатель на базовый класс к классу IdString
					cout << *idString << endl;
					cout << "1. Задать новое значение для IDString " << endl;
					cout << "2. Перевести символы строки в верхний регистр" << endl;
					cout << "3. Соединить текущую строку с заданной с клавиатуры" << endl;
					cout << "q. Выйти" << endl;

					cin >> classMethodSelector;
					switch (classMethodSelector)
					{
					case '1':
					{
						cout << "Введите новое значение строки:" << endl;
						cin >> inputStringToClass;
						*idString = inputStringToClass;
						break;
					}
					case '2':
					{
						idString->upperCase();
						break;
					}
					case '3':
					{
						cout << "Введите строку для конкатинации с заданной" << endl;
						cin >> inputStringToClass;
						IdString idTemp(inputStringToClass);
						*idString = *idString + idTemp;
						break;
					}
					case 'q':
						break;
					default:
						cout << "Данный пункт меню отсутствует в списке, повторите попытку" << endl;
						break;
					}
				} while (classMethodSelector != 'q');

				break;
			}
			case 3:
			{
				
				do
				{
					system("cls");
					cout << "Демонстрация методов класса HexString" << endl;
					HexString *hexStr = static_cast<HexString*>(charStringPtrArray[currentObjectNumber]);//приводим указатель на базовый класс к классу HexString
					cout << *hexStr << endl;
					cout << "1. Задать новое значение для HexString " << endl;
					cout << "2. Сложить два шестнадцатиричных числа" << endl;
					cout << "q. Выйти" << endl;

					cin >> classMethodSelector;
					switch (classMethodSelector)
					{
					case '1':
					{
						cout << "Введите новое значение строки:" << endl;
						cin >> inputStringToClass;
						*hexStr = inputStringToClass;
						break;
					}
					
					case '2':
					{
						cout << "Введите строку в шестнадцатиричном формате для сложения с заданной:" << endl;
						cin >> inputStringToClass;
						HexString hexTempString(inputStringToClass);
						HexString hexString(*hexStr);
						*hexStr = hexTempString + hexString;
						break;
					}

					case 'q':
						break;
					default:
						cout << "Данный пункт меню отсутствует в списке, повторите попытку" << endl;
						break;
					}
				} while (classMethodSelector != 'q');

				break;
			}

			default:
				break;
			}
		case EXIT:
			break;
		default:
			cout << "Данный пункт меню отсутствует в списке, повторите попытку" << endl;
			break;
		}
		system("pause");


	} while (menuSelector != 'q');
	//автоматически определять, что перед нами за объект класса

	return 0;
}
