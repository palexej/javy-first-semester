#pragma once
#include <SDL.h>
class GraphicElement
{
public:

	GraphicElement();
	~GraphicElement();
	void free();//������������ ������
	void setAlpha(Uint8 alpha);//��������� �����-������ ��������

	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);//��������� �������� �� �����������

	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	//��������� �������� ��������
	int getWidth();
	int getHeight();

protected:
	SDL_Texture* mTexture;

	//������� �����������
	int mWidth;
	int mHeight;
};

