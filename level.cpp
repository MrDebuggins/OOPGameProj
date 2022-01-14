#include <fstream>
#include <iterator>
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
		if (enemies[i] != NULL)
			enemies[i]->draw(rend);
	}

	player->draw(rend);

	for (int i = 0; i <= enemiesNr; i++) 
	{
		projectiles[i]->draw(rend);
	}

	if (explosions.size() != 0) 
	{
			for (auto a : explosions) 
			{
				if (a->draw(rend)) 
				{
					explosions.pop_back();
					break;
				}
			}	
	}
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
			lvlObjsArray[i]->loadStaticObjTexture("assets/png/FLOOR_1A.png", rend);
		else
			lvlObjsArray[i]->loadStaticObjTexture("assets/png/FLOOR_1A.png", rend);

		objData >> staticHitBoxes[i].x >> staticHitBoxes[i].y >> staticHitBoxes[i].w >> staticHitBoxes[i].h;

		lvlObjsArray[i]->setObjHitBox(staticHitBoxes[i]);
	}

	objData.close();

	//load projectiles and enemies from txt file
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

	projectiles = new projectile * [enemiesNr + 1];

	for(int i = 0; i < enemiesNr; i++)
	{
		enemies[i] = new Enemy;
		projectiles[i] = new projectile;

		int lvl;
		objData >> lvl;
		enemies[i]->setEnemyLvl(lvl);

		projectiles[i]->setType(lvl);
		projectiles[i]->loadTexture(rend);

		SDL_Rect r{};
		objData >> r.x >> r.y >> r.w >> r.h;
		enemies[i]->setEnemyiHitBox(r);

		enemies[i]->loadEnemyTexture(rend);
	}

	projectiles[enemiesNr] = new projectile;
	projectiles[enemiesNr]->setType(1);
	projectiles[enemiesNr]->loadTexture(rend);

	objData.close();

	player->loadPlayerTextures(rend);
}

void level::lvlEventHandler(SDL_Event* e, SDL_Renderer* rend) 
{
	if (player->inputHandler(e)) //shoot
	{
		SDL_Rect* r = player->getHitBox();
		projectiles[enemiesNr]->setExistFlag(true, player->getViewDir(), r->x, r->y);
	}
	//
	//
	//player collision with static obj's
	for (int i = 0; i < objNr; i++) 
	{
		player->objsCollision(staticHitBoxes[i]);
	}
	//player collision with enemies
	for (int i = 0; i < enemiesNr; i++) 
	{
		if (enemies[i] != NULL)
			player->objsCollision(enemies[i]->getHitBox());
	}
	
	player->mapCollision();
	player->move();

	//
	//
	//shells collision
		//player's shell collision
	if (projectiles[enemiesNr]->getExistFlag()) 
	{
		for (int k = 0; k < enemiesNr; k++) //with enmeies
		{
			if (enemies[k] != NULL)
			{
				SDL_Rect tempRect = enemies[k]->getHitBox();
				enemies[k]->getDmg(projectiles[enemiesNr]->objCollision(&tempRect));

				if (enemies[k]->getState() == false) //destroy npc
				{
					delete enemies[k];
					enemies[k] = NULL;

					effect* newExplo = new effect(false, tempRect.x, tempRect.y, rend, true);
					explosions.push_front(newExplo);
				}
			}
		}

		for (int k = 0; k < objNr; k++) //with static obj's
		{
			projectiles[enemiesNr]->objCollision(&staticHitBoxes[k]);
		}

		projectiles[enemiesNr]->mapCollision();
		projectiles[enemiesNr]->move();
	}
	//
	//
		//enemies shells collision
	for (int i = 0; i < enemiesNr; i++) 
	{
		player->getDmg(projectiles[i]->objCollision(player->getHitBox()));
		
		for (int k = 0; k < objNr; k++) //with static obj's
		{
			projectiles[i]->objCollision(&staticHitBoxes[k]);
		}

		projectiles[i]->mapCollision();
		projectiles[i]->move();
	}
	//
	//
	//enemies collision
	for (int i = 0; i < enemiesNr; i++) 
	{
		if (enemies[i] != NULL) 
		{
			enemies[i]->mapCollision();

			for (int j = 0; j < objNr; j++)
			{
				enemies[i]->setDirFlags(staticHitBoxes[j]);  //verify directions by static obj's
			}

			if (enemies[i]->behaviour(projectiles[enemiesNr]->getHitBox(), projectiles[enemiesNr]->getViewDir(), player->getHitBox(), staticHitBoxes, objNr)) 
			{
				SDL_Rect temp = enemies[i]->getHitBox();
				projectiles[i]->setExistFlag(true, enemies[i]->getViewDir(), temp.x, temp.y);
			}

			for (int k = 0; k < enemiesNr; k++)
			{
				if (k != i && enemies[k] != NULL)
					enemies[i]->setDirFlags(enemies[k]->getHitBox());  //verify directions by other NPC's
			}

			enemies[i]->setDirFlags(*player->getHitBox()); //verify directions by player

			enemies[i]->enemyMovement();
			enemies[i]->move();
		}
	}
}