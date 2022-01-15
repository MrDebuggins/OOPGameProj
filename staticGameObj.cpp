#include "staticGameObj.h"
#include "textureManager.h"

void staticGameObj::loadStaticObjTexture(const char path[], SDL_Renderer* rend) 
{
	objTexture = textureManager::loadTexture(path, rend);
}

void staticGameObj::drawStaticObj(SDL_Renderer* rend) 
{
	textureManager::drawTexture(objTexture, NULL, rend, &shape, NULL);
}

void staticGameObj::setObjHitBox(SDL_Rect r) 
{
	if ((r.x < 0) || (r.x > 1150) || (r.y < 0) || (r.y > 600)) 
	{
		SDL_Log("Invalid static object position! Config files corrupted!\n");
		shape.x, shape.y = 200;
	}

	shape.x = r.x;
	shape.y = r.y;
	shape.h = 50;
	shape.w = 50;
}