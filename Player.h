#pragma once
#include "animatedGameObj.h"

class Player : public animatedGameObj
{


public:
	Player()
	{
		shape = { 1,1,70,70 };
		type = obgjTypePlayer;
		velocity = 2;
	}

	void eventHandler(SDL_Event* e);
	void draw(SDL_Renderer* rend);
	void loadPlayerTextures(SDL_Renderer* rend);
	void move();
	void collisionHandler(SDL_Event* e);
};

