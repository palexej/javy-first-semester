#pragma once
#include "StaticGraphicElement.h"
class Entity : public StaticGraphicElement//����� ��������
{
public:
	Entity();
	Entity(int,int,int,int);
	~Entity();
	void move();
	//�������� � ��������� ��������� ���������� �������� � ������� �� ������ �� ���� ����
	void setXpos(int);

	int getXpos();

	void setYpos(int);

	int getYpos();

	void setXSpeed(int);

	int getXSpeed();

	void setYSpeed(int);

	int getYSpeed();

	bool checkCollision(Entity &);//�������� �� ������������
	
	SDL_Rect getHitboxSize();
protected:
	int xPos, yPos;
	int xSpeed, ySpeed;
	SDL_Rect hitbox;
};

