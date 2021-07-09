#pragma once
#include "Entity.h"
class Player :public Entity
{
public:
	Player();
	Player(int, int, int, int);
	~Player();
	void getKeybordEvent(SDL_Event& e );//получение событий нажатия клавиш движения игрока

};

