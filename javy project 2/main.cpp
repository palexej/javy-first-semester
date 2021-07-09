// pr 2 javy var 13 nasledovanie.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
/*������� ��� ������: ������� ����� ������� � ����������� �� ���� ����� �������������������� � �����, �������� �������������� ���������. ������������ ��� ���� �������
������: ����������� ��� ����������, �����������, ����������� � �������� ��������� ��������, ����������� �����������, ����������, ���������� �������� ������������ �=�. �� ����
������� ���� ������� ������������� ������ ���������, ����������� ��� ������. ��� ������������� ����������� ������� ������ ������������� ������������� ��������������� ������ ���������� ��� �������, ������������� ������������ ����������� ����� ������.

���� ������ �������: ��������� �� ���� ����������� ���������� ������ ��� ����������
�������� ������, ����� ������ � ������. ������������ ������, ������ �������������: �����������, ����������� � �������� ��������� ������ (char), ������� ��������� ����� ������.
������ ������ �������-������������� �������� �� �������� ������ ��������������� � ��,
� ����� �������� � ���� ������ �� �������, ������� ����� ������� � ������ ��-���������������.
���� �������� ������ ������������ �������� ������ ��������������, �� ��������� ������
�������-�������������.
������ ������������ ����������� �������, ��������� � ����� ���������� ������ � � ����������� ��� �����, ��� ������������� ����� �������� �������������� ���� � ������.
�������� �������� ���������, ������� ������:
? ����������� �������� ������ ��� ������ ���������� �� ������� ����� (4-6 ��.);
? � ������ ������� ��������� ���� ������ ����������� �� ����������� ������, ��� ���� ���������� ����������� ������� ������ ����������� ����������� � �������� ��������� ��������;
? ��� ��������� ����������� ����������� ������� ��������� �������� ���� �������������
������� � ������� �������� ������ � ����������� �� �������.
����� ������� ������ �������������� � ������� �������������� ����. �������� ������:
1. ���������������. ���������:
1.1. ������ ���������. ������ ����� ��������� � ������� ���������� �� ������� �����. ����� ����� ����� ��������� ������������ ���� ������� ���� �����������.
1.2. ���������� ��������. � ������� ����� ������ ���� ����� ������ ����� ��������,
��� ��� � ��������� ��������. �������� ��������� �������� � �������� � ������� �������� ����
����������� �� ��� ���, ���� �� ����� ������ ����� ���������. ����������� ������ ����� ��������� �������� ��������� ���.
2. �������������. ���������:
2.1. �������.
2.2. �������-�������������.
2.3. �����, ��������������� �������� �������.
2.4. ������� ���������.
����� ������ ������ �� ���� ������� ���� ������������ ������� ���� �� ������� �� ������
���� ������������ ������� (����� ������������� � ������������), ��������� � ��������� ����������.
3. �����



�������������� ������ ��� ������ �������-�������������: ������� ���� �������� ������
(����� ����) � ������� �������, ��������������� �������� �������� �+� ��� ������������
�����.
����������� �� ������� ����� ������������������ ������.
������ ������� ������ ����� ��������� ������ ������� ����������������� ���� (��� �
�������, ��� � � ������ ��������) � ������� �-� � �+�, �������� ���� �����, ������� ����� ���������� ������ � ������ ������� �����, ��� ���������� ����� ����� ��������� �������������.
���� � ������� ���������������� ������ ����� ��������� ����� �������, �������� �� ����������, ������������������ ������ ��������� ������� ��������. ���������� ������ �����
��������������� ��� ����������������� �����.
������������ ������: �����������, ����� �� ����������� ������ ����� � ������� int, ���������� �������� �������� �+� ���� ����������������� �����.


*/


#include <iostream>

//����������� ������ � ����������������� �������� � ��������
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

