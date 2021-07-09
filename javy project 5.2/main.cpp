/*�� ������ ��������� ������������� ����������� �������� ��������� �������, ����� ��
��������� ������������ ��� ������� ������� �Esc�.
���������� �� ������ ���������, ������� ���������� ����������� �� �����. �� ����������
���������� ������� � �� �������� ��������. ��� ������� �� ����� ������� �������� ������ �
������� ���������� �������� ������ �����. ����� ������ �������, ������� ���������� ��������
������ ����*/


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
		cout << "������ �������������" << endl;
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
						if (e.key.keysym.sym == SDLK_ESCAPE)//����� ��� �������
						{
							quit = true;
						}
						else
						{
							startAnimation = true;
						}


						switch (e.key.keysym.sym)
						{
						case SDLK_ESCAPE://���� ������ �� ������, �� �������
							quit = true;
							break;

						default:
							break;
						}
					}

				}


				SDL_RenderClear(myRenderer);

				if (startAnimation == false)//���� ��� ������� �������, �� ������ ��� ��� ������
				{
					myThermometrTexture.render(30, 250, NULL);
					SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 0xFF);
					myWindowTexture.render(0, 0, NULL);

				}
				if (startAnimation == true)
				{
					myThermometrTexture.render(30, 250, NULL);
					counter += step;
					if (counter > SCREEN_WIDTH+100)//�������� ��������, ���� ����� �� ������� ������
					{
						counter = 0;
						reverseCounter = 0;
					}

					SDL_Rect thermoRectangle;//������������� ����������� �����������

					if (counter <= SCREEN_WIDTH / 2 + 30)
					{
						
						if (blueColor < 249)//���� �� ��������� ����� ����, �� ������ ��������� ��������� ������� �� �����������
						{
							blueColor += step;
							greenColor += step;
							thermoRectangle = { 58,480,20,-counter / 2 };

						}

					}

					else if (counter < SCREEN_WIDTH + 100)//���� �������� �� ����� ������, ����������� ����� ����� ������
					{
						if (blueColor > 0)//���� ���� �� ������, ���������� ������������� � ����������� � �������� �������	
						{
							greenColor -= step;
							blueColor -= step;
							thermoRectangle = { 58,350 + reverseCounter / 2,20,300 };					
							reverseCounter += step;
						}


					}

					SDL_SetRenderDrawColor(myRenderer, 255, 0, 0, 0xFF);//����������� ���������� �����������
					SDL_RenderFillRect(myRenderer, &thermoRectangle);

					SDL_Rect* sunClip = &sunSpriteClisp[frame / 2];
					mySunTexture.render(counter, 150, sunClip);//������ ������

					SDL_SetRenderDrawColor(myRenderer, redColor, greenColor, blueColor, 0xFF);

					++frame;//������� � ���������� ������

					//����������� ��������
					if (frame / 2 >= SUN_SPRITE_COUNT)
					{
						frame = 0;
					}

					myWindowTexture.render(0, 0, NULL);//�� ����� ������� ���� ������������ �������� ����

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

	//������������� SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "���������� ���������������� SDL. ������: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//�������� ���� �� ������ ������ � ��������� ������������ ������������
		myWindow = SDL_CreateWindow("I508B Petrov A.V Sun Var 13", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (myWindow == NULL)
		{
			cout << "���� �� ����� ���� �������. ������: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create renderer for window
			myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (myRenderer == NULL)
			{
				cout << "���������� ������� ��������. ������: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//����� ���� ������ ������
				SDL_SetRenderDrawColor(myRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//�������� png ��������
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "���������� ���������������� SDL_Image. ������: " << IMG_GetError() << endl;;
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
		cout << "���������� ��������� ��������" << endl;
		success = false;
	}
	if (!myThermometrTexture.loadFromFile("images/thermo123.png"))
	{
		cout << "���������� ��������� ��������" << endl;
		success = false;
	}

	if (!mySunTexture.loadFromFile("images/1sun.png"))
	{
		cout << "���������� ��������� ��������" << endl;
		success = false;
	}
	else//������������� ������ ��������
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
//������� ������ � ����� �� ���������
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
