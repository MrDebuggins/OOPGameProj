#include <stdlib.h>
#include <cstdlib>
#include "Enemy.h"
#include "textureManager.h"
#include "Game.h"

void Enemy::loadTexture(SDL_Renderer* rend) 
{
	texturesArray = new SDL_Texture * [2];

	switch (enemyLvl)
	{
	case 1:
		texturesArray[0] =  textureManager::loadTexture("assets/png/enemy_1A.png", rend);
		texturesArray[1] = textureManager::loadTexture("assets/png/enemy_1A.png", rend);
		break;
	case 2:
		texturesArray[0] = textureManager::loadTexture("assets/png/enemy_3A.png", rend);
		texturesArray[1] = textureManager::loadTexture("assets/png/enemy_3B.png", rend);
		break;
	case 3:
		texturesArray[0] = textureManager::loadTexture("assets/png/enemy_4A.png", rend);
		texturesArray[1] = textureManager::loadTexture("assets/png/enemy_4B.png", rend);
		break;
	default:
		break;
	}
}

void Enemy::setEnemyiHitBox(SDL_Rect r) 
{
	if (r.x < 0 || r.x > 1150 || r.y < 0 || r.y > 600)
	{
		SDL_Log("Invalid enemy position! Config files corrupted!\n");
		shape.x, shape.y = 200;
	}

	shape.x = r.x;
	shape.y = r.y;
}

void Enemy::setEnemyLvl(int lvl)
{
	enemyLvl = lvl;
	alive = true;
	switch (enemyLvl)
	{
	case 1:
		velocity = 2;
		HP = 4;
		break;
	case 2:
		velocity = 3;
		HP = 4;
		break;
	case 3:
		velocity = 1;
		HP = 8;
		break;
	default:
		SDL_Log("Wrong NPC level! Config files corrupted!\n");
		velocity = 2;
		HP = 4;
		break;
	}
}

int Enemy::getEnemyLvl()
{
	return enemyLvl;
}

void Enemy::draw(SDL_Renderer* rend) 
{
	textureManager::drawTexture(texturesArray[animID / 5], NULL, rend, &shape, viewDirection);
}

void Enemy::setDirFlags(SDL_Rect s) 
{
	
	//verify allowed directions by objescts
	if ((shape.x + shape.h >= s.x - 5) && (shape.x + shape.h < s.x + 5) && (shape.y >= s.y - shape.w) && (shape.y <= s.y + s.h))
		movementDirFlags[1] = 0;
	else if ((shape.x <= s.x + s.w + 5) && (shape.x > s.x + s.w - 5) && (shape.y >= s.y - shape.w) && (shape.y <= s.y + s.h))
		movementDirFlags[3] = 0;
	else if ((shape.y + shape.h >= s.y - 5) && (shape.y + shape.h < s.y + 5) && (shape.x >= s.x - shape.w) && (shape.x <= s.x + s.w))
		movementDirFlags[2] = 0;
	else if ((shape.y <= s.y + s.h + 5) && (shape.y > s.y + s.h - 5) && (shape.x >= s.x - shape.w) && (shape.x <= s.x + s.w))
		movementDirFlags[0] = 0;
}

void Enemy::mapCollision() 
{
	//verify allowed movement directions by level borders
	if (shape.x <= 5)
		movementDirFlags[3] = 0;
	if (shape.x >= Game::screenWidth - 71)
		movementDirFlags[1] = 0;
	if (shape.y <= 5)
		movementDirFlags[0] = 0;
	if (shape.y >= Game::screenHeight - 71)
		movementDirFlags[2] = 0;
}

