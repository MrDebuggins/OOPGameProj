#include <cstdlib>
#include "Enemy.h"
#include "textureManager.h"
#include "Game.h"

void Enemy::loadEnemyTexture(SDL_Renderer* rend) 
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
	shape = r;
}

void Enemy::setEnemyLvl(int lvl)
{
	enemyLvl = lvl;
	switch (enemyLvl)
	{
	case 1:
		velocity = 2;
		break;
	case 2:
		velocity = 3;
		break;
	case 3:
		velocity = 1;
		break;
	default:
		break;
	}
}

void Enemy::draw(SDL_Renderer* rend) 
{
	textureManager::drawTexture(texturesArray[animID / 5], NULL, rend, &shape, viewDirection);
}

SDL_Rect Enemy::getHitBox() 
{
	return shape;
}

void Enemy::setDirFlags(SDL_Rect s) 
{
	//verify allowed directions by objescts
	if ((shape.x + shape.h >= s.x - 5) && (shape.x + shape.h < s.x + 5) && (shape.y >= s.y - shape.w) && (shape.y <= s.y + s.h))
		movementDirFlags[1] = 0;
	if ((shape.x <= s.x + s.w + 5) && (shape.x > s.x + s.w - 5) && (shape.y >= s.y - shape.w) && (shape.y <= s.y + s.h))
		movementDirFlags[3] = 0;
	if ((shape.y + shape.h >= s.y - 5) && (shape.y + shape.h < s.y + 5) && (shape.x >= s.x - shape.w) && (shape.x <= s.x + s.w))
		movementDirFlags[2] = 0;
	if ((shape.y <= s.y + s.h + 5) && (shape.y > s.y + s.h - 5) && (shape.x >= s.x - shape.w) && (shape.x <= s.x + s.w))
		movementDirFlags[0] = 0;
}

void Enemy::mapCollision() 
{
	//verify allowed movement directions by level borders (don't forgorr to optimaze map collisions)
	if (shape.x <= 5)
		movementDirFlags[3] = 0;
	if (shape.x >= Game::screenWidth - 71)
		movementDirFlags[1] = 0;
	if (shape.y <= 5)
		movementDirFlags[0] = 0;
	if (shape.y >= Game::screenHeight - 71)
		movementDirFlags[2] = 0;
}

void Enemy::enemyMovement() 
{
	if (movementContor >= distanceToMove || movementDirFlags[viewDirection / 90] == 0) 
	{
		xVelocity = 0;
		yVelocity = 0;

		//set a random direction and distance to move
		int dir = rand() % 4;
		if (movementDirFlags[dir] == false) //use % for less control statements!
		{
			for (int i = 0; i < 4; i++)
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
