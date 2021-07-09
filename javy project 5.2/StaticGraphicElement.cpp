
#include "StaticGraphicElement.h"
#include<iostream>
extern  SDL_Window* myWindow;//область окна

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

	//итоговая тестура
	SDL_Texture* newTexture = NULL;

	//загрузка через путь
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout<<"Невозможно загрузить изображение по пути "<< path.c_str()<<"Ошибка "<<IMG_GetError();
	}
	else
	{
		
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//создание текстуры из поверхности
		newTexture = SDL_CreateTextureFromSurface(myRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			cout<<"Невозможно создать текстуру по пути "<< path.c_str()<<" "<< SDL_GetError();
		}
		else
		{
			//получение размеров изображения
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//удаление старой поверхности
		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void StaticGraphicElement::free()
{
	//освобождения памяти
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
	//размер для рендерера на экране
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	//получение размера для анимированного изображения
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