bool Enemy::behaviour(SDL_Rect* shell, int shellDir, SDL_Rect* player, SDL_Rect* objs, int objsNr)
{
	if (SDL_GetTicks() - lastShootTime >= 3500) //cannon reloaded
	{
		canShoot = true;
	}

	if (abs(shape.x - shell->x) < 200 && abs(shape.y - shell->y) < 200 && shell != NULL) //check if shell is nearby
	{
		if ((shellDir == 0 || shellDir == 180) && (shell->x - shell->w >= shape.x && shell->x <= shape.x + shape.w)) //potential vertical impact
		{
			movementDirFlags[0] = false;
			movementDirFlags[2] = false;

			if (viewDirection == 0 || viewDirection == 2) //set condition to change movement direction
				movementContor = distanceToMove;
		}
		else if ((shellDir == 90 || shellDir == 270) && (viewDirection == 90 || viewDirection == 270) && shell->y - shell->w >= shape.y && shell->y <= shape.y + shape.h) //potential horizontal impact
		{
			movementDirFlags[1] = false;
			movementDirFlags[3] = false;

			if (viewDirection == 0 || viewDirection == 2)
				movementContor = distanceToMove;
		}
		else if ((shellDir == 90 || shellDir == 270) && !(shell->y - shell->w >= shape.y || shell->y <= shape.y + shape.h)) //dodge if comes from side
		{
			movementDirFlags[0] = false;
			movementDirFlags[2] = false;
			
		}
	}
	else if(canShoot == true) //check if can shoot
	{
		if ((shape.y + shape.w >= (player->y + 25)) && (shape.y <= (player->y + player->h - 25))) //player is left or right
		{
			if (shape.x > player->x) //player is on left side
			{

				bool freeTraiectory = true;
				for (int i = 0; i < objsNr; i++) //check for objs between player and enemy
				{
					if ((shape.y + shape.w >= objs[i].y) && (shape.y <= objs[i].y + objs[i].h) && (player->x < objs[i].x) && (objs[i].x < shape.x)) 
					{
						freeTraiectory = false;
						break;
					}
				}
				if (freeTraiectory && canShoot && movementDirFlags[3])  //shoot
				{
					canShoot = false;
					lastShootTime = SDL_GetTicks();
					viewDirection = 270;
					xVelocity = -velocity;
					yVelocity = 0;
					return true;
				}
				
			}
			else //player is on right side
			{
				bool freeTraiectory = true;
				for (int i = 0; i < objsNr; i++) ////check for objs between player and enemy
				{
					if ((shape.y + shape.w >= objs[i].y) && (shape.y <= objs[i].y + objs[i].h) && (shape.x < objs[i].x) && (objs[i].x < player->x))
					{
						freeTraiectory = false;
						break;
					}
				}
				if (freeTraiectory && canShoot && movementDirFlags[1]) //shoot
				{
					canShoot = false;
					lastShootTime = SDL_GetTicks();
					viewDirection = 90;
					xVelocity = velocity;
					yVelocity = 0;
					return true;
				}
			}
		}
		else if ((shape.x + shape.w >= (player->x + 25)) && (shape.x <= (player->x + player->w - 25))) //player is above or below
		{
			if(shape.y > player->y) //player is above
			{
				bool freeTraiectory = true;
				for (int i = 0; i < objsNr; i++) 
				{
					if ((shape.x + shape.w >= objs[i].x) && (shape.x <= objs[i].x + objs[i].w) && (player->y < objs[i].y) && (objs[i].y < shape.y))
					{
						freeTraiectory = false;
						break;
					}
				}
				if (freeTraiectory && canShoot && movementDirFlags[0]) 
				{
					canShoot = false;
					lastShootTime = SDL_GetTicks();
					viewDirection = 0;
					xVelocity = 0;
					yVelocity = -velocity;
					return true;
				}
			}
			else //player is below
			{
				bool freeTraiectory = true;
				for (int i = 0; i < objsNr; i++)
				{
					if ((shape.y + shape.w >= objs[i].y + 15) && (shape.y <= objs[i].y + objs[i].h) && (shape.y < objs[i].y) && (objs[i].y < player->y))
					{
						freeTraiectory = false;
						break;
					}
				}
				if (freeTraiectory && canShoot && movementDirFlags[2])
				{
					canShoot = false;
					lastShootTime = SDL_GetTicks();
					viewDirection = 180;
					xVelocity = 0;
					yVelocity = velocity;
					return true;
				}
			}
		}
	}

	return false;
}

void Enemy::enemyMovement() 
{
	if (movementContor >= distanceToMove || movementDirFlags[viewDirection / 90] == 0) 
	{
		xVelocity = 0;
		yVelocity = 0;

		//set a random allowed direction and distance to move
		int dir = rand() % 4;
		if (movementDirFlags[dir] == false)
		{
			for (int i = 0; i < 5; i++)
			{
				if (dir == 3)
					dir = 0;
				if (movementDirFlags[dir] == false)
				{
					++dir;
				}
				else
					continue;
			}
		}
		
		viewDirection = dir * 90;
	
		distanceToMove = rand() % 450 + 150;
		movementContor = 0;

		//set the velocity
		switch (viewDirection)
		{
		case 0:
			yVelocity = -velocity;
			break;
		case 90:
			xVelocity = velocity;
			break;
		case 180:
			yVelocity = velocity;
			break;
		case 270:
			xVelocity = -velocity;
			break;
		}
	}
}

void Enemy::move() 
{
	if (yVelocity != 0 || xVelocity != 0)
	{
		if (animID == 9)
			animID = 0;
		else
			animID++;
	}

	shape.y += yVelocity;
	shape.x += xVelocity;
	movementContor += abs(xVelocity);
	movementContor += abs(yVelocity);

	for (int i = 0; i < 4; i++)
		movementDirFlags[i] = 1;
}

void Enemy::getDmg(int dmg)
{
	HP = HP - dmg;
	if (HP <= 0) 
	{
		alive = false;
	}
}
