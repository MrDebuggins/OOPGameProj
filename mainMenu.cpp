#include "mainMenu.h"

void mainMenu::loadTextures(SDL_Renderer* rend)
{
	buttonsTextures = new SDL_Texture * [8];
	buttonsTextures[0] = textureManager::loadTexture("assets/png/lvl1.png", rend);
	buttonsTextures[1] = textureManager::loadTexture("assets/png/lvl11.png", rend);
	buttonsTextures[2] = textureManager::loadTexture("assets/png/lvl2.png", rend);
	buttonsTextures[3] = textureManager::loadTexture("assets/png/lvl21.png", rend);
	buttonsTextures[4] = textureManager::loadTexture("assets/png/lvl3.png", rend);
	buttonsTextures[5] = textureManager::loadTexture("assets/png/lvl31.png", rend);
	buttonsTextures[6] = textureManager::loadTexture("assets/png/quit.png", rend);
	buttonsTextures[7] = textureManager::loadTexture("assets/png/quit1.png", rend);

	buttonHitBoxes = new SDL_Rect[4];
	buttonHitBoxes[0] = { 100,50,300,100 };
	buttonHitBoxes[1] = { 450,50,300,100 };
	buttonHitBoxes[2] = { 800,50,300,100 };
	buttonHitBoxes[3] = { 450,500,300,100 };
	//buttonHitBoxes[0] = { 450,50,300,100 };
	//buttonHitBoxes[1] = { 450,200,300,100 };
	//buttonHitBoxes[2] = { 450,350,300,100 };
	//buttonHitBoxes[3] = { 450,500,300,100 };

	in = true;
}

int mainMenu::eventHandler(SDL_Event* e, SDL_Renderer* rend)
{
	in = true;

	while (true) 
	{
		if (SDL_GetTicks() - time >= 17) 
		{
			int t = buttonPressed(e);
			if (t != 0)
				return t;

			SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
			SDL_RenderClear(rend);
			draw(rend);
			SDL_RenderPresent(rend);
			time = SDL_GetTicks();
		}
		
	}

	in = false;
	return 0;
}

void mainMenu::draw(SDL_Renderer* rend)
{
	if (active[0]) 
	{
		textureManager::drawTexture(buttonsTextures[1], NULL, rend, &buttonHitBoxes[0], 0);
	}
	else 
	{
		textureManager::drawTexture(buttonsTextures[0], NULL, rend, &buttonHitBoxes[0], 0);
	}
	
	if (active[1])
	{
		textureManager::drawTexture(buttonsTextures[3], NULL, rend, &buttonHitBoxes[1], 0);
	}
	else
	{
		textureManager::drawTexture(buttonsTextures[2], NULL, rend, &buttonHitBoxes[1], 0);
	}

	if (active[2])
	{
		textureManager::drawTexture(buttonsTextures[5], NULL, rend, &buttonHitBoxes[2], 0);
	}
	else
	{
		textureManager::drawTexture(buttonsTextures[4], NULL, rend, &buttonHitBoxes[2], 0);
	}

	if (active[3])
	{
		textureManager::drawTexture(buttonsTextures[7], NULL, rend, &buttonHitBoxes[3], 0);
	}
	else
	{
		textureManager::drawTexture(buttonsTextures[6], NULL, rend, &buttonHitBoxes[3], 0);
	}
}

int mainMenu::buttonPressed(SDL_Event* e)
{
	in = true;
	int x, y;
	SDL_GetMouseState(&x, &y);
	//SDL_Log("adsgadfhsfh\n");
	for (int i = 0; i < 4; i++)
	{
		if ((x > buttonHitBoxes[i].x) && (x < buttonHitBoxes[i].x + buttonHitBoxes[i].w) && (y > buttonHitBoxes[i].y) && (y < buttonHitBoxes[i].y + buttonHitBoxes[i].h))
		{
			active[i] = true;

			SDL_PollEvent(e);
			if (e->type == SDL_MOUSEBUTTONUP)
			{
				in = false;
				return i + 1;
			}
		}
		else
		{
			active[i] = false;
		}
	}

	return 0;
}
