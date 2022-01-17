#pragma once
#include "entity.h"

class Player : public entity
{
	SDL_Texture** HPtextures;
public:
	Player()
	{
		HPtextures = NULL;
		shape = { 1,1,50,50 };
		velocity = 2;
		HP = 1000;
	}
	~Player() 
	{
		for(int i = 0; i < 5; i++)
		{
			SDL_DestroyTexture(HPtextures[i]);
		}
		delete[] HPtextures;
	}

	bool inputHandler(SDL_Event* e);
	void draw(SDL_Renderer* rend);
	void loadTextures(SDL_Renderer* rend);
	void move();
	bool objsCollision(SDL_Rect r);
	void mapCollision();
	int getViewDir();
	//SDL_Rect* getHitBox();
	void getDmg(int dmg);
};

