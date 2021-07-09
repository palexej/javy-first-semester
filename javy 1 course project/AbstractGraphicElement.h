#pragma once
#include <SDL.h>
class GraphicElement
{
public:

	GraphicElement();
	~GraphicElement();
	void free();//освобождение памяти
	void setAlpha(Uint8 alpha);//изменение альфа-канала текстуры

	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);//отрисовка текстуры по координатам

	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	//получение размеров текстуры
	int getWidth();
	int getHeight();

protected:
	SDL_Texture* mTexture;

	//размеры изображения
	int mWidth;
	int mHeight;
};

