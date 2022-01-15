#include "pauseMenu.h"

void pauseMenu::loadTextures(SDL_Renderer* rend) 
{
	buttonsTextures = new SDL_Texture*[8];
	for (int i = 0; i < 8; i++) 
	{
		buttonsTextures[i] = NULL;
	}
	buttonsTextures[0] = textureManager::loadTexture("assets/png/continue.png", rend);
	buttonsTextures[1] = textureManager::loadTexture("assets/png/continue1.png", rend);
	buttonsTextures[2] = textureManager::loadTexture("assets/png/main_menu.png", rend);
	buttonsTextures[3] = textureManager::loadTexture("assets/png/main_menu1.png", rend);

	buttonHitBoxes = new SDL_Rect[2];
	buttonHitBoxes[0] = { 450,200,300,100 };
	buttonHitBoxes[1] = { 450,350,300,100 };
}

void pauseMenu::draw(SDL_Renderer* rend)
{
	if (active[0]) // continue button
	{
		textureManager::drawTexture(buttonsTextures[1], NULL, rend, &buttonHitBoxes[0], 0);
	}
	else 
	{
		textureManager::drawTexture(buttonsTextures[0], NULL, rend, &buttonHitBoxes[0], 0);
	}

	if (active[1]) // main menu button
	{
		textureManager::drawTexture(buttonsTextures[3], NULL, rend, &buttonHitBoxes[1], 0);
	}
	else 
	{
		textureManager::drawTexture(buttonsTextures[2], NULL, rend, &buttonHitBoxes[1], 0);
	}
}

int pauseMenu::buttonPressed(SDL_Event* e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	for (int i = 0; i < 2; i++) 
	{
		if ((x > buttonHitBoxes[i].x) && (x < buttonHitBoxes[i].x + buttonHitBoxes[i].w) && (y > buttonHitBoxes[i].y) && (y < buttonHitBoxes[i].y + buttonHitBoxes[i].h)) 
		{
			active[i] = true;
			
			SDL_PollEvent(e);
			if (e->type == SDL_MOUSEBUTTONUP) 
			{
				in = false;
				return i;
			}
		}
		else 
		{
			active[i] = false;
		}
	}

	return -1;
}
