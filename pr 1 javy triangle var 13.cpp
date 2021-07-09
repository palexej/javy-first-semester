// pr 1 javy triangle var 13.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
Описать класс в соответствии с индивидуальным вариантом задания и реализовать все его
методы. Каждый класс должен содержать, помимо указанных в варианте методов, конструктор с
параметрами, конструктор копирования, деструктор, методы ввода с клавиатуры, установки и
получения значений полей, вывода этих значений на экран. В каждом методе класса, включая
конструкторы и деструктор, предусмотреть отладочную печать сообщения, содержащего имя
метода. Написать программу для тестирования всех методов класса, выбор метода должен
осуществляться с помощью меню.


Класс «Треугольник».Поля: длина одной из сторон и величины прилежащих к ней углов.
Методы : вычисление периметра, медианы, проведенной к заданной стороне, радиуса описанной
	окружности, перегрузка операции сравнения на равенство « == » двух треугольников.*/

//перегрузить операторы для ввода и вывода треугольников
#include "pch.h"
#include <iostream>

using namespace std;

float const PI = 3.1416;

enum chooseSideToMedian//использования перечисления для удобного обозначения сторон
{
	BOTTOM_TRIANGLE_SIDE = '1',
	LEFT_TRIANGLE_SIDE = '2',
	RIGHT_TRIANGLE_SIDE = '3',
};

class Triangle
{

public:
	Triangle(float firstSideLenght, float leftAngle, float rightAngle);//конструктор и деструктор
	~Triangle();
	float countPerimetr();//рассчёт периметра


	float medianToOneSide(char selector);//медиана к одной из сторон
	void setfirstSideLenght(float firstSideLenght);
	float getfirstSideLenght();

	void setLeftAngle(float leftAngle);
	float getLeftAngle();

	void setRightAngle(float rightAngle);
	float getRightAngle();

	float circumscribedRadius();//радиус описаной окружности треугольника

	friend bool operator==(const Triangle &firstTriangle, const Triangle &secondTriangle);//перегрузка операторов сравнения
	friend ostream& operator<< (ostream &out, const Triangle &triangle);
	friend istream& operator>> (istream &in,  Triangle &triangle);//перегрузка операторов потокового ввода-вывода
	
private:
	float firstSideLenghtPrivate, leftAnglePrivate, rightAnglePrivate;
	bool isTriangleExist();//проверка на существование треугольника
	float countMedian(float, float, float);
	float countTriangleSide(float, float, float);//расчёт стороны треугольника


};

bool Triangle::isTriangleExist()
{//если два углы больше нуля и их сумма меньше 180 и также если заданная сторона треугольника больше нуля, то такой треугольник существует
	if (leftAnglePrivate > 0 && rightAnglePrivate > 0 && leftAnglePrivate + rightAnglePrivate < 180 && firstSideLenghtPrivate>0)
	{
		return true;
	}

	else
	{
		return false;
	}
}
ostream& operator<< (ostream &out, const Triangle &triangle)
{
	out << "Длина стороны: " << triangle.firstSideLenghtPrivate << endl;
	out << "Левый угол: " << triangle.leftAnglePrivate<< endl;
	out << "Правый угол:  " << triangle.rightAnglePrivate << endl;
	return out;
}

istream& operator>> (istream &in,  Triangle &triangle)
{
	
	in >> triangle.firstSideLenghtPrivate;
	in >> triangle.leftAnglePrivate;
	in >> triangle.rightAnglePrivate;


	if (!triangle.isTriangleExist())//если треугольник не существует, то значения обнуляются
	{
		triangle.firstSideLenghtPrivate = 0;
		triangle.leftAnglePrivate = 0;
		triangle.rightAnglePrivate = 0;
	}
	return in;

}
//перегрузка оператора сравнения 2-х треугольников по второму признаку равенства тр-ников
bool operator==(const Triangle &firstTriangle, const Triangle &secondTriangle)
{
	return (firstTriangle.firstSideLenghtPrivate == secondTriangle.firstSideLenghtPrivate &&
		firstTriangle.leftAnglePrivate == secondTriangle.leftAnglePrivate &&
		firstTriangle.rightAnglePrivate == secondTriangle.rightAnglePrivate);
}

