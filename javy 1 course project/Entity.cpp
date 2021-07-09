#include "pch.h"
#include "Entity.h"

Entity::Entity(): StaticGraphicElement()
{
	xPos = 0;
	yPos = 0;
	xSpeed = 0;
	ySpeed = 0;
}

Entity::Entity(int myXpos = 0, int myYpos = 0, int myXspeed = 0, int myYSpeed = 0) : StaticGraphicElement()
{
	xPos = myXpos;
	yPos = myYpos;
	xSpeed = myXspeed;
	ySpeed = myYSpeed;
}
Entity::~Entity()
{
	free();
}
void Entity::move()
{
	//движение за счёт изменения координаты на скорость движения
	xPos += xSpeed;
	yPos += ySpeed;
	
}


void Entity::setXpos(int value)
{
	xPos = value;
}

int Entity::getXpos()
{
	return xPos;
}

void Entity::setYpos(int value)
{
	yPos = value;
}

int Entity::getYpos()
{
	return yPos;
}


void Entity::setXSpeed(int value)
{
	xSpeed = value;
}

int Entity::getXSpeed()
{
	return xSpeed;
}


void Entity::setYSpeed(int value)
{
	ySpeed = value;
}

//получение границ хитбокса и проверка на наличие совпадений по ним со вторым объектом
bool Entity::checkCollision(Entity &fireball)
{

	this->getHitboxSize();
	fireball.getHitboxSize();

	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	leftA = this->hitbox.x;
	rightA = this->hitbox.x + this->hitbox.w;
	topA = this->hitbox.y;
	bottomA = this->hitbox.y + this->hitbox.h;

	leftB = fireball.hitbox.x;
	rightB = fireball.hitbox.x + fireball.hitbox.w;
	topB = fireball.hitbox.y;
	bottomB = fireball.hitbox.y + fireball.hitbox.h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

int Entity::getYSpeed()
{
	return ySpeed;
}

SDL_Rect Entity::getHitboxSize()
{
	//получение квадрата хитбокса по координатам
	hitbox.x = xPos;
	hitbox.y = yPos;
	hitbox.w = getWidth();
	hitbox.h = getHeight();
	return hitbox;
}

