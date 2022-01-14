#pragma once
#include "entity.h"

class Enemy : public entity
{
	int enemyLvl = 1;

	bool movementDirFlags[4] = {1,1,1,1};
	int distanceToMove = 0;
	int movementContor = 0;

	bool alive = false;
	bool canShoot = true;
	//int timeFromLastShot = 0;

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
	SDL_Rect getHitBox();
	void setDirFlags(SDL_Rect s);
	void mapCollision();
	bool behaviour(SDL_Rect* shell, int shellDir, SDL_Rect* player, SDL_Rect* objs, int objsNr);
	void enemyMovement();
	void move();
	void getDmg(int dmg);
	bool getState() { return alive; }
	void checkIfCanDodge(int dir);
	bool checkDirForStaticObjs(SDL_Rect* s);
	int getViewDir() { return viewDirection; }
};

