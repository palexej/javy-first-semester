
#include "StaticGraphicElement.h"
#include<iostream>
extern  SDL_Window* myWindow;//������� ����

extern  SDL_Renderer* myRenderer;
extern  SDL_Texture* myTexture;
using namespace std;

StaticGraphicElement::StaticGraphicElement()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

StaticGraphicElement::~StaticGraphicElement()
{
	free();
}

bool StaticGraphicElement::loadFromFile(string path)
{

	free();

	//�������� �������
	SDL_Texture* newTexture = NULL;

	//�������� ����� ����
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout<<"���������� ��������� ����������� �� ���� "<< path.c_str()<<"������ "<<IMG_GetError();
	}
	else
	{
		
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//�������� �������� �� �����������
		newTexture = SDL_CreateTextureFromSurface(myRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			cout<<"���������� ������� �������� �� ���� "<< path.c_str()<<" "<< SDL_GetError();
		}
		else
		{
			//��������� �������� �����������
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//�������� ������ �����������
		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void StaticGraphicElement::free()
{
	//������������ ������
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void StaticGraphicElement::render(int x, int y, SDL_Rect* clip)
{
	//������ ��� ��������� �� ������
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	//��������� ������� ��� �������������� �����������
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(myRenderer, mTexture, clip, &renderQuad);
}

int StaticGraphicElement::getWidth()
{
	return mWidth;
}

int StaticGraphicElement::getHeight()
{
	return mHeight;
}
