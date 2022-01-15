#pragma once
#include "entity.h"

class Enemy : public entity
{
	int enemyLvl = 1;

	bool movementDirFlags[4];
	int distanceToMove;
	int movementContor;

	bool alive = false;
	bool canShoot = true;

public:
	

	Enemy() 
	{
		shape = { 1,1,50,50 };
		movementDirFlags[0] = true;
		movementDirFlags[1] = true;
		movementDirFlags[2] = true;
		movementDirFlags[3] = true;
		distanceToMove = 0;
		movementContor = 0;
		alive = false;
		canShoot = false;
	}

	~Enemy() {}

	void loadTexture(SDL_Renderer* rend);
	void setEnemyiHitBox(SDL_Rect r);
	void setEnemyLvl(int lvl);
	int getEnemyLvl();
	void draw(SDL_Renderer* rend);
	SDL_Rect getHitBox();
	void setDirFlags(SDL_Rect s);
	void mapCollision();
	bool behaviour(SDL_Rect* shell, int shellDir, SDL_Rect* player, SDL_Rect* objs, int objsNr);
	void enemyMovement();
	void move();
	void getDmg(int dmg);
	bool getState() { return alive; }
	int getViewDir() { return viewDirection; }
};

