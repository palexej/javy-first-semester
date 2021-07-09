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

template <typename T>
class DequeOnArray
{
public:
	void makeNull();
	bool isEmpty();
	bool isFull();
	T readLeft();
	T readRight();
	T addRight(T x);
	T outLeft();
	T outRight();
	DequeOnArray(int);
	~DequeOnArray()
	{
	}
private:

	T *data;
	int maxlenght, left, right;
};

template <typename T>
class DequeOnList
{

private:
	class Node
	{
	public:
		Node *next;
		Node *prev;
		T data;

		Node(T data)
		{
			this->data = data;
			next = prev = nullptr;
		}
	};

	Node *right;
	Node *left;
public:
	DequeOnList();

	bool isEmpty();

	bool isFull();

	void addRight(T data);

	void addLeft(T data);

	void outRight();

	void outLeft();

	T readFromRight();

	T readFromLeft();

	~DequeOnList()
	{
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	int dequeSize;
	char selector;
	cout << "Введите размер дека:" << endl;
	cin >> dequeSize;

	cout << "Выберите тип данных для дека и реализацию:" << endl;
	cout << "1. На списках, unsigned int" << endl;
	cout << "2. На списках, float" << endl;
	cout << "3. На массивах, unsigned int" << endl;
	cout << "4. На массивах, float" << endl;
	cin >> selector;
	DequeOnArray<unsigned int> myDeque(dequeSize + 1);
	
	float inputFloat;
	unsigned int inputUnsigned;
	switch (selector)
	{

	case '1':
	{
		DequeOnList<unsigned int> listDequeUnsigned;
		cout << "Добавление элементов в дек справа" << endl;
		
		for (int i = 0; i < dequeSize; i++)
		{
			cout << "Добавление элемента с индексом " << i << " :";
			cin >> inputUnsigned;
			listDequeUnsigned.addRight(inputUnsigned);
		}

		cout << "Извлечение из дека справа:" << endl;
		for (int i = 0; i < dequeSize; i++)
		{
			cout << listDequeUnsigned.readFromRight() << " ";
			listDequeUnsigned.outRight();

		}
		break;
	}
	case '2':
	{
		DequeOnList<float> listDequeFloat;
		cout << "Добавление элементов в дек справа" << endl;
		
		for (int i = 0; i < dequeSize; i++)
		{
			cout << "Добавление элемента с индексом " << i << " :";
			cin >> inputFloat;
			listDequeFloat.addRight(inputFloat);
		}

		cout << "Извлечение из дека справа:" << endl;
		for (int i = 0; i < dequeSize; i++)
		{
			cout << listDequeFloat.readFromRight() << " ";
			listDequeFloat.outRight();
		}
		break;
	}
	case '3':
	{
		DequeOnArray<unsigned int> arrayDequeUnsigned(dequeSize+1);
		cout << "Добавление элементов в дек справа" << endl;

		for (int i = 0; i < dequeSize; i++)
		{
			cout << "Добавление элемента с индексом " << i << " :";
			cin >> inputUnsigned;
			arrayDequeUnsigned.addRight(inputUnsigned);
		}

		cout << "Извлечение из дека справа:" << endl;
		for (int i = 0; i < dequeSize; i++)
		{
			cout << arrayDequeUnsigned.outRight() << " ";
		}
		break;
	}
	case '4':
	{
		DequeOnArray<float> arrayDequeFloat(dequeSize+1);
		cout << "Добавление элементов в дек справа" << endl;

		for (int i = 0; i < dequeSize; i++)
		{
			cout << "Добавление элемента с индексом " << i << " :";
			cin >> inputFloat;
			arrayDequeFloat.addRight(inputFloat);
		}

		cout << "Извлечение из дека справа:" << endl;
		for (int i = 0; i < dequeSize; i++)
		{
			cout << arrayDequeFloat.outRight() << " ";
		}
		break;
	}
	default:
		break;
	}



	system("pause");
	return 0;
}
template <typename T>
DequeOnArray<T>::DequeOnArray(int n = 10)
{
	maxlenght = n;
	data = new T[maxlenght];
	left = 0;
	right = maxlenght - 1;
}

template <typename T>
void DequeOnArray<T>::makeNull()
{
	left = 0;
	right = maxlenght - 1;
}
template <typename T>
bool DequeOnArray<T>::isEmpty()
{
	return (right + 1) % maxlenght == left;
}

template <typename T>
bool DequeOnArray<T>::isFull()
{
	return (right + 2) % maxlenght == left;
}

template <typename T>
T DequeOnArray<T>::readLeft()
{
	return data[left];
}

template <typename T>
T DequeOnArray<T>::readRight()
{
	return data[right];
}

template <typename T>
T DequeOnArray<T>::addRight(T x)
{
	if (isFull())
		return 0;
	right = (right + 1) % maxlenght;
	data[right] = x;
	return 1;
}

template <typename T>
T DequeOnArray<T>::outLeft()
{
	T temp = left;
	left = (left + 1) % maxlenght;
	return data[temp];
}

template <typename T>
T DequeOnArray<T>::outRight()
{
	int temp = right;
	right = right ? right - 1 : maxlenght - 1;
	return data[temp];
}

template <typename T>
DequeOnList<T>::DequeOnList()
{
	right = nullptr;
	left = nullptr;
}

template <typename T>
bool DequeOnList<T>::isEmpty()
{
	return right == nullptr && left == nullptr;
}

template <typename T>
bool DequeOnList<T>::isFull()
{
	return false;
}

template <typename T>
void DequeOnList<T>::addRight(T data)
{
	Node *node = new Node(data);
	if (isEmpty())
		right = left = node;
	else
	{
		node->prev = right;
		right->next = node;
		right = node;
	}
}

template <typename T>
void DequeOnList<T>::addLeft(T data)
{
	Node *node = new Node(data);
	if (isEmpty())
		right = left = node;
	else
	{
		node->next = left;
		left->prev = node;
		left = node;
	}
}

template <typename T>
void DequeOnList<T>::outRight()
{
	if (isEmpty())
		cout << "\nДек пуст.\n";
	else
	{
		if (right != left)
		{
			right = right->prev;
			delete right->next;
			right->next = nullptr;
		}
		else
		{
			delete right;
			right = left = nullptr;
		}
	}
}

template <typename T>
void DequeOnList<T>::outLeft()
{
	if (isEmpty())
		cout << "nop" << endl;
	else
	{
		if (left != right)
		{
			left = left->next;
			delete left->prev;
			left->prev = nullptr;
			//return temp;
		}
		else
		{
			delete left;
			right = left = nullptr;

		}
	}

}

template <typename T>
T DequeOnList<T>::readFromRight()
{
	if (!isEmpty())
	{
		return right->data;
	}
	return 0;
}

template <typename T>
T DequeOnList<T>::readFromLeft()
{
	if (!isEmpty())
	{
		return left->data;
	}
	return 0;
}
