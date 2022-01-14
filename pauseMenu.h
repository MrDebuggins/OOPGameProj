#pragma once
#include "menu.h"
class pauseMenu : public menu
{
private:
	bool active[2] = { false,false };
public:
	void loadTextures(SDL_Renderer* rend);
	int eventHandler(SDL_Event* e, SDL_Renderer* rend);
	void draw(SDL_Renderer* rend);
	int buttonPressed(SDL_Event* e);

	//pauseMenu() 
	//{
	//	buttonHitBoxes = NULL;
	//	buttonsTextures = NULL;
	//}
};

