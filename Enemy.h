#pragma once
#include "entity.h"

class Enemy : public entity
{
	int enemyLvl = 1;
	bool movementDirFlags[4] = {1,1,1,1};
	int distanceToMove = 0;
	int movementContor = 0;
	bool alive = false;

public:
	

	Enemy() 
	{
		shape = { 1,1,70,100 };
		type = objTypeEnemy;

		//enemyLvl = 1;
	}

	~Enemy() 
	{
		enemyLvl = NULL;
		distanceToMove = NULL;
		movementContor = NULL;
		alive = NULL;
	}

	void loadEnemyTexture(SDL_Renderer* rend);
	void setEnemyiHitBox(SDL_Rect r);
	void setEnemyLvl(int lvl);
	int getEnemyLvl();
	void draw(SDL_Renderer* rend);
	SDL_Rect getHitBox(const char* str);
	void setDirFlags(SDL_Rect s);
	void mapCollision();
	void enemyMovement();
	void move();
	void getDmg(int dmg);
	bool getState() { return alive; }
};

