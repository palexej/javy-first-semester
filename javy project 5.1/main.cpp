Написать две программы согласно номеру индивидуального варианта. В первой построить
график функции на интервале, соответствующем выбранному уровню сложности: низкий – на
указанном в задании интервале, средний – на интервале, заданном с клавиатуры, но не
включающем точек разрыва функции, вы-сокий – на произвольном интервале. Масштаб по осям
координат и положение осей определить так, чтобы график занимал весь экран. Приращение
аргумента выбрать таким, чтобы непрерывные участ-ки функции отображались плавной кривой.
#include <SDL.h>

#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 640;//константные размеры окна
const int SCREEN_HEIGHT = 480;

double recountCoordinateX(double);
double recountCoordinateY(double);
double countGraphicFunc(double);
void buildGraphic(double, double, double);

bool init();
void freeMemory();

static SDL_Window* myWindow = NULL;//область окна

static SDL_Renderer* myRenderer = NULL;


int main(int argc, char* args[])
{
	//задаём верхнюю и нижнюю границы с клавиатуры
	double leftBorder, rightBorder;
	setlocale(LC_ALL, "rus");
	cout << "Введите левую и правую границу" << endl;
	cin >> leftBorder >> rightBorder;

	if (!init())
	{
		printf("Ошибка инициализации\n");
	}
	else
	{

		bool quit = false;

		SDL_Event e;

		double myZoom = 1;
		buildGraphic(leftBorder, rightBorder, myZoom);//строим график по умолчанию
		while (!quit)
		{

			//события помещаются в очередь
			while (SDL_PollEvent(&e) != 0)
			{

				//пока не вышли нажатием крестика
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_ESCAPE://если нажали на эскейп, то выходим
						quit = true;
						break;

					case SDLK_UP:// при нажатии на стрелочку вверх приближение увеличивается
						myZoom += 1;
						buildGraphic(leftBorder, rightBorder, myZoom);
						break;
					case SDLK_DOWN:// при нажатии на стрелочку вниз приближение уменьшается
						if (myZoom < 1)//проверка, чтобы график не разворачивало симметрично в другую сторону
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

	freeMemory();//удаление объектов

	return 0;
}

void buildGraphic(double  leftBorder, double rightBorder, double zoomCoef)
{
	double dx = 0.0001;//приращение графика функции

	double squareSide = 2;//сторона квадрата
	//Clear screen
	SDL_SetRenderDrawColor(myRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(myRenderer);


	SDL_SetRenderDrawColor(myRenderer, 255, 0x00, 255, 0xFF);//рисуем оси координат
	SDL_RenderDrawLine(myRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	SDL_RenderDrawLine(myRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(myRenderer, 0x00, 0x00, 0x00, 0xFF);

	while (leftBorder < rightBorder)//пока не дошли до правой границы
	{
		double x = leftBorder;
		double y = countGraphicFunc(x);

		if (y != INFINITY)//значение функции будет равно -inf, если значение синуса будет равно нулю, поэтому этот разрыв мы пропускаем
		{
			double rectangleCoordX = recountCoordinateX(x*zoomCoef - squareSide / 2);//центрирование относительно осей координат 
			double rectangleCoordY = recountCoordinateY(y*zoomCoef - squareSide / 2);
			SDL_Rect rect = { rectangleCoordX,rectangleCoordY,squareSide, squareSide };//рисуем квадратик заданного размера, чтобы было лучше видно
			SDL_SetRenderDrawColor(myRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(myRenderer, &rect);
		}

		leftBorder += dx;//приращаем значение для графика функции
	}

	//обновляем экран
	SDL_RenderPresent(myRenderer);
}



double recountCoordinateX(double coordX)// пересчёт координат
{
	return coordX + SCREEN_WIDTH / 2;
}

double recountCoordinateY(double coordY)// пересчёт координат
{
	return coordY + SCREEN_HEIGHT / 2;
}

double countGraphicFunc(double x)//рассчёт значения y для функции
{
	return 3 * sin(x / 4) - 2 / (sin(2 * x));

	//return (x*x-3)/(x+2);
}

bool init()
{
	
	bool isInitSuccess = true;// флаг того, что всё работает

	//инициализация SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Невозможно инициализировать SDL. Ошибка: " << SDL_GetError() << endl;
		isInitSuccess = false;
	}
	else
	{
		//создание окна по центру экрана с заданными константными координатами
		myWindow = SDL_CreateWindow("I508B Petrov A.V SDL 5 Graphic Var 13", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (myWindow == NULL)
		{
			cout << "Окно не может быть создано. Ошибка: " << SDL_GetError() << endl;
			isInitSuccess = false;
		}
		else
		{
			//создание рендерера окна
			myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
			if (myRenderer == NULL)
			{
				cout << "Невозможно создать рендерер. Ошибка: " << SDL_GetError() << endl;
				isInitSuccess = false;
			}
			else
			{
				//устанавливаем цвет рендерера
				SDL_SetRenderDrawColor(myRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}

	return isInitSuccess;
}

void freeMemory()//удаление окон, рендереров и выход из подсистем
{

	SDL_DestroyRenderer(myRenderer);
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;
	myRenderer = NULL;

	SDL_Quit();
}
