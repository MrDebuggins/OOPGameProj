#include "projectile.h"
#include "Game.h"
#include "textureManager.h"

void projectile::setExistFlag(bool f, int viewDir, int posx, int posy)
{
	show = f;
	this->viewDir = viewDir;

	switch (viewDir)
	{
	case 0:
		shape.x = posx + 22;
		shape.y = posy - 16;
		break;
	case 90:
		shape.x = posx + 50 + 5;
		shape.y = posy + 22 - 5;
		break;
	case 180:
		shape.x = posx + 22;
		shape.y = posy + 50;
		break;
	case 270:
		shape.x = posx - 16 + 5;
		shape.y = posy + 22 - 5;
		break;
	}
}

bool projectile::getExistFlag()
{
	return show;
}

void projectile::loadTexture(SDL_Renderer* rend)
{
	projTexture = textureManager::loadTexture("assets/png/effects/Heavy_Shell.png", rend);
}

void projectile::setType(int type)
{
	switch (type)
	{
	case bullet:
		velocity = 6;
		damage = 1;
		break;
	case twoBullets:
		velocity = 4;
		damage = 3;
		break;
	case plasma:
		velocity = 6;
		damage = 2;
		break;
	default:
		break;
	}
}

void projectile::mapCollision()
{
	if ((shape.y <= 1) || (shape.y >= Game::screenHeight - 1 - shape.h))
		show = false;//kaboom
	if ((shape.x <= 1) || (shape.x >= Game::screenWidth - 1 - shape.w))
		show = false;//kaboom
}

int projectile::objCollision(SDL_Rect* s, bool npc)
{
	if (show == true) 
	{
		if ((shape.x + shape.h >= s->x - 5) && (shape.x + shape.h <= s->x + 5) && (shape.y + 5 + shape.w >= s->y) && (shape.y + 5 <= s->y + s->h) && (viewDir == 90 || npc))
		{
			show = false;
			//SDL_Log("11111");
		}
		else if ((shape.x <= s->x + s->w + 5) && (shape.x >= s->x + s->w - 5) && (shape.y + 5 >= s->y - shape.w) && (shape.y + 5 <= s->y + s->h) && (viewDir == 270 || npc))
		{
			show = false;
			//SDL_Log("33333");
		}
		else if ((shape.y + shape.h >= s->y - 5) && (shape.y + shape.h <= s->y + 5) && (shape.x >= s->x - shape.w) && (shape.x <= s->x + s->w) && (viewDir == 180 || npc))
		{
			show = false;
			//SDL_Log("22222");
		}
		else if ((shape.y <= s->y + s->h + 5) && (shape.y + 5 >= s->y + s->h - 5) && (shape.x + shape.w >= s->x) && (shape.x <= s->x + s->w) && (viewDir == 0 || npc))
		{
			show = false;
			//SDL_Log("00000");
		}

		if (show == false) 
		{
			shape.x = -20;
			shape.y = -20;
			return damage;
		}
			
	}

	return 0;
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
	}
}

void projectile::draw(SDL_Renderer* rend)
{
	if (show == true)
		textureManager::drawTexture(projTexture, NULL, rend, &shape, viewDir);
}