Triangle::Triangle(float firstSideLenght = 10, float leftAngle = 20, float rightAngle = 30)
{
	firstSideLenghtPrivate = firstSideLenght;//если один из параметров отсутствуют, то используются параметры по умолчанию
	leftAnglePrivate = leftAngle;
	rightAnglePrivate = rightAngle;

	if (!isTriangleExist())//если треугольник не существует, то значения обнуляются
	{
		firstSideLenghtPrivate = 0;
		leftAnglePrivate = 0;
		rightAnglePrivate = 0;
	}

}


float Triangle::countMedian(float a, float b, float c)
{
	return sqrt((2 * a*a + 2 * b*b - c * c) / 4);
}
//деструктур
Triangle::~Triangle()
{
	cout << "Деструктор удалил объект" << endl;
	system("pause");
}

//расчёт медианы одной стороны через селектор, в зависимости от которого выбирается нужная последовательность значений, которые подставляются в формулу
//возвращает -1, если не выбраны пункты 1-3
float Triangle::medianToOneSide(char selector)
{	
	float secondSideLenght, thirdSideLenght, topTriangleAngle, medianValue;

	topTriangleAngle = 180 - leftAnglePrivate - rightAnglePrivate;//сначала находим третий угол

	secondSideLenght = countTriangleSide(firstSideLenghtPrivate, leftAnglePrivate, topTriangleAngle);// потом ищем значение сторон по формуле a=c*(sin a)/(sin y)
	thirdSideLenght = countTriangleSide(firstSideLenghtPrivate, rightAnglePrivate, topTriangleAngle);

	switch (selector)
	{
	case BOTTOM_TRIANGLE_SIDE:
		medianValue = countMedian(secondSideLenght, thirdSideLenght, firstSideLenghtPrivate);//подставляем значения в формулу
		break;

	case LEFT_TRIANGLE_SIDE:
		medianValue = countMedian(firstSideLenghtPrivate, thirdSideLenght, secondSideLenght);//подставляем значения в формулу
		break;
	case RIGHT_TRIANGLE_SIDE:
		medianValue = countMedian(firstSideLenghtPrivate, secondSideLenght, thirdSideLenght);//подставляем значения в формулу
		break;


	default:
		medianValue = -1;
		break;
	}

	return medianValue;


}

//радиус описаной окружности треугольника, возвращает радиус
float Triangle::circumscribedRadius()
{

	float secondSideLenght, thirdSideLenght, topTriangleAngle, perimetr, semiPerimeter, radius;

	topTriangleAngle = 180 - leftAnglePrivate - rightAnglePrivate;//сначала находим третий угол

	secondSideLenght = countTriangleSide(firstSideLenghtPrivate, leftAnglePrivate, topTriangleAngle);// потом ищем значение сторон по формуле a=c*(sin a)/(sin y)
	thirdSideLenght = countTriangleSide(firstSideLenghtPrivate, rightAnglePrivate, topTriangleAngle);

	perimetr = firstSideLenghtPrivate + secondSideLenght + thirdSideLenght;

	semiPerimeter = countPerimetr() / 2;//полупериметр 

	radius = (firstSideLenghtPrivate*secondSideLenght*thirdSideLenght)
		/ (4 * sqrt(semiPerimeter*(semiPerimeter - firstSideLenghtPrivate)*(semiPerimeter - secondSideLenght)*(semiPerimeter - thirdSideLenght)));
	// формула радиуса описанной окружности треугольника


	return radius;

}

//расчёт стороны треугольника через значение градусов
float Triangle::countTriangleSide(float firstSide, float rightOrLeftAngle, float topAngle)
{
	return  firstSide * sin(rightOrLeftAngle*(PI / 180)) / sin(topAngle*(PI / 180));
}

//расчёт периметра через нахождение трёх сторон
float Triangle::countPerimetr()
{
	float secondSideLenght, thirdSideLenght, topTriangleAngle;

	topTriangleAngle = 180 - leftAnglePrivate - rightAnglePrivate;//сначала находим третий угол

	secondSideLenght = countTriangleSide(firstSideLenghtPrivate, leftAnglePrivate, topTriangleAngle);// потом ищем значение сторон по формуле a=c*(sin a)/(sin y)
	thirdSideLenght = countTriangleSide(firstSideLenghtPrivate, rightAnglePrivate, topTriangleAngle);

	return firstSideLenghtPrivate + secondSideLenght + thirdSideLenght;


}

