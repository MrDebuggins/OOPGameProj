#pragma once
#include <list>
#include "textureManager.h"
#include "staticGameObj.h"
#include "Player.h"
#include "Enemy.h"
#include "projectile.h"
#include "effect.h"

class level
{
	int lvlID;
	int objNr;
	int enemiesNr;
	int enemiesCounter;

	SDL_Texture* floorTexture;
	staticGameObj** lvlObjsArray;
	Player* player;
	Enemy** enemies;
	projectile** projectiles;

	SDL_Rect* staticHitBoxes;

	std::list<effect*> explosions;
public:
	level() 
	{
		lvlID = 1;
		floorTexture = NULL;
		lvlObjsArray = NULL;

		player = NULL;
		enemies = NULL;

		staticHitBoxes = NULL;
		projectiles = NULL;

		objNr = 0;
		enemiesNr = 0;
		enemiesCounter = 0;
	}

	level(SDL_Renderer* rend, int id)
	{

		lvlID = id;
		floorTexture = textureManager::loadTexture("assets/png/grass_02.png", rend);

		player = new Player;
		enemies = NULL;
		loadLvlData(rend);
	}

	~level() 
	{
		SDL_DestroyTexture(floorTexture);
		floorTexture = NULL;

		for (int i = 0; i < objNr; i++) 
		{
			delete lvlObjsArray[i];
		}
		delete[] lvlObjsArray;
		lvlObjsArray = NULL;

		delete player;
		player = NULL;

		for (int i = 0; i < enemiesNr; i++) 
		{
			delete enemies[i];
		}
		delete[] enemies;

		for (int i = 0; i <= enemiesNr; i++) 
		{
			delete projectiles[i];
		}
		delete[] projectiles;

		delete[] staticHitBoxes;
		staticHitBoxes = NULL;

		for (auto a : explosions) 
		{
			a->~effect();
		}
		explosions.clear();
	}

	void loadLvlData(SDL_Renderer* rend);
	void drawLvlFloor(SDL_Renderer* rend);
	void drawLvlObjs(SDL_Renderer* rend);
	int lvlEventHandler(SDL_Event* e, SDL_Renderer* rend);
	int getID() { return lvlID; }
};

