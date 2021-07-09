#include "pch.h"
#include "Player.h"
#include "Entity.h"
const int PLAYER_SPEED = 10;//ограничение скорости игрока
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
	//изменяем координаты игрока, если нажата соответствующая клавиша для движения, иначе ставим скорость в ноль и движение прекращается
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