//сеттер с возможностью обнуления значения, если треугольник не существует
void Triangle::setfirstSideLenght(float firstSideLenght)
{
	this->firstSideLenghtPrivate = firstSideLenght;
	if (!isTriangleExist())//если треугольник не существует, то  значения обнуляются
	{
		firstSideLenghtPrivate = 0;
	}


}
float Triangle::getfirstSideLenght()
{
	return firstSideLenghtPrivate;
}

//сеттер с возможностью обнуления значения, если треугольник не существует
void Triangle::setLeftAngle(float leftAngle)
{
	this->leftAnglePrivate = leftAngle;
	if (!isTriangleExist())//если треугольник не существует, то  значения обнуляются
	{
		leftAnglePrivate = 0;
	}
}
float Triangle::getLeftAngle()
{
	return leftAnglePrivate;
}

//сеттер с возможностью обнуления значения, если треугольник не существует
void Triangle::setRightAngle(float rightAngle)
{
	this->rightAnglePrivate = rightAngle;
	if (!isTriangleExist())//если треугольник не существует, то  значения обнуляются
	{
		rightAnglePrivate = 0;
	}
}
float Triangle::getRightAngle()
{
	return rightAnglePrivate;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	Triangle myTriangle;//конструктор по-умолчанию
	Triangle secondTriangle(45.1, 90);//конструктор с 2 параметрами из 3 доступных
	Triangle copyTriangle(secondTriangle);//конструктор копирования

	char selector;
	do {
		system("CLS");

		cout << "Вызван конструктор по умолчанию myTriangle" << endl;
		cout << myTriangle;//вывод полей треугольника через оператор потокового вывода

		cout << "\nВызван конструктор копирования copyTriangle" << endl;
		cout << copyTriangle;

		cout << "\nВызван конструктор с параметрами secondTriangle" << endl;
		cout << secondTriangle;

		cout << "\nМеню" << endl;

		cout << "1. Установка значения поля myTriangle" << endl;
		cout << "2. Получение значения поля myTriangle" << endl;
		cout << "3. Периметр треугольника myTriangle" << endl;
		cout << "4. Медиана к одной из сторон треугольника myTriangle" << endl;
		cout << "5. Радиус описанной окружности myTriangle" << endl;
		cout << "6. Сравнение двух треугольников myTriangle и на равенство" << endl;
		cout << "q. Выход" << endl;

		cin >> selector;

		switch (selector)
		{

		case '1':
			//float inputfirstSideLenght, inputLeftAngle, inputRightAngle;
			cout << "Введите значения сторон для объекта myTriangle: длина стороны, левый и правый углы:" << endl;
			cin >> myTriangle;
			
			system("pause");
			break;
		case '2':
			cout << "Получение значений полей myTriangle" << endl;//вывод полей треугольника через геттеры
			cout << "Длина стороны: " << myTriangle.getfirstSideLenght() << endl;
			cout << "Левый угол: " << myTriangle.getLeftAngle() << endl;
			cout << "Правый угол:  " << myTriangle.getRightAngle() << endl;
			system("pause");
			break;

		case '3':

			cout << "Периметр треугольника для объекта myTriagle: " << myTriangle.countPerimetr() << endl;
			system("pause");
			break;


		case '4':
			char selector;
			float medianResult;
		
			cout << "Выберите, к какой стороне провести медиану:" << endl;
			cout << "1. Нижняя сторона" << endl;
			cout << "2. Левая сторона" << endl;
			cout << "3. Правая сторона" << endl;

			cin >> selector;

			medianResult = myTriangle.medianToOneSide(selector);
			if (medianResult>0)
			{
				cout << "Медиана к выбранной сторон составляет: " << medianResult << endl;
			}
			else
			{
				cout << "Неверно выбран пункт меню, повторите попытку" << endl;
			}

			system("pause");
			break;
		
		case '5':

			cout << "Радиус описанной окружности для объекта myTriangle: " << myTriangle.circumscribedRadius() << endl;

			system("pause");
			break;

		case '6':
			if (myTriangle == secondTriangle)
			{
				cout << "Треугольники myTriangle и secondTriangle равны" << endl;
			}
			else
			{
				cout << "Треугольники myTriangle и secondTriangle не равны" << endl;
			}
			system("pause");
			break;
		case 'q':
			return 0;
			break;
		default:
			cout << "Пункт меню не выбран. Повторите попытку." << endl;
			system("pause");
			break;
		}
	} while (true);


}
