#include <fstream>
#include "level.h"
#include "Game.h"

using namespace std;

void level::drawLvlFloor(SDL_Renderer* rend) 
{
	for (int i = 0; i < Game::screenWidth; i += 150) 
	{
		for (int j = 0; j < Game::screenHeight; j += 150) 
		{
			SDL_Rect rect = { i,j,150,150 };
			textureManager::drawTexture(floorTexture, NULL, rend, &rect, NULL);
		}
	}
}

void level::drawLvlObjs(SDL_Renderer* rend) 
{
	for (int i = 0; i < objNr; i++) 
	{
		lvlObjsArray[i]->drawStaticObj(rend);
	}

	for (int i = 0; i < enemiesNr; i++) 
	{
		enemies[i]->draw(rend);
	}

	player->draw(rend);
}

void level::loadLvlData(SDL_Renderer* rend) 
{
	ifstream objData;

	switch (lvlID)
	{
	case 1:
		objData.open("config/lvl1/lvl1_objs.txt");
		break;
	default:
		break;
	}

	objData >> objNr;
	lvlObjsArray = new staticGameObj*[objNr];
	staticHitBoxes = new SDL_Rect[objNr];


	//load static objects from txt file
	for (int i = 0; i < objNr; i++) 
	{
		lvlObjsArray[i] = new staticGameObj;

		int j;								//choose what texture to load for this obj
		objData >> j;
		if (j == 1)
			lvlObjsArray[i]->loadStaticObjTexture("assets/png/STONE_1B.png", rend);
		else
			lvlObjsArray[i]->loadStaticObjTexture("assets/png/STONE_2B.png", rend);

		objData >> staticHitBoxes[i].x >> staticHitBoxes[i].y >> staticHitBoxes[i].w >> staticHitBoxes[i].h;

		lvlObjsArray[i]->setObjHitBox(staticHitBoxes[i]);
	}

	objData.close();

	//load enemies from txt file
	switch (lvlID)
	{
	case 1:
		objData.open("config/lvl1/lvl1_enemies.txt");
		break;
	default:
		break;
	}

	objData >> enemiesNr;
	enemies = new Enemy*[enemiesNr];

	for(int i = 0; i < enemiesNr; i++)
	{
		enemies[i] = new Enemy;

		int lvl;
		objData >> lvl;
		enemies[i]->setEnemyLvl(lvl);

		SDL_Rect r{};
		objData >> r.x >> r.y >> r.w >> r.h;
		enemies[i]->setEnemyiHitBox(r);

		enemies[i]->loadEnemyTexture(rend);
	}

	objData.close();

	player->loadPlayerTextures(rend);

	//load projectiles

}

void level::lvlEventHandler(SDL_Event* e) 
{
	player->inputHandler(e);

	for (int i = 0; i < objNr; i++) 
	{
		player->collisionHandler(e, staticHitBoxes[i]);
	}
	player->move();

	for (int i = 0; i < enemiesNr; i++)
	{
		enemies[i]->mapCollision();
		for (int j = 0; j < objNr; j++) 
		{
			enemies[i]->setDirFlags(staticHitBoxes[j]);  //verify directions by static obj's
		}

		for (int k = 0; k < enemiesNr; k++) 
		{
			if (k != i)
				enemies[i]->setDirFlags(enemies[k]->getHitBox());  //verify directions by other NPC's
		}

		enemies[i]->enemyMovement();
		enemies[i]->move();
	}
}