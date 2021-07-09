�������� ��� ��������� �������� ������ ��������������� ��������. � ������ ���������
������ ������� �� ���������, ��������������� ���������� ������ ���������: ������ � ��
��������� � ������� ���������, ������� � �� ���������, �������� � ����������, �� ��
���������� ����� ������� �������, ��-����� � �� ������������ ���������. ������� �� ����
��������� � ��������� ���� ���������� ���, ����� ������ ������� ���� �����. ����������
��������� ������� �����, ����� ����������� �����-�� ������� ������������ ������� ������.
#include <SDL.h>

#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 640;//����������� ������� ����
const int SCREEN_HEIGHT = 480;

double recountCoordinateX(double);
double recountCoordinateY(double);
double countGraphicFunc(double);
void buildGraphic(double, double, double);

bool init();
void freeMemory();

static SDL_Window* myWindow = NULL;//������� ����

static SDL_Renderer* myRenderer = NULL;


int main(int argc, char* args[])
{
	//����� ������� � ������ ������� � ����������
	double leftBorder, rightBorder;
	setlocale(LC_ALL, "rus");
	cout << "������� ����� � ������ �������" << endl;
	cin >> leftBorder >> rightBorder;

	if (!init())
	{
		printf("������ �������������\n");
	}
	else
	{

		bool quit = false;

		SDL_Event e;

		double myZoom = 1;
		buildGraphic(leftBorder, rightBorder, myZoom);//������ ������ �� ���������
		while (!quit)
		{

			//������� ���������� � �������
			while (SDL_PollEvent(&e) != 0)
			{

				//���� �� ����� �������� ��������
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_ESCAPE://���� ������ �� ������, �� �������
						quit = true;
						break;

					case SDLK_UP:// ��� ������� �� ��������� ����� ����������� �������������
						myZoom += 1;
						buildGraphic(leftBorder, rightBorder, myZoom);
						break;
					case SDLK_DOWN:// ��� ������� �� ��������� ���� ����������� �����������
						if (myZoom < 1)//��������, ����� ������ �� ������������� ����������� � ������ �������
						{
							break;
						}
						myZoom -= 1;
						buildGraphic(leftBorder, rightBorder, myZoom);
						break;

					default:
						break;
					}
				}
			}

		}

	}

	freeMemory();//�������� ��������

	return 0;
}

void buildGraphic(double  leftBorder, double rightBorder, double zoomCoef)
{
	double dx = 0.0001;//���������� ������� �������

	double squareSide = 2;//������� ��������
	//Clear screen
	SDL_SetRenderDrawColor(myRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(myRenderer);


	SDL_SetRenderDrawColor(myRenderer, 255, 0x00, 255, 0xFF);//������ ��� ���������
	SDL_RenderDrawLine(myRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	SDL_RenderDrawLine(myRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(myRenderer, 0x00, 0x00, 0x00, 0xFF);

	while (leftBorder < rightBorder)//���� �� ����� �� ������ �������
	{
		double x = leftBorder;
		double y = countGraphicFunc(x);

		if (y != INFINITY)//�������� ������� ����� ����� -inf, ���� �������� ������ ����� ����� ����, ������� ���� ������ �� ����������
		{
			double rectangleCoordX = recountCoordinateX(x*zoomCoef - squareSide / 2);//������������� ������������ ���� ��������� 
			double rectangleCoordY = recountCoordinateY(y*zoomCoef - squareSide / 2);
			SDL_Rect rect = { rectangleCoordX,rectangleCoordY,squareSide, squareSide };//������ ��������� ��������� �������, ����� ���� ����� �����
			SDL_SetRenderDrawColor(myRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(myRenderer, &rect);
		}

		leftBorder += dx;//��������� �������� ��� ������� �������
	}

	//��������� �����
	SDL_RenderPresent(myRenderer);
}



double recountCoordinateX(double coordX)// �������� ���������
{
	return coordX + SCREEN_WIDTH / 2;
}

double recountCoordinateY(double coordY)// �������� ���������
{
	return coordY + SCREEN_HEIGHT / 2;
}

double countGraphicFunc(double x)//������� �������� y ��� �������
{
	return 3 * sin(x / 4) - 2 / (sin(2 * x));

	//return (x*x-3)/(x+2);
}

bool init()
{
	
	bool isInitSuccess = true;// ���� ����, ��� �� ��������

	//������������� SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "���������� ���������������� SDL. ������: " << SDL_GetError() << endl;
		isInitSuccess = false;
	}
	else
	{
		//�������� ���� �� ������ ������ � ��������� ������������ ������������
		myWindow = SDL_CreateWindow("I508B Petrov A.V SDL 5 Graphic Var 13", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (myWindow == NULL)
		{
			cout << "���� �� ����� ���� �������. ������: " << SDL_GetError() << endl;
			isInitSuccess = false;
		}
		else
		{
			//�������� ��������� ����
			myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
			if (myRenderer == NULL)
			{
				cout << "���������� ������� ��������. ������: " << SDL_GetError() << endl;
				isInitSuccess = false;
			}
			else
			{
				//������������� ���� ���������
				SDL_SetRenderDrawColor(myRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}

	return isInitSuccess;
}

void freeMemory()//�������� ����, ���������� � ����� �� ���������
{

	SDL_DestroyRenderer(myRenderer);
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;
	myRenderer = NULL;

	SDL_Quit();
}
