#include "pch.h"
#include "Player.h"
#include "Entity.h"
const int PLAYER_SPEED = 10;//����������� �������� ������
Player::Player() : Entity()
{
}

Player::Player(int, int, int, int) : Entity()
{
}


Player::~Player()
{
}
void Player::getKeybordEvent(SDL_Event& e)
{
	//�������� ���������� ������, ���� ������ ��������������� ������� ��� ��������, ����� ������ �������� � ���� � �������� ������������
	if (e.type == SDL_KEYDOWN)
	{

		xSpeed = PLAYER_SPEED;
		switch (e.key.keysym.sym)
		{

		case SDLK_a:
			xPos -= xSpeed;
			break;
		case SDLK_d:
			xPos += xSpeed;
			break;
		}

	}
	else
	{
		xSpeed = 0;
	}

}


