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
	shape = r;
}