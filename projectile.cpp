#include "projectile.h"
#include "Game.h"
#include "textureManager.h"

void projectile::setExistFlag(bool f, int viewDir, int posx, int posy)
{
	show = f;
	this->viewDir = viewDir;
	shape.x = posx;
	shape.y = posy;
}

bool projectile::getExistFlag()
{
	return show;
}

void projectile::loadTexture(SDL_Renderer* rend)
{
	projTexture = textureManager::loadTexture("assets/png/effects/Sniper_Shell.png", rend);
}

void projectile::setType(int type)
{
	this->type = (projectileTypes)type;
	if (type == bullet || type == twoBullets)
		velocity = 2;
	else
		velocity = 3;
}

void projectile::mapCollision()
{
	if ((shape.y <= 1) || (shape.y >= Game::screenHeight - 1 - shape.h))
		show = false;//kaboom
	if ((shape.x <= 1) || (shape.x >= Game::screenWidth - 1 - shape.w))
		show = false;//kaboom
}

void projectile::move()
{
	if (show == true) 
	{
		switch (viewDir)
		{
		case 0:
			shape.y -= velocity;
			break;
		case 90:
			shape.x += velocity;
			break;
		case 180:
			shape.y += velocity;
			break;
		case 270:
			shape.x -= velocity;
			break;
		default:
			break;
		}

		SDL_Log("move\n");
	}
}

void projectile::draw(SDL_Renderer* rend)
{
	if(show == true)
	{
		textureManager::drawTexture(projTexture, NULL, rend, &shape, viewDir);
		SDL_Log("draw\n");
	}
}
