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
	for (int i = 0; i < objNr; i++) //draw static objects
	{
		lvlObjsArray[i]->drawStaticObj(rend);
	}

	for (int i = 0; i < enemiesNr; i++) //draw enemies
	{
		if (enemies[i] != NULL)
			enemies[i]->draw(rend);
	}

	player->draw(rend);

	for (int i = 0; i <= enemiesNr; i++) //draw shells
	{
		projectiles[i]->draw(rend);
	}

	if (explosions.size() != 0) //draw explosions
	{
			for (auto a : explosions) 
			{
				if (a->draw(rend)) 
				{
					a->~effect();
					explosions.pop_back();
					break;
				}
			}	
	}
}

void level::loadLvlData(SDL_Renderer* rend) 
{
	ifstream objData;

	try
	{
		switch (lvlID)
		{
		case 1:
			objData.open("config/lvl1/lvl1_objs.txt");
			break;
		case 2:
			objData.open("config/lvl2/lvl2_objs.txt");
			break;
		case 3:
			objData.open("config/lvl3/lvl3_objs.txt");
			break;
		default:
			break;
		}

		if (objData.fail())
		{
			if (lvlID == 1)
				throw "Can't open file: config/lvl1/lvl1_objs.txt\n";
			else if (lvlID == 2)
				throw "Can't open file: config/lvl2/lvl2_objs.txt\n";
			else
				throw "Can't open file: config/lvl3/lvl3_objs.txt\n";
		}
	}
	catch (const char* str)
	{
		SDL_Log("%s", str);
	}

	objData >> objNr;
	lvlObjsArray = new staticGameObj*[objNr];
	staticHitBoxes = new SDL_Rect[objNr];


	//load static objects from txt file
	for (int i = 0; i < objNr; i++) 
	{
		lvlObjsArray[i] = new staticGameObj;

		int j;								
		objData >> j;

		lvlObjsArray[i]->loadStaticObjTexture("assets/png/FLOOR_1A.png", rend);

		objData >> staticHitBoxes[i].x >> staticHitBoxes[i].y >> staticHitBoxes[i].w >> staticHitBoxes[i].h;
		staticHitBoxes[i].w = 50; staticHitBoxes[i].h = 50;

		lvlObjsArray[i]->setObjHitBox(staticHitBoxes[i]);
	}

	objData.close();

	//load projectiles and enemies from txt file
	try
	{
		switch (lvlID)
		{
		case 1:
			objData.open("config/lvl1/lvl1_enemies.txt");
			break;
		case 2:
			objData.open("config/lvl2/lvl2_enemies.txt");
			break;
		case 3:
			objData.open("config/lvl3/lvl3_enemies.txt");
			break;
		default:
			break;
		}

		if (objData.fail())
		{
			if (lvlID == 1)
				throw "Can't open file: config/lvl1/lvl1_enemies.txt\n";
			else if (lvlID == 2)
				throw "Can't open file: config/lvl2/lvl2_enemies.txt\n";
			else
				throw "Can't open file: config/lvl3/lvl3_enemies.txt\n";
		}
	}
	catch (const char* str)
	{
		SDL_Log("%s", str);
	}


	objData >> enemiesNr;
	if (enemiesNr == 0) 
	{
		SDL_Log("Invalid number of enemies! Config files corrupted!\n");
	}
	enemiesCounter = enemiesNr;
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

		enemies[i]->loadTexture(rend);
	}

	// player projectile
	projectiles[enemiesNr] = new projectile;
	projectiles[enemiesNr]->setType(1);
	projectiles[enemiesNr]->loadTexture(rend);

	objData.close();

	player->loadTextures(rend);
}

int level::lvlEventHandler(SDL_Event* e, SDL_Renderer* rend) 
{
	if (enemiesCounter <= 0) //next lvl
		return 2;

	if (player->inputHandler(e)) //shoot
	{
		SDL_Rect* r = player->getHitBox();
		projectiles[enemiesNr]->setExistFlag(true, player->getViewDir(), r->x, r->y);
	}
	//
	//
	//player collision with static objects
	for (int i = 0; i < objNr; i++) 
	{
		if (player->objsCollision(staticHitBoxes[i]))
			return 1;
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
		//player shell collision
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
					enemiesCounter--;

					explosions.push_front(new effect(false, tempRect.x - 10, tempRect.y - 10, rend, true));
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
		player->getDmg(projectiles[i]->objCollision(player->getHitBox()));// with player
		
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
				enemies[i]->setDirFlags(staticHitBoxes[j]);  //verify directions by static objects
			}

			//shoot
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

	return 0;
}