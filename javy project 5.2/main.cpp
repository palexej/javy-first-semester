/*Во второй программе смоделировать непрерывное движение заданного объекта, выход из
программы осуществлять при нажатии клавиши «Esc».
Изобразить на экране градусник, который показывает температуру за окном. На градуснике
обозначить деления и их цифровые значения. При нажатии на любую клавишу восходит солнце и
столбик градусника начинает ползти вверх. Когда солнце садится, столбик градусника начинает
ползти вниз*/


#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include "StaticGraphicElement.h"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* myWindow = NULL;

SDL_Renderer* myRenderer = NULL;


bool init();

bool loadMedia();


void close();

StaticGraphicElement myThermometrTexture;
StaticGraphicElement myWindowTexture;
StaticGraphicElement mySunTexture;

using namespace std;

const int SUN_SPRITE_COUNT = 2, THERMO_SPRITE_COUNT = 5;
SDL_Rect thermometrSpriteClisp[THERMO_SPRITE_COUNT];
SDL_Rect sunSpriteClisp[SUN_SPRITE_COUNT];



int main(int argc, char* args[])
{
	if (!init())
	{
		cout << "Ошибка инициализации" << endl;
	}
	else
	{
		if (loadMedia())
		{

			bool quit = false;
			bool startAnimation = false;

			SDL_Event e;
			int frame = 0;
			int counter = 0;
			const int step = 5;
			int redColor = 0, blueColor = 0, greenColor = 0, reverseCounter = 0;
			while (!quit)
			{

				while (SDL_PollEvent(&e) != 0)
				{

					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					else if (e.type == SDL_KEYDOWN)
					{
						if (e.key.keysym.sym == SDLK_ESCAPE)//выход при эскейпе
						{
							quit = true;
						}
						else
						{
							startAnimation = true;
						}


						switch (e.key.keysym.sym)
						{
						case SDLK_ESCAPE://если нажали на эскейп, то выходим
							quit = true;
							break;

						default:
							break;
						}
					}

				}


				SDL_RenderClear(myRenderer);

				if (startAnimation == false)//если нет нажатия клавиши, то рисуем все без солнца
				{
					myThermometrTexture.render(30, 250, NULL);
					SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 0xFF);
					myWindowTexture.render(0, 0, NULL);

				}
				if (startAnimation == true)
				{
					myThermometrTexture.render(30, 250, NULL);
					counter += step;
					if (counter > SCREEN_WIDTH+100)//обнуляем счётчики, если вышли за пределы экрана
					{
						counter = 0;
						reverseCounter = 0;
					}

					SDL_Rect thermoRectangle;//прямоугольник отображения температуры

					if (counter <= SCREEN_WIDTH / 2 + 30)
					{
						
						if (blueColor < 249)//пока не полностью синее небо, то рисуем квадратик заданного размера по координатам
						{
							blueColor += step;
							greenColor += step;
							thermoRectangle = { 58,480,20,-counter / 2 };

						}

					}

					else if (counter < SCREEN_WIDTH + 100)//пока примерно не конец экрана, закрашиваем поерх белым цветом
					{
						if (blueColor > 0)//пока небо не чёрное, отображаем прямоугольник с уменьшением в обратную сторону	
						{
							greenColor -= step;
							blueColor -= step;
							thermoRectangle = { 58,350 + reverseCounter / 2,20,300 };					
							reverseCounter += step;
						}


					}

					SDL_SetRenderDrawColor(myRenderer, 255, 0, 0, 0xFF);//отображение квадратика температуры
					SDL_RenderFillRect(myRenderer, &thermoRectangle);

					SDL_Rect* sunClip = &sunSpriteClisp[frame / 2];
					mySunTexture.render(counter, 150, sunClip);//рисуем солнце

					SDL_SetRenderDrawColor(myRenderer, redColor, greenColor, blueColor, 0xFF);

					++frame;//переход к следующему фрейму

					//зацикливаем анимацию
					if (frame / 2 >= SUN_SPRITE_COUNT)
					{
						frame = 0;
					}

					myWindowTexture.render(0, 0, NULL);//на самом верхнем слое отрисовываем текстуру окна

				}
				SDL_Delay(50);
				SDL_RenderPresent(myRenderer);

			}
		}
	}

	close();

	return 0;
}


bool init()
{

	bool success = true;

	//инициализация SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Невозможно инициализировать SDL. Ошибка: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//создание окна по центру экрана с заданными константными координатами
		myWindow = SDL_CreateWindow("I508B Petrov A.V Sun Var 13", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (myWindow == NULL)
		{
			cout << "Окно не может быть создано. Ошибка: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create renderer for window
			myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (myRenderer == NULL)
			{
				cout << "Невозможно создать рендерер. Ошибка: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//белый цвет зливки экрана
				SDL_SetRenderDrawColor(myRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//загрузка png картинок
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "Невозможно инициализировать SDL_Image. Ошибка: " << IMG_GetError() << endl;;
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{

	bool success = true;


	if (!myWindowTexture.loadFromFile("images/newWindow.png"))
	{
		cout << "Невозможно загрузить текстуру" << endl;
		success = false;
	}
	if (!myThermometrTexture.loadFromFile("images/thermo123.png"))
	{
		cout << "Невозможно загрузить текстуру" << endl;
		success = false;
	}

	if (!mySunTexture.loadFromFile("images/1sun.png"))
	{
		cout << "Невозможно загрузить текстуру" << endl;
		success = false;
	}
	else//устанавливаем фреймы анимации
	{

		sunSpriteClisp[0].x = 0;
		sunSpriteClisp[0].y = 0;
		sunSpriteClisp[0].w = 115;
		sunSpriteClisp[0].h = 100;

		sunSpriteClisp[1].x = 120;
		sunSpriteClisp[1].y = 0;
		sunSpriteClisp[1].w = 120;
		sunSpriteClisp[1].h = 100;
	}


	return success;
}
//очистка памяти и выход из подсистем
void close()
{

	mySunTexture.free();
	myThermometrTexture.free();
	myWindowTexture.free();

	SDL_DestroyRenderer(myRenderer);
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;
	myRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
