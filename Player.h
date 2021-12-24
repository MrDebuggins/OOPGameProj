#pragma once
#include "entity.h"

class Player : public entity
{


public:
	Player()
	{
		shape = { 1,1,50,50 };
		type = obgjTypePlayer;
		velocity = 2;
	}

	bool inputHandler(SDL_Event* e);
	void draw(SDL_Renderer* rend);
	void loadPlayerTextures(SDL_Renderer* rend);
	void move();
	void objsCollision(SDL_Rect r);
	void mapCollision();
	int getViewDir();
	SDL_Rect getHitBox();
};

