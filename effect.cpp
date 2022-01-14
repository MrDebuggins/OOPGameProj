#include "effect.h"
#include "textureManager.h"

void effect::loadTexutres(SDL_Renderer* rend)
{
	//if (type) 
	//{
	//	texturesArray = new SDL_Texture*[3];
	//	texturesArray[0] = textureManager::loadTexture("assets/png/effects/Explosion_A.png", rend);
	//	texturesArray[1] = textureManager::loadTexture("assets/png/effects/Explosion_B.png", rend);
	//	texturesArray[2] = textureManager::loadTexture("assets/png/effects/Explosion_C.png", rend);

	//	shape.w = 50;
	//	shape.h = 50;
	//}
	//else 
	//{
		texturesArray = new SDL_Texture * [8];
		texturesArray[0] = textureManager::loadTexture("assets/png/effects/Explosion_A.png", rend);
		texturesArray[1] = textureManager::loadTexture("assets/png/effects/Explosion_B.png", rend);
		texturesArray[2] = textureManager::loadTexture("assets/png/effects/Explosion_C.png", rend);
		texturesArray[3] = textureManager::loadTexture("assets/png/effects/Explosion_D.png", rend);
		texturesArray[4] = textureManager::loadTexture("assets/png/effects/Explosion_E.png", rend);
		texturesArray[5] = textureManager::loadTexture("assets/png/effects/Explosion_F.png", rend);
		texturesArray[6] = textureManager::loadTexture("assets/png/effects/Explosion_G.png", rend);
		texturesArray[7] = textureManager::loadTexture("assets/png/effects/Explosion_H.png", rend);

		shape.w = 50;
		shape.h = 50;
	//}
}

bool effect::draw(SDL_Renderer* rend)
{
	if (active) 
	{
		textureManager::drawTexture(texturesArray[animID/5], NULL, rend, &shape, NULL);

		animID++;

		if ((type == true) && (animID == 14)) 
		{
			animID = 0;
			active = false;
			return true;
		}
		else if ((type == false) && (animID == 39)) 
		{
			animID = 0;
			active = false;
			return true;
		}
		else
			return false;
	}
	
	return false;
}

void effect::activate(int x, int y)
{
	active = true;
	shape.x = x;
	shape.y = y;
}
