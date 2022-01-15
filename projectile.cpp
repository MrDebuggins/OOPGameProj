#include "projectile.h"
#include "Game.h"
#include "textureManager.h"

void projectile::setExistFlag(bool f, int viewDir, int posx, int posy)
{
	show = f;
	this->viewDir = viewDir;

	switch (viewDir) // chek view direction
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
	switch (type)
	{
	case bullet:
		projTexture = textureManager::loadTexture("assets/png/effects/Heavy_Shell.png", rend);
		break;
	case plasma:
		projTexture = textureManager::loadTexture("assets/png/effects/Plasma.png", rend);
		break;
	case twoBullets:
		projTexture = textureManager::loadTexture("assets/png/effects/Double_Shell.png", rend);
		break;
	default:
		break;
	}

	shellEffect = new effect(true, -300, -300, rend, false);
}

void projectile::setType(int type)
{
	this->type = (projectileTypes)type;
	switch (type)
	{
	case bullet:
		velocity = 6;
		damage = 2;
		break;
	case twoBullets:
		velocity = 4;
		damage = 4;
		break;
	case plasma:
		velocity = 8;
		damage = 2;
		break;
	default:
		SDL_Log("Wrong projectile type! Config files corrupted!\n");
		velocity = 6;
		damage = 2;
		break;
	}
}

bool projectile::mapCollision()
{
	if (show == true) 
	{
		if ((shape.y <= 1) || (shape.y >= Game::screenHeight - 1 - shape.h))
			show = false;
		if ((shape.x <= 1) || (shape.x >= Game::screenWidth - 1 - shape.w))
			show = false;

		if (show == false) // explode
		{
			shellEffect->activate(shape.x - 20, shape.y - 18);
			shape.x = 1500; //hide shell
			shape.y = 900;
			return true;
		}
	}
	
	return false;
}

int projectile::objCollision(SDL_Rect* s)
{
	if (show == true) 
	{
		// chek if colided with top
		if ((shape.x + shape.h >= s->x - 5) && (shape.x + shape.h <= s->x + 5) && (shape.y + 5 + shape.w >= s->y) && (shape.y + 5 <= s->y + s->h) && (viewDir == 90))
		{
			show = false;
		}
		else if ((shape.x <= s->x + s->w + 5) && (shape.x >= s->x + s->w - 5) && (shape.y + 5 >= s->y - shape.w) && (shape.y + 5 <= s->y + s->h) && (viewDir == 270))
		{
			show = false;
		}
		else if ((shape.y + shape.h >= s->y - 5) && (shape.y + shape.h <= s->y + 5) && (shape.x >= s->x - shape.w) && (shape.x <= s->x + s->w) && (viewDir == 180))
		{
			show = false;
		}
		else if ((shape.y <= s->y + s->h + 5) && (shape.y + 5 >= s->y + s->h - 5) && (shape.x + shape.w >= s->x) && (shape.x <= s->x + s->w) && (viewDir == 0))
		{
			show = false;
		}
		// check if colided with side 
		else if ((shape.x >= s->x) && (shape.y >= s->y) && (shape.x <= s->x + s->w) && (shape.y <= s->y + s->h) && (viewDir == 0 || viewDir == 180)) 
		{
			show = false;
		}
		else if ((shape.x - 5 >= s->x) && (shape.y + 5 >= s->y) && (shape.x - 5 <= s->x + s->w) && (shape.y +5 <= s->y + s->h) && (viewDir == 90 || viewDir == 270)) 
		{
			show = false;
		}

		if (show == false) 
		{
			shellEffect->activate(shape.x - 20, shape.y - 18); //explode
			shape.x = 1500; //hide shell
			shape.y = 900;
			return damage;
		}
			
	}

	return false;
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
	{
		textureManager::drawTexture(projTexture, NULL, rend, &shape, viewDir);
	}

	shellEffect->draw(rend);
}
