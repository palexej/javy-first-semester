#pragma once
#include "StaticGraphicElement.h"
class Entity : public StaticGraphicElement//класс сущности
{
public:
	Entity();
	Entity(int,int,int,int);
	~Entity();
	void move();
	//усановка и получение различных параметров скорости и позиций на экране по двум осям
	void setXpos(int);

	int getXpos();

	void setYpos(int);

	int getYpos();

	void setXSpeed(int);

	int getXSpeed();

	void setYSpeed(int);

	int getYSpeed();

	bool checkCollision(Entity &);//проверка на столкновение
	
	SDL_Rect getHitboxSize();
protected:
	int xPos, yPos;
	int xSpeed, ySpeed;
	SDL_Rect hitbox;
};

