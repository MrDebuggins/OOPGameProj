#pragma once
#include "animatedGameObj.h"
#include "dataStructures.h"
class projectile : public animatedGameObj
{
	SDL_Texture* projTexture = NULL;
	projectileTypes type;
	bool show = 0;

	int viewDir;
public:
	projectile() 
	{
		projTexture = NULL;
		this->viewDir = 0;
		type = bullet;
		shape = { 0,0,100,100 };
	}

	void setExistFlag(bool f, int viewDir, int posx, int posy);
	bool getExistFlag();
	void loadTexture(SDL_Renderer* rend);
	void setType(int type);
	void mapCollision();
	void move();
	void draw(SDL_Renderer* rend);
};