int CharString::countCopyConstructor = 0;//����������� ������������ ��������
int main()
{
	setlocale(LC_ALL, "Russian");

	char menuSelector, classObjectSelector, inputStringToClass[255], classMethodSelector;
	int countOfArrayPointers = 0, countOfObject = 0, currentObjectNumber = 0;
	CharString** charStringPtrArray = nullptr;
	CharString tempCharStr;


	while (countOfArrayPointers <= 0)
	{
		cout << "������� ����� ���������� �� ����� CharString" << endl;
		cin >> countOfArrayPointers;

	}
	charStringPtrArray = new CharString*[countOfArrayPointers];//������������ �������� ������� ����������


	while (countOfObject < countOfArrayPointers)//������ ��� �������� � ������
	{
		cout << "�������� ����������� ������� ������ �� ������: " << endl;
		cout << "1. CharString" << endl;
		cout << "2. IdString" << endl;
		cout << "3. HexString" << endl;
		cin >> classObjectSelector;

		cout << "������� �������� ������:" << endl;
		cin >> inputStringToClass;
		switch (classObjectSelector)//� ����������� �� ������ ����  ������ ����� ������ ������
		{
		case '1':
		{
			charStringPtrArray[countOfObject] = new CharString(inputStringToClass);//������������ �������� �������� ������
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
			cout << "��������� ������ ������ ����������� � ������. ��������� �������" << endl;
			break;

		}
		countOfObject++;
	}
	do
	{
		system("cls");

		cout << "����� ��������� � ������� ���������� �� ������� �����:" << countOfArrayPointers << endl;
		cout << "������� ��������� �� ������ ������: " << currentObjectNumber << endl;
		cout << "�������� ����� ���� �� �������������:" << endl;
		cout << "1. ������� � ����������� ��������� <-" << endl;
		cout << "2. ������� � ���������� ��������� ->" << endl;
		cout << "3. ������������ �������� ������� ������" << endl;
		cout << "q. �����" << endl;
		cin >> menuSelector;
		switch (menuSelector)
		{
		case PREVIOUS_OBJECT:
		{
			currentObjectNumber--;
			if (currentObjectNumber < 0)
			{
				currentObjectNumber = countOfArrayPointers - 1;//���� �� ������� �� ����� �������, ����������� ��������� ��������, ���� �� ����� �� ����� �������
			}

			break;
		}
		case NEXT_OBJECT: // ���� �� ������� �� ����� �������, ����������� 0, ���� �� ����� �� ����� �������.

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
			switch (charStringPtrArray[currentObjectNumber]->getType())//���������� ��� ������� � ������������� ������ ������ 
			{
			case 1:
			{
				cout << "������������ ������� ������ CharString:" << endl;
				CharString* charStr = charStringPtrArray[currentObjectNumber];
				cout << *charStr << endl;
				do
				{
					cout << "1. ������ ����� �������� ��� CharString " << endl;
					cout << "q. �����" << endl;

					cin >> classMethodSelector;
					switch (classMethodSelector)
					{
					case '1':
						cout << "������� ����� �������� ������:" << endl;
						cin >> inputStringToClass;
						*charStr = inputStringToClass;
						break;
					case 'q':
						break;
					default:
						cout << "������ ����� ���� ����������� � ������, ��������� �������" << endl;
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
					cout << "������������ ������� ������ IDString" << endl;
					IdString *idString = static_cast<IdString*>(charStringPtrArray[currentObjectNumber]);//�������� ��������� �� ������� ����� � ������ IdString
					cout << *idString << endl;
					cout << "1. ������ ����� �������� ��� IDString " << endl;
					cout << "2. ��������� ������� ������ � ������� �������" << endl;
					cout << "3. ��������� ������� ������ � �������� � ����������" << endl;
					cout << "q. �����" << endl;

					cin >> classMethodSelector;
					switch (classMethodSelector)
					{
					case '1':
					{
						cout << "������� ����� �������� ������:" << endl;
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
						cout << "������� ������ ��� ������������ � ��������" << endl;
						cin >> inputStringToClass;
						IdString idTemp(inputStringToClass);
						*idString = *idString + idTemp;
						break;
					}
					case 'q':
						break;
					default:
						cout << "������ ����� ���� ����������� � ������, ��������� �������" << endl;
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
					cout << "������������ ������� ������ HexString" << endl;
					HexString *hexStr = static_cast<HexString*>(charStringPtrArray[currentObjectNumber]);//�������� ��������� �� ������� ����� � ������ HexString
					cout << *hexStr << endl;
					cout << "1. ������ ����� �������� ��� HexString " << endl;
					cout << "2. ������� ��� ����������������� �����" << endl;
					cout << "q. �����" << endl;

					cin >> classMethodSelector;
					switch (classMethodSelector)
					{
					case '1':
					{
						cout << "������� ����� �������� ������:" << endl;
						cin >> inputStringToClass;
						*hexStr = inputStringToClass;
						break;
					}
					
					case '2':
					{
						cout << "������� ������ � ����������������� ������� ��� �������� � ��������:" << endl;
						cin >> inputStringToClass;
						HexString hexTempString(inputStringToClass);
						HexString hexString(*hexStr);
						*hexStr = hexTempString + hexString;
						break;
					}

					case 'q':
						break;
					default:
						cout << "������ ����� ���� ����������� � ������, ��������� �������" << endl;
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
			cout << "������ ����� ���� ����������� � ������, ��������� �������" << endl;
			break;
		}
		system("pause");


	} while (menuSelector != 'q');
	//������������� ����������, ��� ����� ���� �� ������ ������

	return 0;
}
