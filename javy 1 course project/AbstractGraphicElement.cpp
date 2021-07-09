#include "pch.h"
#include "AbstractGraphicElement.h"


extern  SDL_Window* myWindow;//область окна

extern  SDL_Renderer* myRenderer;


void GraphicElement::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}


void GraphicElement::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void GraphicElement::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(myRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int GraphicElement::getWidth()
{
	return mWidth;
}

int GraphicElement::getHeight()
{
	return mHeight;
}


GraphicElement::GraphicElement()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

GraphicElement::~GraphicElement()
{
	free();
}

void GraphicElement::free()
{
	//освобождение памяти под текстуру, если она сущетсвует
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		//mTextString = "";

	}
}