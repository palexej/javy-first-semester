#include "pch.h"
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include<conio.h>
#include <iostream>
using namespace std;
#include "AbstractGraphicElement.h"
class TextLabel :public GraphicElement
{
public:
	
	TextLabel();

	~TextLabel();


	bool TextLabel::setTextAndColor(string, int r, int g, int b);

	//void free();//������������ ������
	//void setAlpha(Uint8 alpha);//��������� �����-������ ��������
	//
	//void render(int x, int y);//��������� �������� �� �����������


	////��������� �������� ��������
	//int getWidth();
	//int getHeight();
	//void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);


	/*void setTextString(string myText);

	string getTextString();*/

protected:
	string mTextString;
	
	//SDL_Texture* mTexture;

	////������� �����������
	//int mWidth;
	//int mHeight;
	
};